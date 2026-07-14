/*
 * File  : SaveProjectDlg.h
 * Author: Mark Documento
 */

#ifndef _Croon_SaveProjectDlg_h_
#define _Croon_SaveProjectDlg_h_

class SaveProjectDlg : public ProgressDlg {
public:
    SaveProjectDlg();
    int Run(String savePath, KarData& data);
    int Run(KarData& data);
    void Close() override;
    
private:
    void StartSave();
    void AttachCroonInfo();
    
private:
    KarData* data;
    String ffmpeg;
    String tempFilename;
    bool attaching = false;
    int progressVal = 0;
};

#endif
