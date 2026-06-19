/*
 * File  : MusicPlayer.h
 * Author: Mark Documento
 */

#ifndef _Croon_MusicPlayer_h_
#define _Croon_MusicPlayer_h_

#include "AudioPlayer.h"
#include "SDLMixerAudioPlayer.h"
typedef AudioPlayer<SDLMixerAudioPlayer> MusicPlayer;

#endif
