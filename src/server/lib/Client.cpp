#include "./Client.hpp"

Client::Client(int fd){
    this->fd = fd;
    connected = true;
    name = "Anon";
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
            if(!message_finished && current.find(END_MESSAGE) != string::npos){
                //Remove os delimitadores da mensagem
                msg = msg.substr(string(START_MESSAGE).size(), msg.size() - string(END_MESSAGE).size() - string(START_MESSAGE).size());

                if(msg[0] == '/'){ //A mensagem se trata de um comando
                    run_command(msg);
                }
                else{ //É uma mensagem usual. Encaminhar para o canal, se houver canal.
                    cout << name << ": " << msg << endl;
                }

                message_finished = true;
                msg = "";
            }

            // cout << "DEBUG MSG: " << msg << endl << "DEBUG CURRENT: " << current << endl; 
    }
}

void Client::run_command(string command){
    vector<string> split_results = split(command,' ');
    command = split_results[0];
    string arg = split_results.size() >= 2 ? split_results[1] : "";

    if(command == "/nickname" && arg.size()){
        mut.lock();
        this->name = arg;
        mut.unlock();
    }
    else{
        cout << "Comando inválido passado pelo usuário" << endl;
    }
}