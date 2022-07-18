#include <iostream>
#include <string>
#include <vector>

#include "../shared/Utils.hpp"
#include "lib/Action.hpp"

using namespace std;

int main() {
    Action *act = new Action();

    act->clear();

    while (true) {
        string msg;
        getline(cin, msg, '\n');

        vector<string> split_results = split(msg, ' ');
        string command = split_results[0];

        if (command == "/connect")
            act->connect(split_results);

        else if (command == "/quit")
            act->quit();

        else if (command == "/help")
            act->help();

        else if (command == "/clear")
            act->clear();

        else
            act->send_message(msg);
    }

    return 0;
}