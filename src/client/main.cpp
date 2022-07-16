#include <iostream>
#include <string>
#include <thread>
#include "../shared/Socket.hpp"
#include "../shared/Constants.hpp"


using namespace std;

void receive(int fd){
    string msg;
    while(true){
        try{
            msg = Socket::receive(fd);
        }
        catch (exception e){
            cout << "Deu ruim" << endl;
            break;
        }
        cout << msg << endl;
    }
}

int main(){
    Socket s = Socket(string(SERVER_IP), SERVER_PORT);
    s.connect();
    cout << "Cliente conectado com sucesso" << endl;

    thread t(&receive, s.getFd());

    while (true){
        string msg;
        getline(cin, msg, '\n');
        msg = string("/startmsg/").append(msg).append(string("/endmsg/"));
        
        try{
            Socket::send(s.getFd(), msg);
        }
        catch (exception e){
            cout << "Servidor desconectado" << endl;
            break;
        }
    }
    
    t.join();

    // string data = Socket::receive(s.getFd());
    // cout << "Dados recebidos do servidor: " << data << endl;
    
    // Socket::send(s.getFd(), "Cliente diz oi!");
    // cout << "Dados enviados para o servidor com sucesso!!" << endl;
    
    return 0;
}