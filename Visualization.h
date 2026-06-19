/*
 * File  : Visualization.h
 * Author: Mark Documento
 */

#ifndef _Croon_Visualization_h_
#define _Croon_Visualization_h_

struct Visualization {
    static String Filter(String viz, String assFn, bool preview) {
        if (viz == "@@freqs") return ShowFreqs(assFn, preview);
        else if (viz == "@@spectrum") return ShowSpectrum(assFn, preview);
        else if (viz == "@@vectorscopedot") return AVectorScopeDot(assFn, preview);
        else if (viz == "@@vectorscopeline") return AVectorScopeLine(assFn, preview);
        else if (viz == "@@waves") return ShowWaves(assFn, preview);
        return String::GetVoid();
    }
    
    static Image Thumbnail(String viz) {
        if (viz == "@@freqs") return CroonImg::VizFreqs();
        else if (viz == "@@spectrum") return CroonImg::VizSpectrum();
        else if (viz == "@@vectorscopedot") return CroonImg::VizVectorScopeDot();
        else if (viz == "@@vectorscopeline") return CroonImg::VizVectorScopeLine();
        else if (viz == "@@waves") return CroonImg::VizWaves();
        return CroonImg::GrayMic256();
    }
    
    static String Reso(bool preview, char sep) {
        return Format("%d%c%d", preview ? 320:1926, sep, preview ? 180:1080);
    }
    
    static String Reso(bool preview, int h, char sep) {
        return Format("%d%c%d", preview ? 320:1926, sep, h);
    }
    
    static String ShowFreqs(String assFn, bool preview) {
        return Format("[1:a]showfreqs=s=%s:mode=line:colors=red[vis]; "
                        "[0:v][vis]overlay=0:0[bg]; "
                        "[bg]subtitles=%s",
                        Reso(preview, 'x'),
                        assFn);
    }
    
    static String ShowSpectrum(String assFn, bool preview) {
        return Format("[1:a]showspectrum=s=%s:mode=combined:color=intensity[vis]; "
                        "[0:v][vis]overlay=0:0[bg]; "
                        "[bg]subtitles=%s",
                        Reso(preview, 'x'),
                        assFn);
    }
    
    static String APhaseMeter(String assFn, bool preview) {
        return Format("[1:a]aphasemeter=s=%s[vis]; "
                        "[0:v][vis]overlay=0:0[bg]; "
                        "[bg]subtitles=%s",
                        Reso(preview, 'x'),
                        assFn);
    }
    
    static String AVectorScopeDot(String assFn, bool preview) {
        return Format("[1:a]avectorscope=s=%s:mode=lissajous_xy:draw=dot[vis]; "
                        "[0:v][vis]overlay=0:0[bg]; "
                        "[bg]subtitles=%s",
                        Reso(preview, 'x'),
                        assFn);
    }
    
    static String AVectorScopeLine(String assFn, bool preview) {
        return Format("[1:a]avectorscope=s=%s:mode=lissajous_xy:draw=line[vis]; "
                        "[0:v][vis]overlay=0:0[bg]; "
                        "[bg]subtitles=%s",
                        Reso(preview, 'x'),
                        assFn);
    }
    
    static String ShowWaves(String assFn, bool preview) {
        return Format("[1:a]showwaves=s=%s:mode=line:colors=cyan[wave]; "
                        "[wave]scale=%s[wave_scaled]; "
                        "[0:v][wave_scaled]overlay=0:(H-h)/2[bg]; "
                        "[bg]subtitles=%s",
                        Reso(preview, preview ? 50:300, 'x'),
                        Reso(preview, preview ? 200:1204, ':'),
                        assFn);
    }
};

#endif
