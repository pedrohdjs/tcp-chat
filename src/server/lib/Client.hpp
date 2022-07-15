#pragma once

#include "../../shared/Socket.hpp"
#include "./Utils.hpp"
#include "./Chatroom.hpp"
#include "./Server.hpp"

#include <iostream>
#include <thread>
#include <string>
#include <mutex>

#define START_MESSAGE "/startmsg/"
#define END_MESSAGE "/endmsg/"
#define MAX_TRIES 5

using namespace std;

//Classe que representa um cliente conectado ao servidor
class Client{
    public:
        // Constrói um cliente com o FD passado
        Client(int fd);

        bool operator==(const Client& other);

        // Inicia o recebimento de mensagens do cliente em uma thread separada
        void receive();

        // Envia uma mensagem para o cliente específico
        void send(string msg);
        
        // Obtém o nome do cliente
        string get_name();

        // Muta esse cliente
        void mute();

        // Desmuta esse cliente
        void unmute();

        bool get_connected();

        Chatroom* get_cr();

        // Desconecta o cliente
        void disconnect();
    private:
        // O loop principal do recebimento de mensagens
        void main_loop();
        
        //Executa um comando recebido
        void run_command(string command);

        int fd; // Descritor de arquivo
        bool is_admin; // Indica se o cliente é administrador do servidor atual
        bool is_muted; // Indica se o cliente está mutado
        string name; // O nome do cliente
        bool connected; // Estado da conexão
        thread* worker; // A thread de recepção das mensagens
        mutex mut;
        Chatroom* cr; // A chatroom na qual o usuário está
};