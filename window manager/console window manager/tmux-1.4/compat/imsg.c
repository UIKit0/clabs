/* $Id: imsg.c,v 1.7 2010/11/13 16:29:05 nicm Exp $ */
/*	$OpenBSD: imsg.c,v 1.3 2010/05/26 13:56:07 nicm Exp $	*/

/*
 * Copyright (c) 2003, 2004 Henning Brauer <henning@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/uio.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tmux.h"

int	 imsg_get_fd(struct imsgbuf *);

void
imsg_init(struct imsgbuf *ibuf, int fd)
{
	msgbuf_init(&ibuf->w);
	bzero(&ibuf->r, sizeof(ibuf->r));
	ibuf->fd = fd;
	ibuf->w.fd = fd;
	ibuf->pid = getpid();
	TAILQ_INIT(&ibuf->fds);
}

ssize_t
imsg_read(struct imsgbuf *ibuf)
{
	struct msghdr		 msg;
	struct cmsghdr		*cmsg;
	union {
		struct cmsghdr hdr;
		char	buf[CMSG_SPACE(sizeof(int) * 16)];
	} cmsgbuf;
	struct iovec		 iov;
	ssize_t			 n;
	int			 fd;
	struct imsg_fd		*ifd;

	bzero(&msg, sizeof(msg));

	iov.iov_base = ibuf->r.buf + ibuf->r.wpos;
	iov.iov_len = sizeof(ibuf->r.buf) - ibuf->r.wpos;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = &cmsgbuf.buf;
	msg.msg_controllen = sizeof(cmsgbuf.buf);

	if ((n = recvmsg(ibuf->fd, &msg, 0)) == -1) {
		if (errno != EINTR && errno != EAGAIN) {
			return (-1);
		}
		return (-2);
	}

	ibuf->r.wpos += n;

	for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL;
	    cmsg = CMSG_NXTHDR(&msg, cmsg)) {
		if (cmsg->cmsg_level == SOL_SOCKET &&
		    cmsg->cmsg_type == SCM_RIGHTS) {
			fd = (*(int *)CMSG_DATA(cmsg));
			if ((ifd = calloc(1, sizeof(struct imsg_fd))) == NULL) {
				close(fd);
				return (-1);
			}
			ifd->fd = fd;
			TAILQ_INSERT_TAIL(&ibuf->fds, ifd, entry);
		}
		/* we do not handle other ctl data level */
	}

	return (n);
}

ssize_t
imsg_get(struct imsgbuf *ibuf, struct imsg *imsg)
{
	size_t			 av, left, datalen;

	av = ibuf->r.wpos;

	if (IMSG_HEADER_SIZE > av)
		return (0);

	memcpy(&imsg->hdr, ibuf->r.buf, sizeof(imsg->hdr));
	if (imsg->hdr.len < IMSG_HEADER_SIZE ||
	    imsg->hdr.len > MAX_IMSGSIZE) {
		errno = ERANGE;
		return (-1);
	}
	if (imsg->hdr.len > av)
		return (0);
	datalen = imsg->hdr.len - IMSG_HEADER_SIZE;
	ibuf->r.rptr = ibuf->r.buf + IMSG_HEADER_SIZE;
	if ((imsg->data = malloc(datalen)) == NULL && datalen != 0)
		return (-1);

	if (imsg->hdr.flags & IMSGF_HASFD)
		imsg->fd = imsg_get_fd(ibuf);
	else
		imsg->fd = -1;

	memcpy(imsg->data, ibuf->r.rptr, datalen);

	if (imsg->hdr.len < av) {
		left = av - imsg->hdr.len;
		memmove(&ibuf->r.buf, ibuf->r.buf + imsg->hdr.len, left);
		ibuf->r.wpos = left;
	} else
		ibuf->r.wpos = 0;

	return (datalen + IMSG_HEADER_SIZE);
}

int
imsg_compose(struct imsgbuf *ibuf, u_int32_t type, u_int32_t peerid,
    pid_t pid, int fd, void *data, u_int16_t datalen)
{
	struct ibuf	*wbuf;

	if ((wbuf = imsg_create(ibuf, type, peerid, pid, datalen)) == NULL)
		return (-1);

	if (imsg_add(wbuf, data, datalen) == -1)
		return (-1);

	wbuf->fd = fd;

	imsg_close(ibuf, wbuf);

	return (1);
}

int
imsg_composev(struct imsgbuf *ibuf, u_int32_t type, u_int32_t peerid,
    pid_t pid, int fd, const struct iovec *iov, int iovcnt)
{
	struct ibuf	*wbuf;
	int		 i, datalen = 0;

	for (i = 0; i < iovcnt; i++)
		datalen += iov[i].iov_len;

	if ((wbuf = imsg_create(ibuf, type, peerid, pid, datalen)) == NULL)
		return (-1);

	for (i = 0; i < iovcnt; i++)
		if (imsg_add(wbuf, iov[i].iov_base, iov[i].iov_len) == -1)
			return (-1);

	wbuf->fd = fd;

	imsg_close(ibuf, wbuf);

	return (1);
}

/* ARGSUSED */
struct ibuf *
imsg_create(struct imsgbuf *ibuf, u_int32_t type, u_int32_t peerid,
    pid_t pid, u_int16_t datalen)
{
	struct ibuf	*wbuf;
	struct imsg_hdr	 hdr;

	datalen += IMSG_HEADER_SIZE;
	if (datalen > MAX_IMSGSIZE) {
		errno = ERANGE;
		return (NULL);
	}

	hdr.type = type;
	hdr.flags = 0;
	hdr.peerid = peerid;
	if ((hdr.pid = pid) == 0)
		hdr.pid = ibuf->pid;
	if ((wbuf = ibuf_dynamic(datalen, MAX_IMSGSIZE)) == NULL) {
		return (NULL);
	}
	if (imsg_add(wbuf, &hdr, sizeof(hdr)) == -1)
		return (NULL);

	return (wbuf);
}

int
imsg_add(struct ibuf *msg, void *data, u_int16_t datalen)
{
	if (datalen)
		if (ibuf_add(msg, data, datalen) == -1) {
			ibuf_free(msg);
			return (-1);
		}
	return (datalen);
}

void
imsg_close(struct imsgbuf *ibuf, struct ibuf *msg)
{
	struct imsg_hdr	*hdr;

	hdr = (struct imsg_hdr *)msg->buf;

	hdr->flags &= ~IMSGF_HASFD;
	if (msg->fd != -1)
		hdr->flags |= IMSGF_HASFD;

	hdr->len = (u_int16_t)msg->wpos;

	ibuf_close(&ibuf->w, msg);
}

void
imsg_free(struct imsg *imsg)
{
	free(imsg->data);
}

int
imsg_get_fd(struct imsgbuf *ibuf)
{
	int		 fd;
	struct imsg_fd	*ifd;

	if ((ifd = TAILQ_FIRST(&ibuf->fds)) == NULL)
		return (-1);

	fd = ifd->fd;
	TAILQ_REMOVE(&ibuf->fds, ifd, entry);
	free(ifd);

	return (fd);
}

int
imsg_flush(struct imsgbuf *ibuf)
{
	while (ibuf->w.queued)
		if (msgbuf_write(&ibuf->w) < 0)
			return (-1);
	return (0);
}

void
imsg_clear(struct imsgbuf *ibuf)
{
	int	fd;

	msgbuf_clear(&ibuf->w);
	while ((fd = imsg_get_fd(ibuf)) != -1)
		close(fd);
}
