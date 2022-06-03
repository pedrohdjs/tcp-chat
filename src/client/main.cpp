#include <iostream>
#include <string>
#include "../shared/Socket.hpp"

using namespace std;

int main(){
    cout << "Hello, client!!" << endl;

    Socket s = Socket("127.0.0.1", 3000);
    s.connect();

    cout << "Conectei!!" << endl;

    s.send("Cliente diz oi!");
    
    return 0;
}