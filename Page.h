/*
 * File  : Page.h
 * Author: Mark Documento
 */

#ifndef _Croon_Page_h_
#define _Croon_Page_h_

class Page : public Ctrl {
public:
    Page() : Page("") {}
    Page(String name) : pageName(name), enableNext(false), enablePrev(true) {
        prevBtn.SetLabel("< Back").Disable();
        prevBtn.Hide();
        prevBtn << [=] { WhenPreviousPage(); };
        nextBtn.SetLabel("Next >").Disable();
        nextBtn.Hide();
        nextBtn << [=] { WhenNextPage(); };
        WantFocus(true);
    }
    Button& GetPrevButton() { return prevBtn; }
    Button& GetNextButton() { return nextBtn; }
    virtual const String& GetPageName() const { return pageName; }
    virtual void HidePage() {
        Disable();
        Hide();
        PageHidden();
    }
    virtual void ShowPage() {
        Show();
        Enable();
        PageShown();
    }
    virtual void PageShown() {
        Populate();
        ShowButtons();
        WhenShown();
    }
    virtual void PageHidden() {
        SaveData();
        HideButtons();
        WhenHidden();
    }
    virtual void Reset() {};
    virtual void Populate() {}
    virtual void SaveData() {}
    virtual void HideButtons() {
        prevBtn.Disable();
        prevBtn.Hide();
        nextBtn.Disable();
        nextBtn.Hide();
    }
    virtual void ShowButtons() {
        prevBtn.Enable(enablePrev);
        prevBtn.Show();
        nextBtn.Enable(enableNext);
        nextBtn.Show();
    }
    
    Event<> WhenPreviousPage;
    Event<> WhenNextPage;
    Event<> WhenShown;
    Event<> WhenHidden;
    
protected:
    String pageName;
    Button prevBtn;
    Button nextBtn;
    bool enableNext;
    bool enablePrev;
};

#endif

