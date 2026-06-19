/*
 * File  : TimingLine.h
 * Author: Mark Documento
 */

#ifndef _Croon_TimingLine_h_
#define _Croon_TimingLine_h_

class TimingLine : public Ctrl {
public:
    TimingLine() :
        blank(true), decor(""), lyrics(""), position(0.0f), duration(0.0f), withButtons(false)
        { Initialize(withButtons); }
    TimingLine(const TimingLine& tl) :
        blank(tl.blank), decor(""), lyrics(tl.decor + tl.lyrics), position(tl.position),
        duration(tl.duration), withButtons(tl.withButtons)
        { Initialize(withButtons); }
    TimingLine(const String& lyrics, double position) :
        blank(false), decor(""), lyrics(lyrics), position(position),
        duration(0.0f), withButtons(true)
        { Initialize(withButtons); }
    TimingLine(const String& lyrics, double position, bool withButtons) :
        blank(false), decor(""), lyrics(lyrics), position(position),
        duration(0.0f), withButtons(withButtons)
        { Initialize(withButtons); }
    void Paint(Draw& w) override;
    void LeftDouble(Point pos, dword) override;
    void LeftUp(Point pos, dword) override;
    void Initialize(bool withButtons);
    double GetPosition() const { return position; }
    String GetLyrics() const { return decor + lyrics; }
    void SetPosition(double position);
    void SetDuration(double duration) { this->duration = duration; }
    void DisplayTime();
    void Normal();
    void Highlight1();
    void Highlight2();
    void EnableTimeBtns(bool enable=true);
    void ResetTiming();
    
    Event<> WhenEditingLyrics;
    Event<> WhenInterrupt;
    Event<> WhenLeftClicked;
    Event<String> WhenLyricsEdited;
    Event<> WhenRetime;
    Gate<double> WhenSetPosition;
    Event<> WhenTimeButtonsDisabled;
    
public:
    Label lyricsLbl;
    Label timeLbl;
    Button decSecBtn;
    Button incSecBtn;
    Button retimeBtn;
    MarginFrame frame;
    
public:
    static const Color NColor;
    static const Color H1Color;
    static const Color H2Color;
    
private:
    bool blank;
    String decor;
    String lyrics;
    double position;
    double duration;
    bool withButtons;
    Color bgColor;
};

#endif
