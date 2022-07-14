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