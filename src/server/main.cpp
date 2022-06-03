#include <iostream>
#include <string>
#include "../shared/Socket.hpp"

using namespace std;

int main(){
    Socket s = Socket("127.0.0.1", 3000);
    s.bind();
    s.listen(MAX_CONNECTIONS);
    
    int fd = s.accept();
    cout << "Conexão aceita: " << endl;

    Socket::send(fd, "Server diz oi!");
    cout << "Dados enviados para o cliente com sucesso!!" << endl;

    string data = Socket::receive(fd);
    cout << "Dados recebidos do cliente: " << data << endl;

    data = Socket::receive(fd);
    cout << "Dados recebidos do cliente: " << data << endl;

    return 0;
}