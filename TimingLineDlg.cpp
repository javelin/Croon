/*
 * File  : TimingLineDlg.cpp
 * Author: Mark Documento
 */

#include "Croon.h"

TimingLineDlg::TimingLineDlg(String decor, String lyrics) {
    CtrlLayout(*this, "Edit Lyrics");
    CenterOwner();
    
    decorEd.SetData(decor);
    lyricsEd.SetData(lyrics);
    
    okBtn << [=] {
        Break(IDOK);
        Close();
    };
    
    cancelBtn << [=] {
        Break(IDCANCEL);
        Close();
    };
}