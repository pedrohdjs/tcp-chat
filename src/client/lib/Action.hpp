#pragma once

#include <limits>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include "../../shared/Socket.hpp"

using namespace std;

class Action {
   public:
    Action();

    void connect(vector<string> components);

    bool send_message(string message);

    static void clear();

    void quit();

    void help();

   private:
    Socket *s;
    thread t;
    bool connected;
    bool has_nick;
    static void receive_message(int fd);
    bool check_connection();
};