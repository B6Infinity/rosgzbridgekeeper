#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    void OnHello(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnHelp(wxCommandEvent &event);

    void showLoadingTopics(wxCommandEvent &event);
    void refreshTopics(wxCommandEvent &event);
    void setVersion(wxCommandEvent &event);
};