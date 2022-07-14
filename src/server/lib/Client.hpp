#pragma once

#include "../../shared/Socket.hpp"
#include "./Utils.hpp"

#include <iostream>
#include <thread>
#include <string>
#include <mutex>

#define START_MESSAGE "/startmsg/"
#define END_MESSAGE "/endmsg/"

//Classe que representa um cliente conectado ao servidor
class Client{
    public:
        // Constrói um cliente com o FD passado
        Client(int fd);

        // Inicia o recebimento de mensagens do cliente em uma thread separada
        void receive();
    private:
        // O loop principal do recebimento de mensagens
        void main_loop();
        
        //Executa um comando recebido
        void run_command(string command);

        int fd; // Descritor de arquivo
        bool is_admin; // Indica se o cliente é administrador do servidor atual
        string name; // O nome do cliente
        bool connected; // Estado da conexão
        thread* worker; // A thread de recepção das mensagens
        mutex mut;
};