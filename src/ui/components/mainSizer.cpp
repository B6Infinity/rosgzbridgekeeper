#include <wx/wx.h>
#include "globals.h"

wxBoxSizer *generateMainSizer(MainFrame *parent)
{
  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

  // Create the first row sizer
  wxBoxSizer *firstRowSizer = new wxBoxSizer(wxHORIZONTAL);

  wxButton *refreshTopicsButton = new wxButton(parent, ID_BTN_REFRESH_TOPICS, "Refresh");



  wxButton *createBridgeButton = new wxButton(parent, ID_BTN_CREATE_BRIDGE, "Create Bridge");
 

  firstRowSizer->Add(refreshTopicsButton, 0, wxALL, 5);
  firstRowSizer->Add(createBridgeButton, 0, wxALL, 5);

  mainSizer->Add(firstRowSizer, 0, wxEXPAND);
  //

  // Create the second row sizer
  wxBoxSizer *secondRowSizer = new wxBoxSizer(wxHORIZONTAL);

  // List of ign topics
  wxBoxSizer *ignListBoxContainer = new wxBoxSizer(wxVERTICAL);

  wxListBox *ignListBox = new wxListBox(parent, ID_LBOX_IGN_TOPICS);
  ignListBox->Append("Press Refresh...");
  wxStaticText *ignHeading = new wxStaticText(parent, wxID_ANY, "IGN Topics");
  ignHeading->SetForegroundColour(wxColour(255, 165, 0)); // Set text color to orange
  ignListBoxContainer->Add(ignHeading, 0, wxALL, 5);
  ignListBoxContainer->Add(ignListBox, 1, wxALL | wxEXPAND, 5);

  // List of ROS topics
  wxBoxSizer *rosListBoxContainer = new wxBoxSizer(wxVERTICAL);

  wxListBox *rosListBox = new wxListBox(parent, ID_LBOX_ROS_TOPICS);
  rosListBox->Append("Press Refresh...");
  wxStaticText *rosHeading = new wxStaticText(parent, wxID_ANY, "ROS Topics");
  rosHeading->SetForegroundColour(wxColour(0, 255, 255)); // Set text color to cyan
  rosListBoxContainer->Add(rosHeading, 0, wxALL, 5);
  rosListBoxContainer->Add(rosListBox, 1, wxALL | wxEXPAND, 5);

  // List of BRIDGED topics
  wxBoxSizer *bridgedListBoxContainer = new wxBoxSizer(wxVERTICAL);

  wxListBox *bridgedListBox = new wxListBox(parent, ID_LBOX_BRIDGE_TOPICS);
  bridgedListBox->Append("Press Refresh...");
  wxStaticText *bridgeHeading = new wxStaticText(parent, wxID_ANY, "Bridged Topics");
  bridgeHeading->SetForegroundColour(wxColour(0, 255, 0)); // Set text color to greeb
  bridgedListBoxContainer->Add(bridgeHeading, 0, wxALL, 5);
  bridgedListBoxContainer->Add(bridgedListBox, 1, wxALL | wxEXPAND, 5);

  // Add stuff to the sizer finally
  secondRowSizer->Add(ignListBoxContainer, 1, wxEXPAND);
  secondRowSizer->Add(bridgedListBoxContainer, 1, wxALL | wxEXPAND, 5);
  secondRowSizer->Add(rosListBoxContainer, 1, wxEXPAND);

  // Add the second row sizer to the main sizer
  mainSizer->Add(secondRowSizer, 1, wxEXPAND);

  return mainSizer;
}
