#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> get_ros_topics(){
    string ros_topics_str = "/hello\n/hello/stuff\n/block/cmd_vel";

    vector<string> words;

    string old_word = "";
    for (size_t i = 0; i < ros_topics_str.length(); i++)
    {
        char c = ros_topics_str[i];
        if (c != '\n')
        {
            old_word += c;
        }
        else
        {
            cout << old_word << ", ";
            words.push_back(old_word);
            old_word = "";

        }
    }
    cout << old_word << endl;
    words.push_back(old_word);

    return words;
}

std::vector<std::string> get_ign_topics(){
    string ros_topics_str = "/hello\n/hello/stuffedup\n/block/cmd_vel/tf\n/block/cmd_vel";

    vector<string> words;

    string old_word = "";
    for (size_t i = 0; i < ros_topics_str.length(); i++)
    {
        char c = ros_topics_str[i];
        if (c != '\n')
        {
            old_word += c;
        }
        else
        {
            cout << old_word << ", ";
            words.push_back(old_word);
            old_word = "";

        }
    }
    cout << old_word << "\n";
    words.push_back(old_word);

    return words;
}

int main()
{
    std::vector<std::string> ros_topics = get_ros_topics();
    std::vector<std::string> gazebosim_topics = get_ign_topics();

    std::cout << "\n\n";

    for (const string rtopic : ros_topics){
        std::cout << rtopic << ": ";

        bool found = false;
        for (const string itopic : gazebosim_topics) {
            if (rtopic == itopic) {
                found = true;
                break;
            }
        }
        string res = found ? "Found" : "Not found";
        
        std::cout << res << "\n";

    }



    return 0;
}