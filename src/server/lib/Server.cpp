#include "./Server.hpp"

Server* Server::_instance = nullptr;

Server::Server( ): s(SERVER_IP, SERVER_PORT){
} 

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
    while (true){
        string ip;
        int fd = s.accept(&ip);
        Client* c = new Client(fd, ip);

        try {
            c->send("/ack");
        }
        catch (exception e){
            delete c;
            continue;
        }

        add_client(c);
        cout << "Cliente com FD " << fd << " e IP " << ip << " conectado!" << endl;
    }
}

thread* Server::get_worker(){
    return worker;
}

void Server::add_client(Client* c){
    lock_guard<mutex> g(mut); //Tranca o acesso aos recursos enquanto está em escopo
    clients.push_back(c);
    clients.back()->receive(); //Inicia o recebimento de mensagens vindas do cliente

    // //DEBUG
    // cout << endl;
    // for(Client* cli : clients){
    //     cout << cli->get_name() << ": " << cli->get_connected();
    // }
    // cout << endl;
}

unordered_map<string, Chatroom*> Server::get_chatrooms(){
    return chatrooms;
}

void Server::add_chatroom(Chatroom* cr){
    lock_guard<mutex> g(mut);
    chatrooms[cr->get_name()] = cr;
}