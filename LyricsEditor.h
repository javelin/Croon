/*
 * File  : LyricsEditor.h
 * Author: Mark Documento
 */

#ifndef _Croon_LyricsEditor_h_
#define _Croon_LyricsEditor_h_

class LyricsEditorLine : public ParentCtrl, public Pte<LyricsEditorLine> {
public:
    LyricsEditorLine(const TimeLyrics& line);
    Event<> WhenEnter;
    Event<Vector<EditField::Highlight>&> WhenHighlight;
    
private:
    EditString lineEd;
};

class LyricsEditor : public Ctrl {
public:
    LyricsEditor();
    void Populate();
    
private:
    //ListCtrl lyricsList;
    ArrayCtrl lyricsList;
    EditString editor;
};

#endif
