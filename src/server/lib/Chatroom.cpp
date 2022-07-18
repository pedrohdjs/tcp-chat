#include "./Chatroom.hpp"

#include <regex>

Chatroom::Chatroom(string name) { this->name = name; }

void Chatroom::send(string msg) {
    lock_guard<mutex> g(mut);
    for (Client* c : clients) {
        if (c->get_connected()) {
            c->send(msg);
        }
    }
}

void Chatroom::add_client(Client* c) {
    this->send(c->get_name().append(" entrou na sala."));
    lock_guard<mutex> g(mut);
    clients.push_back(c);
}

bool Chatroom::is_name_valid(string name) {
    return (bool)std::regex_match(name, std::regex("^[&#][^\\s,^G]{0,199}$"));
}

void Chatroom::remove_client(string name) {
    lock_guard<mutex> g(
        mut);  // Tranca o acesso aos recursos enquanto está em escopo

    vector<Client*>::iterator it = clients.begin();
    while (it != clients.end()) {
        if ((*it)->get_name() == name) {
            (*it)->exit_cr();
            it = clients.erase(it);
        } else {
            it++;
        }
    }
}

void Chatroom::remove_client(Client* c) {
    lock_guard<mutex> g(
        mut);  // Tranca o acesso aos recursos enquanto está em escopo
    vector<Client*>::iterator it = clients.begin();
    while (it != clients.end()) {
        if (*(*it) == *c) {
            (*it)->exit_cr();
            it = clients.erase(it);
        } else {
            it++;
        }
    }
}

void Chatroom::mute_client(string name) {
    lock_guard<mutex> g(
        mut);  // Tranca o acesso aos recursos enquanto está em escopo
    for (vector<Client*>::iterator it = clients.begin(); it != clients.end();
         it++) {
        if ((*it)->get_name() == name) {
            (*it)->mute();
        }
    }
}

void Chatroom::unmute_client(string name) {
    lock_guard<mutex> g(
        mut);  // Tranca o acesso aos recursos enquanto está em escopo
    for (vector<Client*>::iterator it = clients.begin(); it != clients.end();
         it++) {
        if ((*it)->get_name() == name) {
            (*it)->unmute();
        }
    }
}

string Chatroom::get_name() { return name; }

string Chatroom::get_client_ip(string name) {
    lock_guard<mutex> g(mut);
    for (Client* c : clients) {
        if (c->get_name() == name) {
            return c->get_ip();
        }
    }
    return string("Usuário não encontrado");
}