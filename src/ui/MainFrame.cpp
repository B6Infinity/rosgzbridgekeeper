#include <stdio.h>
#include <cstdio>
#include <string>
#include <wx/wx.h>

#include "globals.h"
#include "MainFrame.h"
#include "CLIManager.h"

#include "components/mainSizer.cpp"
#include "components/menuBar.cpp"

std::vector<std::string> ign_topics;
std::vector<std::string> ros_topics;
std::vector<std::string> bridged_topics;

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, APP_NAME)
{
    MainFrame *mainFrame = this;
    // Set UI
    SetMenuBar(generateMenuBar());
    CreateStatusBar();
    SetStatusText(wxString::Format("Welcome to %s!", APP_NAME));

    SetSizer(generateMainSizer(this));

    // ________________________ UI DONE ___________________________

    // Bind Event Handlers
    Bind(wxEVT_MENU, &MainFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnHelp, this, wxID_HELP);
    Bind(wxEVT_BUTTON, &MainFrame::showLoadingTopics, this, ID_BTN_REFRESH_TOPICS);

    /*It can be convenient to use unnamed lambdas instead of functions for event handlers, especially for such short functions. Here, for example, we could replace the handler above with just*/
    // Bind(wxEVT_MENU, [=](wxCommandEvent&) { wxLogMessage("Hello from a lambda!"); }, ID_Hello);
}

// Basic Event Handlers
void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("Konnichiwa Asshole", "ABout yeh bitch", wxOK | wxICON_INFORMATION);
}
void MainFrame::OnHelp(wxCommandEvent &event)
{
    wxMessageBox("Info on how to use this...", "This is pretty simple", wxOK | wxICON_QUESTION);
}

void MainFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Tis loggin time");
}

// Functionality Event Handlers

void MainFrame::showLoadingTopics(wxCommandEvent &event)
{
    std::cout << "Look\n";
    SetStatusText("Fetching Topics...");

    wxBusyCursor busyCursor;
    wxWindowDisabler disabler;

    refreshTopics(event);
}

void MainFrame::refreshTopics(wxCommandEvent &event)
{
    using namespace std;

    // Fetch and Sort Topics
    {
        cout << "Fetching IGN Topics..." << endl;
        string ign_topics_str = executeCommand("ign topic -l");

        ign_topics.clear();
        string old_word = "";
        for (size_t i = 0; i < ign_topics_str.length(); i++)
        {
            char c = ign_topics_str[i];
            if (c != '\n')
            {
                old_word += c;
            }
            else
            {
                ign_topics.push_back(old_word);
                old_word = "";
            }
        }
        if (old_word.length() > 1)
        {
            ign_topics.push_back(old_word);
        }

        // ROS Topics ----------------
        cout << "Fetching ROS Topics..." << endl;
        string ros_topics_str = executeCommand("ros2 topic list");

        ros_topics.clear();
        old_word = "";
        for (size_t i = 0; i < ros_topics_str.length(); i++)
        {
            char c = ros_topics_str[i];
            if (c != '\n')
            {
                old_word += c;
            }
            else
            {
                ros_topics.push_back(old_word);
                old_word = "";
            }
        }
        if (old_word.length() > 1)
        {
            ros_topics.push_back(old_word);
        }
        std::string().swap(old_word); // Free the memory

        // Bridged Topics ----------------
        cout << "Seperating Bridged Topics..." << endl;
        bridged_topics.clear();
        // Sorry but I lack the skill to get any better than O(n^2)
        for (const string &itopic : ign_topics)
        {
            for (const string &rtopic : ros_topics)
            {
                if (rtopic == itopic)
                {
                    bridged_topics.push_back(itopic);

                    break;
                }
            }
        }

        std::cout << "\n All bridged topics: \n";
        for (const string btopic : bridged_topics)
        {
            std::cout << btopic << std::endl;
        }
    }

    // Update UI ---------------------
    {
        wxListBox *ignListBox = dynamic_cast<wxListBox *>(FindWindowById(ID_LBOX_IGN_TOPICS));
        wxListBox *rosListBox = dynamic_cast<wxListBox *>(FindWindowById(ID_LBOX_ROS_TOPICS));
        wxListBox *bridgedListBox = dynamic_cast<wxListBox *>(FindWindowById(ID_LBOX_BRIDGE_TOPICS));


        cout << "Updating UI\n";
        // IGN Topics ----------------
        ignListBox->Clear();
        for (const string &topic : ign_topics)
            ignListBox->Append(topic);

        // IGN List Box event handlers
        ignListBox->Bind(wxEVT_COMMAND_LISTBOX_SELECTED, [=](wxCommandEvent& event) {
            wxString selectedTopic = ignListBox->GetStringSelection();

            int rlbIndex = rosListBox->FindString(selectedTopic);
            if (rlbIndex != wxNOT_FOUND) {
                rosListBox->SetSelection(rlbIndex);
            }else{
                rosListBox->SetSelection(-1);
            }

            int blbIndex = bridgedListBox->FindString(selectedTopic);
            if (blbIndex != wxNOT_FOUND)
            {
                bridgedListBox->SetSelection(blbIndex);
            }else{
                bridgedListBox->SetSelection(-1);
            }
            

        });

        // Double Click to get topic info
        ignListBox->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event){
            wxString topic = ignListBox->GetStringSelection();
            string info_text = executeCommand(("ign topic -i -t " + topic.ToStdString()).c_str());
            wxMessageBox(info_text, topic.ToStdString(), wxOK | wxICON_INFORMATION);
        });





        // ROS Topics

        rosListBox->Clear();

        for (const string &topic : ros_topics)
        {
            rosListBox->Append(topic);
        }

        // rosListBox Event Handlers -----------

        rosListBox->Bind(wxEVT_COMMAND_LISTBOX_SELECTED, [=](wxCommandEvent& event) {
            wxString selectedTopic = rosListBox->GetStringSelection();

            int ilbIndex = ignListBox->FindString(selectedTopic);
            if (ilbIndex != wxNOT_FOUND) {
                ignListBox->SetSelection(ilbIndex);
            }else{
                ignListBox->SetSelection(-1);
            }

            int blbIndex = bridgedListBox->FindString(selectedTopic);
            if (blbIndex != wxNOT_FOUND)
            {
                bridgedListBox->SetSelection(blbIndex);
            }else{
                bridgedListBox->SetSelection(-1);
            }
        });
        // Double Click to get topic info
        rosListBox->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event){
            wxString topic = rosListBox->GetStringSelection();
            string info_text = executeCommand(("ros2 topic info " + topic.ToStdString()).c_str());
            wxMessageBox(info_text, topic.ToStdString(), wxOK | wxICON_INFORMATION);

            std::cout << getEquivalentMessageType("sensor_msgs/msg/LaserScan", true) << std::endl;
        });


        // Bridged Topics

        bridgedListBox->Clear();

        for (const string &topic : bridged_topics)
            bridgedListBox->Append(topic);
        bridgedListBox->SetForegroundColour(wxColour(0, 255, 0)); // Set text color to green

        bridgedListBox->Bind(wxEVT_COMMAND_LISTBOX_SELECTED, [=](wxCommandEvent& event) {
            wxString selectedTopic = bridgedListBox->GetStringSelection();

            int ilbIndex = ignListBox->FindString(selectedTopic);
            if (ilbIndex != wxNOT_FOUND) {
                ignListBox->SetSelection(ilbIndex);
            }else{
                ignListBox->SetSelection(-1);
            }

            int rlbIndex = rosListBox->FindString(selectedTopic);
            if (rlbIndex != wxNOT_FOUND)
            {
                rosListBox->SetSelection(rlbIndex);
            }else{
                rosListBox->SetSelection(-1);
            }
        });

        // Double Click to get topic info
        bridgedListBox->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event){
            wxString topic = bridgedListBox->GetStringSelection();
            string info_text = executeCommand(("ros2 topic info " + topic.ToStdString()).c_str());
            wxMessageBox(info_text, topic.ToStdString(), wxOK | wxICON_INFORMATION);
        });
    }

    SetStatusText("Done!");
}
