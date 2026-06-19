/*
 * File  : TimingDlg.cpp
 * Author: Mark Documento
 */

#include "Croon.h"

TimingDlg::TimingDlg() : timingCtrl(lineHeight) {
    Title("Time Lyrics").NoZoomable().Sizeable().SetMinSize(Size(Zx(400), Zy(220)));
    SetRect(0, 0, Zx(640), Zy(800));
    CenterOwner();
    *this << timingCtrl.HSizePosZ(10, 10).VSizePosZ(45, 60)
            << playBtn.Ok().SetLabel("Play").LeftPosZ(10, 50).TopPosZ(10, 30)
            << timeLbl.SetLabel("00:00.000/00:00.000").AlignRight().RightPosZ(10, 110).TopPosZ(10, 35)
            << sliderCtrl.MinMax(0, 100).Step(1).Jump().HSizePosZ(70, 135).TopPosZ(20, 12)
            << adjustDec.SetLabel("-").LeftPosZ(10, 25).BottomPosZ(15, 25)
            << adjustEd.SetInc(100).MinMax(1, 1000).AlignRight().LeftPosZ(35, 60).BottomPosZ(15, 25)
            << adjustInc.SetLabel("+").LeftPosZ(95, 25).BottomPosZ(15, 25)
            << adjustLbl.SetLabel("Adjust All Timed").LeftPosZ(125, 100).BottomPosZ(15, 25)
            << adjustDec.SetLabel("-").LeftPosZ(10, 25).BottomPosZ(15, 25)
            << adjustEd.SetInc(100).MinMax(1, 1000).AlignRight().LeftPosZ(35, 60).BottomPosZ(15, 25)
            << adjustInc.SetLabel("+").LeftPosZ(95, 25).BottomPosZ(15, 25)
            << adjustLbl.SetLabel("Adjust All Timed").LeftPosZ(125, 100).BottomPosZ(15, 25)
            << closeBtn.Cancel().SetLabel("Close").RightPosZ(10, 100).BottomPosZ(15, 25);
            
    sliderCtrl.WhenSlideFinish = [=] {
        double value = (double)sliderCtrl.GetData();
        auto& player = MusicPlayer::GetPlayer();
        player.Seek(value/100.0f*player.Duration());
    };
    timingCtrl.WhenDoneTiming << [=] {
    };
    timingCtrl.WhenInterrupt << [=] {
        if (MusicPlayer::GetPlayer().IsPlaying()) {
            TogglePlay();
        }
    };
    timingCtrl.WhenPlayAt << [=] (auto position) {
        auto& player = MusicPlayer::GetPlayer();
        player.Seek(position);
        if (!player.IsPlaying()) {
            TogglePlay();
        }
    };
    timingCtrl.WhenDirty << [=] { dirty = true; };
    timingCtrl.WhenTiming << [=] (auto _) {
        return MusicPlayer::GetPlayer().IsPlaying();
    };
    
    playBtn << [=] {
        TogglePlay();
        timingCtrl.SetFocus();
    };
    
    sliderCtrl.WhenSlideFinish = [=] {
        double value = (double)sliderCtrl.GetData();
        auto& player = MusicPlayer::GetPlayer();
        player.Seek(value/100.0f*player.Duration());
    };
    
    adjustEd.SetData(500);
    adjustDec << [=] {
        timingCtrl.Adjust(-((double)adjustEd.GetData()));
    };
    adjustInc << [=] {
        timingCtrl.Adjust((double)adjustEd.GetData());
    };
    
    closeBtn << [=] { Close(); };
}

void TimingDlg::Close() {
    MusicPlayer::GetPlayer().Pause();
    if (PromptYesNoCancel("Save changes and close?") == 1) {
        data->timedLyrics = timingCtrl.GetTimedLyrics();
        data->rawLyrics = TimedLyricsToRaw(data->timedLyrics);
        data->timed = timingCtrl.GetTimed();
        TopWindow::Close();
    }
}

bool TimingDlg::Key(dword key, int count) {
    switch (key) {
    case K_P:
        TogglePlay();
        return true;
    }
    return Ctrl::Key(key, count);
}

void TimingDlg::PollProgress() {
    SetTimeCallback(100, [=] {
        auto& player = MusicPlayer::GetPlayer();
        if (!player.IsOpen()) {
            playBtn.SetLabel("Play");
            player.Reopen();
            SetProgress(player.Duration());
            timingCtrl.PlayBackDone();
        }
        else if (player.IsPlaying()) {
            SetProgress(player.Position());
            PollProgress();
        }
    }, timerId);
}

void TimingDlg::Populate() {
    timeLbl.SetLabel("00:00.000/" + FormatTime(data->duration));
    timingCtrl.SetTimedLyrics(data->timedLyrics, data->duration);
    timingCtrl.SetFocus();
}

void TimingDlg::SetProgress(double position) {
    auto& player = MusicPlayer::GetPlayer();
    auto duration = player.Duration();
    if (duration > 0.0f) {
        sliderCtrl.SetData((int)(position/duration*100.0));
        timingCtrl.SetMusicPosition(position, duration);
    }
    else {
        sliderCtrl.SetData(0);
        timingCtrl.SetMusicPosition(0.0f, 0.0f);
    }
    timeLbl.SetLabel((FormatTime(position).Mid(3) + "/") + FormatTime(duration).Mid(3));
}

void TimingDlg::TogglePlay() {
    auto& player = MusicPlayer::GetPlayer();
    if (!player.IsPlaying()) {
        timingCtrl.ReadyForTiming();
        player.Play();
        PollProgress();
        playBtn.SetLabel("Pause");
    }
    else {
        player.Pause();
        playBtn.SetLabel("Play");
    }
}
