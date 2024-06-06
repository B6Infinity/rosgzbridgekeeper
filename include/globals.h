#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <string>
#include <thread>
#include <wx/wx.h>

extern const char *APP_NAME;
extern std::vector<std::string> gazebosim_topics;
extern std::vector<std::string> ros_topics;
extern std::vector<std::string> bridged_topics;

extern std::vector<std::thread> bridge_threads;

// IDs
enum
{
    ID_Hello = 1,
    ID_BTN_REFRESH_TOPICS = 2,
    ID_LBOX_IGN_TOPICS = 3,
    ID_LBOX_ROS_TOPICS = 4,
    ID_LBOX_BRIDGE_TOPICS = 5,
    ID_BTN_CREATE_BRIDGE = 6,
    ID_BTN_GZ_VERSION = 7,
};

// Values
extern std::string GZ_VERSION;


#endif // GLOBALS_H