#pragma once
#include <string>
#include <thread>
#include <mutex>

#include "../../shared/Socket.hpp"
#include "./Client.hpp"

using namespace std;

class Client;

class Chatroom{
    public:
        // Tenta criar uma chatroom
        Chatroom(string name);

        // Valida um nome
        static bool is_name_valid(string name);

        // Repassa mensagem para todos os clientes
        void send(string msg);

        // Adiciona um novo cliente
        void add_client(Client* c);

        // // Remove um cliente
        void remove_client(string name);

        // Remove um cliente
        void remove_client(Client* c);

        // Muta um cliente
        void mute_client(string name);

        // Desmuta um cliente
        void unmute_client(string name);

        // Obtém o IPv4 do usuário com o nome passado
        string get_client_ip(string name);

        // Retorna o nome da chatroom
        string get_name();
    private:
        string name;
        vector<Client*> clients;
        mutex mut;
};
