#include "./Chatroom.hpp"

Chatroom::Chatroom(string name){
    this->name = name;
}

void Chatroom::send(string msg){
    lock_guard<mutex> g(mut);
    for(Client* c : clients){
        if(c->get_connected()){
            c->send(msg);
        }
    }
}

void Chatroom::add_client(Client* c){
    lock_guard<mutex> g(mut);
    clients.push_back(c);
}

bool Chatroom::is_name_valid(string name){
    return true;
}

// void Chatroom::remove_client(string name){
//     lock_guard<mutex> g(mut); //Tranca o acesso aos recursos enquanto está em escopo
//     for(vector<Client*>::iterator it = clients.begin(); it != clients.end(); it++){
//         if((*it)->get_name() == name){
//             clients.erase(it);
//         }
//     }
// }

void Chatroom::mute_client(string name){
    lock_guard<mutex> g(mut); //Tranca o acesso aos recursos enquanto está em escopo
    for(vector<Client*>::iterator it = clients.begin(); it != clients.end(); it++){
        if((*it)->get_name() == name){
            (*it)->mute();
        }
    }
}

void Chatroom::unmute_client(string name){
    lock_guard<mutex> g(mut); //Tranca o acesso aos recursos enquanto está em escopo
    for(vector<Client*>::iterator it = clients.begin(); it != clients.end(); it++){
        if((*it)->get_name() == name){
            (*it)->unmute();
        }
    }
}


string Chatroom::get_name(){
    return name;
}