#include <stdio.h>
#include <cstdio>
#include <string>
#include <wx/wx.h>
#include "globals.h"
#include "App.h"
#include "MainFrame.h"

const char *APP_NAME = "RosGzBridgeKeeper";

bool App::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show(true);

    int screenWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    int frameWidth = frame->GetSize().GetWidth();
    int xPos = screenWidth - frameWidth - 300;
    frame->SetPosition(wxPoint(xPos, 0));

    frame->SetClientSize(600, 350);
    return true;
}