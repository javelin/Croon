/*
 * File  : ConvertDlg.h
 * Author: Mark Documento
 */

#ifndef _Croon_ConvertDlg_h_
#define _Croon_ConvertDlg_h_

class ConvertDlg : public ProgressDlg {
public:
    ConvertDlg();
    int Run(String audioPath);
    String GetConvertedFile() const { return outputPath; }
    double GetDurationn() const { return duration; }
    
private:
    void StartConversion();
    double ComputeTS(const Vector<String>& vs);

private:
    String ffmpeg;
    String output;
    String audioPath;
    String outputPath;
    double duration = 0.0f;
    String renderTime;
    int progressVal = 0;
    bool gotDuration = false;
    bool done = false;
};

#endif
