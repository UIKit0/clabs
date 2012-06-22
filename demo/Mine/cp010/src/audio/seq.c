
/************************************************************
 * cp: seq.c
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#include "seq.h"
#include "audio.h"
#include "music.h"
#include <stdlib.h>
#include <math.h>

typedef struct Sequence
{
	u16 * score;
	u32   instpos;
	float last_time;
	float w;
	u16   notepos;
	u8    inst;
}
Sequence;

static Sequence * seqs;

static void reset_note(Sequence * seq);
static float seq_pull(Sequence * seq, float time);




void seq_init()
{
	seqs = calloc(music_nscore, sizeof(*seqs));

	int i;
	for (i=0; i<music_nscore; i++) {
		seqs[i].score = music_scores[i];
		seqs[i].last_time = -music_mspr-1;
		reset_note(&seqs[i]);
	}
}

float seq_mix_all(float time)
{
	float x = 0.0f;
	int i;
	for (i=0; i<music_nscore; i++)
		x += seq_pull(&seqs[i], time);
	return x * music_amplify / music_nscore;
}




static void reset_note(Sequence * seq)
{
	u16 note  = seq->score[seq->notepos];
	if (note == 0xFFFF) return;
	seq->inst = note & 0xFF;
	u8 octave = note >> 12;
	note = (note >> 8) & 0x0F;
	seq->instpos = 0;

	if (octave) {
		float freq = 300 * pow(2, octave + note/12.0f - 42.0f/12.0f);
		seq->w = 1000.0f * 2*PI * freq / audio_bitrate;
	}
	else seq->w = 0.0f;	// stop note
}

static float seq_pull(Sequence * seq, float time)
{
	// When the sequence ends...
	if (seq->score[seq->notepos] == 0xFFFF)
		return 0.0f;

	// When it's time to jump to the next row...
	if (time - seq->last_time >= music_mspr) {
		seq->last_time += music_mspr;

		// Not a blank row...
		if (seq->score[++seq->notepos])
			reset_note(seq);
	}

	// Play the instrument!
	return music_insts[seq->inst](seq->w * seq->instpos++);
}

