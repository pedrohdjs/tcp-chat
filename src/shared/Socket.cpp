#include "Socket.hpp"

Socket::Socket (string addr, unsigned short port) {
    cout << addr << ":" << port << endl;
    this->fd = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);  

    if (this->fd == -1) {
        throw runtime_error("Falha ao criar socket");
    }

    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = inet_addr(addr.c_str());
    this->address.sin_port = htons(port);
}

Socket::~Socket () {
    close();
}

int Socket::getFd () {
    return this->fd;
}

void Socket::bind() {
    int reuse = 1;

    if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse) == -1){
        throw std::runtime_error("Falha ao fazer definir opcoes do socket");
    }

    if (::bind(this->fd, (struct sockaddr *)&this->address, sizeof(this->address)) == -1){
        throw std::runtime_error("Falha ao fazer bind do socket com a porta passada");
    }
}



void Socket::listen (int maxConnections) {
    if (::listen(this->fd, maxConnections) == -1) {
        throw runtime_error("Falha ao fazer listen no socket");
    }

    return;
}

int Socket::accept() {
    int client_fd;
    struct sockaddr_storage client_address;
    socklen_t client_address_size = sizeof client_address;

    client_fd = ::accept(this->fd, (struct sockaddr *) &client_address, &client_address_size);

    return client_fd;
}

void Socket::connect () {
    if (::connect(this->fd, (struct sockaddr *) &this->address, sizeof(this->address)) == -1) {
        throw runtime_error("Falha ao conectar o socket");
    }

    return;
}

void Socket::send (int fd, string msg) {
    int bytes_sent;

    while (msg.size() > 0) {
        string chunk;

        if(msg.size() > MAX_MESSAGE_SIZE) {
            chunk = msg.substr(0, MAX_MESSAGE_SIZE);
            msg = msg.substr(MAX_MESSAGE_SIZE, msg.size());
        } else {
            chunk = msg;
            msg = "";
        }
        
        bytes_sent = ::send(fd, chunk.c_str(), chunk.size(), 0);

        if (bytes_sent <= 0) {
            throw runtime_error("Falha ao enviar mensagem");
        }
    }

    return;
}

string Socket::receive (int fd) {
    char buffer[MAX_MESSAGE_SIZE];
    memset(buffer, 0, MAX_MESSAGE_SIZE);
    int bytes_read;

    bytes_read = ::recv(fd, buffer, MAX_MESSAGE_SIZE, 0);
    
    if (bytes_read <= 0) {
        cout << "Error: " << errno << endl;
        throw runtime_error("Falha ao receber mensagem");
    }

    return string(buffer);
}

void Socket::close(){
    ::close(fd);
}