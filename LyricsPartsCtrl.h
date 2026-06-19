#ifndef _Croon_LyricsPartsCtrl_h_
#define _Croon_LyricsPartsCtrl_h_

class LyricsPartsCtrl : public Ctrl {
public:
	// row, col[0..2], newState
    Event<int, int, bool> WhenToggle;

    LyricsPartsCtrl() {
        font = StdFont();
        boldFont = font.Bold();

        // Extra vertical spacing; boxes remain square because width == row height.
        vpad = 12;

        AddFrame(sb);
        sb.WhenScroll = [=] { Refresh(); };
        sb.SetLine(1);

        dragging = false;
        last_row = last_col = -1;

        SetFrame(InsetFrame());
        BackPaint();
    }

    // New: set lyrics + apply box states (row-indexed)
    void SetLyricsAndParts(Vector<String>&& lyrics,
                               const Vector<Tuple<int, bool, bool, bool>>& parts)
    {
        lines = pick(lyrics);
        state.SetCount(lines.GetCount(), 0);

        for(const auto& t : parts) {
            int row = t.a;
            if(row < 0 || row >= lines.GetCount())
                continue;

            // Keep behavior consistent: boxes only exist on lyric rows
            if(!HasLyrics(row))
                continue;

            dword bits = 0;
            if(t.b) bits |= 1u; // box1
            if(t.c) bits |= 2u; // box2
            if(t.d) bits |= 4u; // box3
            state[row] = bits;
        }

        SyncScroll();
        Refresh();
    }
    
    void ClearParts() {
        for (int i = 0; i < state.GetCount(); ++i) {
            state[i] = 0;
        }
    }

    int GetCount() const { return lines.GetCount(); }

    bool GetBox(int row, int col) const {
        if(row < 0 || row >= state.GetCount()) return false;
        if(col < 0 || col >= BOX_COUNT) return false;
        return (state[row] >> col) & 1;
    }

    void SetBox(int row, int col, bool on) {
        if(row < 0 || row >= state.GetCount()) return;
        if(col < 0 || col >= BOX_COUNT) return;
        if(!HasLyrics(row)) return;

        dword mask = (1u << col);
        bool cur = (state[row] & mask) != 0;
        if(cur == on) return;

        if(on) state[row] |= mask;
        else   state[row] &= ~mask;

        RefreshRow(row);
        WhenToggle(row, col, on);
    }

    // U++ native getter: (row_index, box1, box2, box3) for lyric rows only
    Vector<Tuple<int, bool, bool, bool>> GetParts() const
    {
        Vector<Tuple<int, bool, bool, bool>> result;

        for(int row = 0; row < lines.GetCount(); row++) {
            if(!HasLyrics(row))
                continue;

            bool b1 = (state[row] & 1) != 0;
            bool b2 = (state[row] & 2) != 0;
            bool b3 = (state[row] & 4) != 0;

            result.Add(Tuple<int, bool, bool, bool>(row, b1, b2, b3));
        }

        return result;
    }

    // Appearance knobs (optional)
    void SetFont(Font f) {
        font = f;
        boldFont = font.Bold();
        SyncScroll();
        Refresh();
    }

    // Extra vertical spacing per row (pixels). Boxes remain square automatically.
    void SetVerticalPadding(int px) { vpad = max(0, px); SyncScroll(); Refresh(); }

private:
    static constexpr int BOX_COUNT = 2;

    Vector<String> lines;  // pickable / movable in U++
    Vector<dword>  state;  // bit0=box1, bit1=box2, bit2=box3
    Font           font;
    Font           boldFont;

    int            vpad;   // extra vertical spacing per row

    ScrollBar      sb;

    bool dragging;
    int  last_row, last_col;

private:
    bool HasLyrics(int row) const {
        if(row < 0 || row >= lines.GetCount()) return false;
        auto line = TrimBoth(lines[row]);
        return !line.IsEmpty() && line != "-";
    }

    int RowHeight() const {
        return max(font.GetHeight() + vpad, 24);
    }
    
    int HeaderHeight() const {
        return RowHeight();
    }

    int BoxSize() const {
        // Square boxes: width == height == row height
        return RowHeight();
    }

    int BoxesWidth() const {
        return BOX_COUNT * BoxSize();
    }

    void SyncScroll() {
        int rh = RowHeight();
        int total = lines.GetCount() * rh;
        //int page  = max(0, GetSize().cy);
        int page  = max(0, GetSize().cy - HeaderHeight());

        sb.SetTotal(total);
        sb.SetPage(page);
        sb.SetLine(rh);

        int maxpos = max(0, total - page);
        sb.Set(clamp((int)sb, 0, maxpos));
    }

    void RefreshRow(int row) {
        int rh = RowHeight();
        //int y0 = row * rh - sb;
        int y0 = HeaderHeight() + row * rh - sb;
        Refresh(0, y0, GetSize().cx, rh);
    }

    Rect BoxRect(int row, int col) const {
        Size sz = GetSize();
        int rh = RowHeight();
        int bs = BoxSize();
        //int y  = row * rh - sb;
        int y  = HeaderHeight() + row * rh - sb;

        int xL = sz.cx - BoxesWidth();
        return RectC(xL + col * bs, y, bs, rh);
    }

    bool HitTestBox(Point p, int& out_row, int& out_col) const {
        Size sz = GetSize();
        int rh = RowHeight();
        int bs = BoxSize();

        int xL = sz.cx - BoxesWidth();
        if(p.x < xL) return false;

        //int y = p.y + sb;
        int y = p.y - HeaderHeight() + sb;
        if(y < 0) return false;

        int row = y / rh;
        if(row < 0 || row >= lines.GetCount()) return false;
        if(!HasLyrics(row)) return false;

        int local_x = p.x - xL;
        int col = local_x / bs;
        if(col < 0 || col >= BOX_COUNT) return false;

        Rect r = BoxRect(row, col);
        if(!r.Contains(p)) return false;

        out_row = row;
        out_col = col;
        return true;
    }

    void ToggleAt(Point p) {
        int row, col;
        if(!HitTestBox(p, row, col)) {
            last_row = last_col = -1;
            return;
        }

        // Drag behavior: toggle only when entering a different box
        if(row == last_row && col == last_col)
            return;

        last_row = row;
        last_col = col;

        dword mask = (1u << col);
        bool now_on = ((state[row] & mask) == 0);

        if(now_on) state[row] |= mask;
        else       state[row] &= ~mask;

        RefreshRow(row);
        WhenToggle(row, col, now_on);
    }

public:
    virtual void Layout() override {
        SyncScroll();
    }

    virtual void Paint(Draw& w) override;

    virtual void MouseWheel(Point, int zdelta, dword) override {
        sb.Wheel(zdelta);
        Refresh();
    }

    virtual void LeftDown(Point p, dword) override {
        SetFocus();
        dragging = true;
        SetCapture();
        last_row = last_col = -1; // ensure first toggle happens
        ToggleAt(p);
    }

    virtual void MouseMove(Point p, dword) override {
        if(dragging)
            ToggleAt(p);
    }

    virtual void LeftUp(Point, dword) override {
        dragging = false;
        last_row = last_col = -1;
        ReleaseCapture();
    }

    virtual void LostCapture() {
        dragging = false;
        last_row = last_col = -1;
    }
};


#endif
