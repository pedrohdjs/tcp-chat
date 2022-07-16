#pragma once

#include "../../shared/Constants.hpp"
#include "../../shared/Socket.hpp"
#include "./Client.hpp"
#include "./Chatroom.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <unordered_map>


using namespace std;

// Forward declaration devido a dependências circulares
class Client;
class Chatroom;

// Classe principal do servidor, contendo seus dados. 
// Segue o Design Pattern do GoF "Singleton", especificado em
// https://refactoring.guru/pt-br/design-patterns/singleton/cpp/example
class Server {
    public:
        // Obtém a instância do Server
        static Server* get_instance();

        // O objeto não deve ser clonável
        Server(Server &other) = delete;

        // Não deve ser possível atribuir valores ao objeto
        void operator=(const Server&) = delete;

        // Inicializa o servidor
        void init();

        // Executa o servidor
        void run();

        // Retorna a thread principal do servidor
        thread* get_worker();

        // Adiciona um cliente ao servidor
        void add_client(Client* c);

        // Obtém as salas
        unordered_map<string, Chatroom*> get_chatrooms();

        // Adiciona uma chatroom
        void add_chatroom(Chatroom* cr);
    private:
        // Construtor privado para impedir criação direta pelo usuário
        Server();

        // O loop da thread
        void main_loop();

        static Server* _instance; // A instância do server
        Socket s; // O socket que recebe as conexões
        thread* worker; // A thread que recebe conexões
        vector<Client*> clients; //Os clientes conectados
        unordered_map<string, Chatroom*> chatrooms;
        mutex mut; // Mutex que controla o acesso aos dados
};