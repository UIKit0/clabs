
/************************************************************
 * cp: audio.h
 *
 * Licensed under GPLv2.
 * ABSOLUTELY NO WARRANTY!
 *
 * Copyright (C) eXerigumo Clanjor (哆啦比猫/兰威举).
 ************************************************************/

#ifndef __AUDIO_H
#define __AUDIO_H

#include "../core/core.h"

extern u32 audio_bitrate;
extern u8  audio_playing;

void audio_open();
void audio_close();
void audio_play();
void audio_stop();

#endif

