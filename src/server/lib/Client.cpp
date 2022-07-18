#include "./Client.hpp"

Client::Client(int fd, string ip) {
    this->fd = fd;
    this->ip = ip;
    connected = true;
    is_muted = false;
    is_admin = false;
    name = "Anon";
    this->cr = nullptr;
}

bool Client::operator==(const Client& other) { return this->fd == other.fd; }

void Client::receive() {
    worker = new thread(&Client::main_loop, this);
    worker->detach();
}

void Client::main_loop() {
    bool message_finished = true;  // Indica se a mensagem está completa
    string msg = "";               // A mensagem corrente

    while (connected) {
        string current;

        try {
            current = Socket::receive(fd);
        } catch (exception e) {
            cout << "Erro na conexão com " << fd << ". Finalizando thread."
                 << endl;
            cout << e.what() << endl;
            break;
        }

        // Nova mensagem começando
        if (message_finished && current.find(START_MESSAGE) != string::npos) {
            message_finished = false;
        }

        // Adiciona apenas caso a mensagem esteja sendo construída
        // Caso contrário, o conteúdo recebido é ignorado
        if (!message_finished) {
            msg.append(current);
        }

        // Fim da mensagem, enviar
        if (!message_finished && current.find(END_MESSAGE) != string::npos &&
            connected) {
            // Remove os delimitadores da mensagem
            msg = msg.substr(string(START_MESSAGE).size(),
                             msg.size() - string(END_MESSAGE).size() -
                                 string(START_MESSAGE).size());

            if (msg[0] == '/') {  // A mensagem se trata de um comando
                run_command(msg);
            } else if (is_muted) {
                this->send("Você está mutado e não pode mandar mensagens.");
            } else {  //É uma mensagem usual. Encaminhar para o canal, se houver
                      // canal.
                msg = string("").append(name).append(":").append(msg);
                if (this->cr != nullptr) {
                    cr->send(msg);
                } else {
                    this->send(
                        "Entre em uma sala com /join para enviar mensagens.");
                }
            }

            message_finished = true;
            msg = "";
        }
    }

    disconnect();
}

void Client::run_command(string command) {
    cout << "Comando recebido: " << command << endl;
    vector<string> split_results = split(command, ' ');
    command = split_results[0];

    string arg = "";
    if (command == "/join" && split_results.size() > 2)
        arg = split_results[1] + " " + split_results[2];
    else
        arg = split_results.size() >= 2 ? split_results[1] : "";

    if (command == "/ping") {
        this->send("pong");
        return;
    } else if (command == "/quit") {
        if (cr != nullptr) {
            cr->remove_client(this);
        }
        this->disconnect();
        return;
    } else if (command == "/nickname" && arg.size() > 0 && arg.size() < 50) {
        mut.lock();
        this->name = arg;
        mut.unlock();
        this->send("Seu nome foi alterado.");
        return;
    } else if (command == "/join" && arg.size() > 0) {
        if (!Chatroom::is_name_valid(arg)) {
            this->send("O nome da sala passado é inválido.");
            return;
        }

        // Sai da sala atual
        if (this->cr != nullptr) {
            this->cr->remove_client(this);
        }

        Server* s = Server::get_instance();
        unordered_map<string, Chatroom*> chatrooms = s->get_chatrooms();
        if (!chatrooms.count(arg)) {  // Sala ainda não existe, criar e fazer do
                                      // usuário admin
            Chatroom* new_cr = new Chatroom(arg);
            new_cr->add_client(this);
            s->add_chatroom(new_cr);
            mut.lock();
            this->cr = new_cr;
            this->is_admin = true;
            mut.unlock();
            this->send("Você entrou no canal como admin.");
        } else {  // Sala existente
            chatrooms[arg]->add_client(this);
            mut.lock();
            this->is_admin = false;
            this->cr = chatrooms[arg];
            mut.unlock();
            this->send("Você entrou no canal.");
        }
    } else if (this->cr != nullptr &&
               this->is_admin) {  // Comandos de administrador
        if (command == "/mute" && arg.size() > 0) {
            this->cr->mute_client(arg);
            this->send("Você mutou o usuário.");
        } else if (command == "/unmute" && arg.size() > 0) {
            this->cr->unmute_client(arg);
            this->send("Você desmutou o usuário.");
        } else if (command == "/kick" && arg.size() > 0) {
            this->cr->remove_client(arg);
            this->send("Você removeu o usuário.");
        } else if (command == "/whois" && arg.size() > 0) {
            string ip = this->cr->get_client_ip(arg);
            this->send(string("IP do usuário: ").append(ip));
        } else {
            this->send("O comando passado é inválido.");
        }
    } else {
        this->send("O comando passado é inválido ou não autorizado.");
    }
}

void Client::send(string msg) {
    msg = message_string(msg);
    try {
        Socket::send(fd, msg);
        return;
    } catch (exception e) {
        for (int i = 0; i < MAX_TRIES - 1; i++) {
            try {
                Socket::send(fd, msg);
                return;
            } catch (exception e) {
                continue;
            }
        }
    }

    disconnect();
}

string Client::get_name() { return name; }

bool Client::get_connected() { return connected; }

Chatroom* Client::get_cr() { return cr; }

void Client::mute() {
    lock_guard<mutex> g(mut);
    is_muted = true;
    this->send("Você foi mutado.");
}

void Client::unmute() {
    lock_guard<mutex> g(mut);
    is_muted = false;
    this->send("Você foi desmutado.");
}

void Client::disconnect() {
    if (!connected) return;

    try {
        this->send("/disconnect");
    } catch (exception e) {
        // Mensagem não pôde ser enviada. Cliente provavelmente crashou.
    }

    lock_guard<mutex> g(mut);
    connected = false;
}

void Client::exit_cr() {
    lock_guard<mutex> g(mut);
    if (this->cr != nullptr) {
        cr = nullptr;
    }
    this->send("/exit");
}

string Client::get_ip() { return ip; }