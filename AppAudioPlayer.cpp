/*
 * File  : AppAudioPlayer.cpp
 * Author: Mark Documento
 */

#include "AppAudioPlayer.h"

using namespace Upp;

#include "SDLMixerAudioPlayer.h"

void AppAudioPlayer::InitPlayer() {
    SDLMixerAudioPlayer::InitPlayer();
}

void AppAudioPlayer::DeInitPlayer() {
    SDLMixerAudioPlayer::DeInitPlayer();
}

bool AppAudioPlayer::Open(const Upp::String& filename) {
    return SDLMixerAudioPlayer::GetPlayer().Open(filename);
}

bool AppAudioPlayer::Close() {
    return SDLMixerAudioPlayer::GetPlayer().Close();
}

bool AppAudioPlayer::Reopen() {
    return SDLMixerAudioPlayer::GetPlayer().Reopen();
}

bool AppAudioPlayer::Pause() {
    return SDLMixerAudioPlayer::GetPlayer().Pause();
}

bool AppAudioPlayer::Play() {
    return SDLMixerAudioPlayer::GetPlayer().Play();
}

bool AppAudioPlayer::Seek(double seconds) {
    return SDLMixerAudioPlayer::GetPlayer().Seek(seconds);
}

bool AppAudioPlayer::IsPlaying() {
    return SDLMixerAudioPlayer::GetPlayer().IsPlaying();
}

bool AppAudioPlayer::IsOpen() {
    return SDLMixerAudioPlayer::GetPlayer().IsOpen();
}

double AppAudioPlayer::Duration() {
    return SDLMixerAudioPlayer::GetPlayer().Duration();
}

double AppAudioPlayer::Position() {
    return SDLMixerAudioPlayer::GetPlayer().Position();
}
