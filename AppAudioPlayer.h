/*
 * File  : AppAudioPlayer.h
 * Author: Mark Documento
 */

#ifndef _Croon_AppAudioPlayer_h_
#define _Croon_AppAudioPlayer_h_

#include <Core/Core.h>

struct AppAudioPlayer {
    static void InitPlayer();
    static void DeInitPlayer();
    static bool Open(const Upp::String& filename);
    static bool Close();
    static bool Reopen();
    static bool Pause();
    static bool Play();
    static bool Seek(double seconds);
    static bool IsPlaying();
    static bool IsOpen();
    static double Duration();
    static double Position();
};

#endif
