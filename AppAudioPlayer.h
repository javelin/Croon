/*
 * File  : AppAudioPlayer.h
 * Author: Mark Documento
 */

#ifndef _Croon_AppAudioPlayer_h_
#define _Croon_AppAudioPlayer_h_

#include "SDLMixerAudioPlayer.h"

struct AppAudioPlayer {
    static void InitPlayer() { SDLMixerAudioPlayer::InitPlayer(); }
    static void DeInitPlayer() { SDLMixerAudioPlayer::DeInitPlayer(); }
    static SDLMixerAudioPlayer& GetPlayer() { return SDLMixerAudioPlayer::GetPlayer(); }
};

#endif
