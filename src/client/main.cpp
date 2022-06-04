#include <iostream>
#include <string>
#include "../shared/Socket.hpp"

using namespace std;

int main(){
    Socket s = Socket("127.0.0.1", 3000);
    s.connect();
    cout << "Cliente conectado com sucesso" << endl;

    string data = Socket::receive(s.getFd());
    cout << "Dados recebidos do servidor: " << data << endl;
    
    Socket::send(s.getFd(), "Cliente diz oi!");
    cout << "Dados enviados para o servidor com sucesso!!" << endl;
    
    return 0;
}