/*
 * File  : WizardDlg.h
 * Author: Mark Documento
 */

#ifndef _Croon_WizardDlg_h_
#define _Croon_WizardDlg_h_

class WizardDlg : public WithCroonWizardLayout<TopWindow> {
public:
    WizardDlg();
    int Run(String tempAudioPath, double duration, String origAudioFilePath);
    void Close() override;
    
public:
    static const int maxPages = 3;
    
private:
    String tempAudioPath;
    Page* pages[maxPages];
    int currPage;
};

#endif
