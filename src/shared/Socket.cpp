#include "Socket.hpp"

Socket::Socket (string addr, unsigned short port) {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);  

    if (this->fd == -1) {
        throw runtime_error("Falha ao criar socket");
    }

    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(port);
    this->address.sin_addr.s_addr = inet_addr(addr.c_str());
}

Socket::~Socket () {
    close(this->fd);
}


void Socket::listen () {
    int reuse = 1;

    if (bind(this->fd, (struct sockaddr *) &this->address, sizeof(this->address)) != 0 ||
        setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuse, sizeof(int)) != 0) {
        throw runtime_error("Falha ao fazer bind do socket com a porta passada");
    }

    if (::listen(this->fd, 10) != 0) {
        throw runtime_error("Falha ao fazer listen no socket");
    }

    return;
}

int Socket::accept() {
    int client_fd;
    struct sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);

    client_fd = ::accept(this->fd, (struct sockaddr *) &client_address, &client_address_size);

    return client_fd;
}

void Socket::connect () {
    if (::connect(this->fd, (struct sockaddr *) &this->address, sizeof(this->address)) != 0) {
        throw runtime_error("Falha ao conectar o socket");
    }

    return;
}

void Socket::send (string msg) {
    sleep(2);
    if (::write(this->fd, msg.c_str(), msg.size()) != msg.size()) {
        throw runtime_error("Falha ao enviar mensagem");
    }

    return;
}

string Socket::receive () {
    char buffer[MAX_MESSAGE_SIZE];
    memset(buffer, 0, MAX_MESSAGE_SIZE);
    int bytes_read;

    bytes_read = ::read(this->fd, buffer, MAX_MESSAGE_SIZE);

    if (bytes_read == -1) {
        cout << errno << endl;
        throw runtime_error("Falha ao receber mensagem");
    }

    return string(buffer);
}