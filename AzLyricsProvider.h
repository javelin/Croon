/*
 * File  : AzLyricsProvider.h
 * Author: Mark Documento
 */

#ifndef _Croon_AzLyricsProvider_h_
#define _Croon_AzLyricsProvider_h_

struct AzLyricsProvider {
    static const char* Name();
    static String BuildUrl(String title, String artist);
    static bool ExtractLyrics(String content, String& lyrics);

private:
    static const char* UrlFormat();
    static const char* LyricsPattern();
};

#endif
