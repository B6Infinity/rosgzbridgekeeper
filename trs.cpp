
#include <iomanip>
#include <iostream>

using namespace std;

std::string getEquivalentMessageType(const char *mtype, const bool ign = false)
{
    if (ign)
    {
        return "bruh";
    }
    
    return mtype;
}

int main()
{
    string s = getEquivalentMessageType("elo");
    
    cout << s << endl;
    
    
    return 0;
}