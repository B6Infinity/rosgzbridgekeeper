#include <wx/wx.h>

class App : public wxApp
{
public:
    bool OnInit() override;

    // void refreshTopics();
};

// Wx Macro that looks for the entry
wxIMPLEMENT_APP(App);