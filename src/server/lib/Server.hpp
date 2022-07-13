#pragma once

#include "../../shared/Socket.hpp"

#include <iostream>
#include <thread>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 3000

using namespace std;

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

        // Para a thread
        void stop();

        // Retorna se o servidor deveria parar
        bool get_should_stop();

    private:
        // Construtor privado para impedir criação direta pelo usuário
        Server();

        // O loop da thread
        void main_loop();

        static Server* _instance; // A instância do server
        Socket s; // O socket que recebe as conexões
        bool should_stop; // Define se o servidor deve parar
        thread* worker; // A thread que recebe conexões
};