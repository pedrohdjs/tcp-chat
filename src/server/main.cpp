#include <iostream>
#include <string>
#include <thread>
#include <iostream>
#include <csignal>

#include "../shared/Socket.hpp"
#include "./lib/Server.hpp"

using namespace std;

void handle_signal(int signal){
    cout << "O servidor não pode ser finalizado." << endl;
}

int main(){
    Server* s = Server::get_instance();
    s->init();
    s->run();

    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    s->get_worker()->join(); //Espera a thread terminar

    return 0;
}