#pragma once
#include <iostream>
#include <string>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#define MAX_MESSAGE_SIZE 4096

using namespace std;

class Socket {
    public: 
        /* Constrói o socket com base em um endereço ipv4 e uma porta. */
        Socket(string addr, unsigned short port);

        /* Destrutor: fecha o socket antes de destruir o objeto */
        ~Socket();

        /* Função para socket do lado de servidor.
        Faz bind e começa a ouvir na porta estabelecida*/
        void listen();

        /* Função para socket do lado de servidor.
        Aceita uma conexão e retorna seu descritor de arquivo (ou -1 no caso de erro)*/
        int accept();

        /* Função para socket do lado de cliente
        Conecta a um servidor */
        void connect();
        
        /* Envia mensagem */
        void send(string msg);

        /* Recebe mensagem */
        string receive();
    
    private:
        int fd; /* File descriptor do socket */
        struct sockaddr_in address; /* Endereço do socket */
};