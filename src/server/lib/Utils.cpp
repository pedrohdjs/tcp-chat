#include "./Utils.hpp"

vector<string>split(string s, char delimiter){
    vector<string> res;
    string segment;
    stringstream ss(s);

    while(getline(ss,segment,delimiter)){
        res.push_back(segment);
    }

    return res;
}

string message_string(string msg){
    return string(START_MESSAGE).append(msg).append(string(END_MESSAGE));
}