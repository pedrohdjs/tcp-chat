#include "./Server.hpp"

Server* Server::_instance = nullptr;

Server* Server::get_instance(){
    if(Server::_instance == nullptr){
        Server::_instance = new Server();
    }

    return Server::_instance;
}

void Server::init(){
    s.bind();
    s.listen(MAX_CONNECTIONS);

    cout << "Servidor ouvindo em " << SERVER_IP << ":" << SERVER_PORT << endl;

    return;
}

void Server::run(){
    worker = new thread(&Server::main_loop, this);
}

void Server::main_loop(){
    cout << "Aguardando conexões" << endl;
    while (!should_stop){
        int fd = s.accept();
    }
}

thread* Server::get_worker(){
    return worker;
}

bool Server::get_should_stop(){
    return should_stop;
}

Server::Server( ): s(SERVER_IP, SERVER_PORT){
    should_stop = false;
} 