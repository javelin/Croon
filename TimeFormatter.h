/*
 * File  : TimeFormatter.h
 * Author: Mark Documento
 */

#ifndef _Croon_TimeFormatter_h_
#define _Croon_TimeFormatter_h_

struct TimeFormatter {
    static double CountInDuration(int bpm);
    static String Format(double seconds, bool roundMs=false, char decimal='.');
    static String Ass(double seconds);
    static String Srt(double seconds);
    static String Clock(double seconds);
};

#endif
