#include "./Client.hpp"

Client::Client(int fd){
    this->fd = fd;
    connected = true;
    is_muted = false;
    name = "Anon";
    this->cr = nullptr;
}

void Client::receive(){
    worker = new thread(&Client::main_loop, this);
    worker->detach();
}

void Client::main_loop(){
    bool message_finished = true; //Indica se a mensagem está completa
    string msg = ""; //A mensagem corrente

    while(connected){
        string current;

        try{
            current = Socket::receive(fd);
        }
        catch (exception e){
            cout << "Erro na conexão com " << fd << ". Finalizando thread." << endl;
            cout << e.what() << endl;
            break;
        }

        //Nova mensagem começando
        if(message_finished && current.find(START_MESSAGE) != string::npos){
            message_finished = false;
        }

        //Adiciona apenas caso a mensagem esteja sendo construída
        //Caso contrário, o conteúdo recebido é ignorado
        if(!message_finished){
            msg.append(current);
        }

        //Fim da mensagem, enviar
        if(!message_finished && current.find(END_MESSAGE) != string::npos && connected){
            //Remove os delimitadores da mensagem
            msg = msg.substr(string(START_MESSAGE).size(), msg.size() - string(END_MESSAGE).size() - string(START_MESSAGE).size());

            if(msg[0] == '/'){ //A mensagem se trata de um comando
                run_command(msg);
            }
            else if(is_muted){
                this->send("Você está mutado e não pode mandar mensagens.");
            }
            else{ //É uma mensagem usual. Encaminhar para o canal, se houver canal.
                msg = string("").append(name).append(":").append(msg);
                this->send(msg);
            }

            message_finished = true;
            msg = "";
        }
    }
    
    disconnect();
}

void Client::run_command(string command){
    cout << "Comando recebido: " << command << endl;
    vector<string> split_results = split(command,' ');
    command = split_results[0];
    string arg = split_results.size() >= 2 ? split_results[1] : "";

    if (command == "/ping"){
        this->send(message_string("pong"));
    }
    else if(command == "/nickname" && arg.size() > 0 && arg.size() < 50){
        mut.lock();
        this->name = arg;
        mut.unlock();
        this->send("Seu nome foi alterado.");
    }
    else{
        this->send("O comando passado é inválido ou não autorizado.");
    }
}

void Client::send(string msg){
    try{
        Socket::send(fd,message_string(msg));
        return;
    }
    catch(exception e){
        for(int i = 0; i<MAX_TRIES-1; i++){
            try{
                Socket::send(fd,msg);
                return;
            }
            catch(exception e){
                continue;
            }
        }
    }

    disconnect();
}

string Client::get_name(){
    return name;
}

bool Client::get_connected(){
    return connected;
}

Chatroom* Client::get_cr(){
    return cr;
}

void Client::mute(){
    lock_guard<mutex> g(mut);
    is_muted = true;
}

void Client::unmute(){
    lock_guard<mutex> g(mut);
    is_muted = false;
}

void Client::disconnect(){
    try{
        this->send(message_string("/disconnect"));
    }
    catch (exception e){
        //Mensagem não pôde ser enviada.
    }

    lock_guard<mutex> g(mut);
    connected = false;
}