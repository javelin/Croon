/*
 * File  : VidThumbnail.h
 * Author: Mark Documento
 */

#ifndef _Croon_VidThumbnail_h_
#define _Croon_VidThumbnail_h_

class MyImageCtrl : public ImageCtrl {
public:
    void LeftUp(Point p, dword keyflags) override { WhenPushed(); }
    Event<> WhenPushed;
};

class VidThumbnail : public Ctrl, public Pte<VidThumbnail> {
public:
    VidThumbnail();
    VidThumbnail(String path, Image image);
    VidThumbnail(const VidThumbnail& vt);
    void SetSelected(bool set=true);
    String GetPath() const { return path; }
    void Layout() override;
    
    Event<String> WhenSelected;
    
public:
    static const int Width;
    static const int Height;
    
private:
    void Initialize();
    
private:
    String path;
    Image image;
    Button button;
    MyImageCtrl imgCtrl;
    Option selected;
};

#endif
