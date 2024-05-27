#include <wx/wx.h>
#include "globals.h"

wxMenuBar* generateMenuBar()
{

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello\tCtrl+H",
                     "This is a simple bridge manager GUI for ROS2 and Gazebo.");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_HELP, "&Help\tF1", "Get help regarding this software.");
    menuHelp->Append(wxID_ABOUT);

    // MENU BAR
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    return menuBar;
}
