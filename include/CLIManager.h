#include <stdio.h>
#include <cstdio>
#include <string>
#include <map>

// std::map<std::string, std::string> db;

std::string executeCommand(const char *command);
int loadDB();
std::string getEquivalentMessageType(const char *mtype, const bool getign);