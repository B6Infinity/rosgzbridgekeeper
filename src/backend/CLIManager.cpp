#include <stdio.h>
#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "CLIManager.h"

std::string executeCommand(const char *command)
{

    std::cout << "Executing `" << command << "` ..." << std::endl;
    std::string result;
    FILE *pipe = popen(command, "r");
    if (pipe)
    {
        char buffer[128];
        while (!feof(pipe))
        {
            if (fgets(buffer, 128, pipe) != nullptr)
                result += buffer;
        }
        pclose(pipe);
    }
    return result;
}

std::map<std::string, std::string> db;

int loadDB()
{
    using namespace std;
    ifstream file("DB.csv");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string key, value;
            getline(ss, key, ',');
            getline(ss, value, ',');
            db[key] = value;
        }
        file.close();
    }
    else
    {
        std::cout << "Failed to open DB.csv" << std::endl;
    }

    // std::cout << db.size() << std::endl;

    return db.size();
}

std::string getEquivalentMessageType(const char *mtype, const bool getign = true)
{

    std::string modifiedMtype = mtype;
    std::string searchString = "ignition";
    std::string replaceString = "gz";
    size_t pos = modifiedMtype.find(searchString);
    while (pos != std::string::npos)
    {
        modifiedMtype.replace(pos, searchString.length(), replaceString);
        pos = modifiedMtype.find(searchString, pos + replaceString.length());
    }
    mtype = modifiedMtype.c_str();

    if (db.size() == 0)
    {
        std::cout << "Loading message types from DB.csv" << std::endl;
        loadDB();
    }

    if (!getign)
    {
        for (const auto &pair : db)
        {
            if (pair.second == mtype)
            {
                return pair.first;
            }
        }
        return "";
    }

    return db[mtype];
}

