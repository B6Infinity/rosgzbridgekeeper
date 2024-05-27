
#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

map<std::string, std::string> db;

void loadDB()
{
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
        cout << "Failed to open DB.csv" << endl;
    }

    cout << db.size() << endl;
}

std::string getEquivalentMessageType(const char *mtype, const bool ign = false)
{
    if (ign)
    {
        for (const auto &pair : db)
        {
            if (pair.second == mtype)
            {
                return pair.first;
            }
        }
    }

    return db[mtype];
}

int main()
{

    loadDB();

    string s = getEquivalentMessageType("gz.msgs.Clock", true);
    cout << s << endl;

    return 0;
}