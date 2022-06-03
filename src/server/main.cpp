#include <iostream>
#include <string>
#include "../shared/Socket.hpp"

using namespace std;

int main(){
    cout << "Hello, server!!" << endl;

    Socket s = Socket("127.0.0.1", 3000);
    s.listen();
    s.accept();

    cout << "Alguém conectou!!" << endl;

    string data = s.receive();
    cout << "Recebi: " << data << endl;
    
    return 0;
}