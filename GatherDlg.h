/*
 * File  : GatherDlg.h
 * Author: Mark Documento
 */

#ifndef _Croon_GatherDlg_h_
#define _Croon_GatherDlg_h_

class GatherDlg : public ProgressDlg {
public:
    GatherDlg();
    int Run(String videoDir);
    const Vector<Image>& Images() const { return images; }
    
    Event<int, String, String, Image> WhenVideoAdded;
    
private:
    Vector<Image> images;
    Vector<String> paths;
    int curPath;
    bool overwriteTN = false;
    String ffmpeg;
};

#endif
