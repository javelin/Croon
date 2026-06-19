/*
 * File  : DownloadDlg.cpp
 * Author: Mark Documento
 */

#include "Croon.h"

DownloadDlg::DownloadDlg() {
    WhenAbortingProcess = [=] (bool byUser) {
        if (byUser && request.IsOpen()) {
            request.Abort();
        }
    };
    WhenUpdateProgress << [=] {
        static int phase = -1;
        if (phase < request.GetPhase()) phase = request.GetPhase();
        progress.Set(phase, HttpRequest::FINISHED - HttpRequest::BEGIN);
        monitor.SetLabel(request.GetPhaseName());
    };
}

int DownloadDlg::Run(String url, String title, String userAgent) {
    request.Url(url).UserAgent(userAgent).New();
    SetTimeCallback(80, [=] {
        PollProgress();
    }, timerId);
    return RunDlg(title);
}

void DownloadDlg::PollProgress() {
    SetTimeCallback(20, [=] {
        if (request.Do()) {
            UpdateProgress();
            PollProgress();
        }
        else {
            int code = request.GetStatusCode();
            ProcessEnded(code);
            if (request.IsSuccess()) {
                WhenDownloadSuccess(request.GetContent());
                Break(IDOK);
            }
            else {
                Break(IDCANCEL);
            }
            TopWindow::Close();
            Hide();
        }
    }, timerId);
}
