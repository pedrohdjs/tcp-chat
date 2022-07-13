#include <iostream>
#include <string>
#include <thread>
#include <iostream>
#include <csignal>

#include "../shared/Socket.hpp"
#include "./lib/Server.hpp"

using namespace std;

void handle_signal(int signal){
    cout << "O servidor não pode ser finalizado." << endl;
}

int main(){

    //TODO: remover comentários na entrega
    
    // Socket s = Socket("127.0.0.1", 3000);
    // s.bind();
    // s.listen(MAX_CONNECTIONS);
    
    // int fd = s.accept();
    // cout << "Conexão aceita: " << endl;

    // Socket::send(fd, "Server diz oi!");
    // cout << "Dados enviados para o cliente com sucesso!!" << endl;

    // string data = Socket::receive(fd);
    // cout << "Dados recebidos do cliente: " << data << endl;

    Server* s = Server::get_instance();
    s->init();
    s->run();

    // TODO: Descomentar na entrega
    // signal(SIGINT, handle_signal);
    // signal(SIGTERM, handle_signal);

    s->get_worker()->join(); //Espera a thread terminar

    return 0;
}