#include "Action.hpp"

using namespace std;

Action::Action() { this->connected = false; }

void Action::connect(vector<string> components) {
    try {
        this->s = new Socket(string(components[1]), stoi(components[2]));
        this->s->connect();
        this->t = thread((&receive_message), s->getFd());
        this->connected = true;
    } catch (exception e) {
        cout << "Algo deu errado. Cheque o formato: /connect IP PORTA e o "
                "servidor"
             << endl;
    }
}

void Action::receive_message(int fd) {
    string msg = "";
    while (msg != "/disconnect") {
        try {
            msg = Socket::receive(fd);
        } catch (exception e) {
            cout << "Algo deu errado. Desconectando!" << endl;
            break;
        }

        regex regexp("(/startmsg/)(.*?)(/endmsg/)");  // Grupo entre /startmsg/
                                                      // e /endmsg/
        smatch m;
        regex_search(msg, m, regexp);
        msg = m[2];

        if (msg == "/ack")
            cout << "Cliente conectado com sucesso" << endl;
        else if (msg == "/exit")
            cout << "Saiu da sala!" << endl;
        else if (msg == "/disconnect")
            cout << "Até mais =]" << endl;
        else
            cout << msg << endl;
    }
}

bool Action::send_message(string message) {
    if (!this->check_connection()) return false;

    message = string("/startmsg/").append(message).append(string("/endmsg/"));
    try {
        Socket::send(s->getFd(), message);
        return true;
    } catch (exception e) {
        return false;
    }
}

void Action::quit() {
    if (this->check_connection()) {
        this->send_message("/quit");
        this->t.join();
    }
    exit(0);
}

bool Action::check_connection() {
    if (this->connected) return true;
    cout << "Você precisa se conectar primeiro!" << endl;
    return false;
}

void Action::help() {
    cout << "Instrução"
         << "\t"
         << "Formato" << endl
         << endl;

    cout << "/connect"
         << "\t"
         << "/connect IP PORTA" << endl;

    cout << "/ping"
         << "\t\t"
         << "/ping" << endl;

    cout << "/nickname"
         << "\t"
         << "/nickname seu_nick" << endl;

    cout << "/join"
         << "\t\t"
         << "/join #canal" << endl;

    cout << "/mute"
         << "\t\t"
         << "/mute nick" << endl;

    cout << "/unmute"
         << "\t\t"
         << "/unmute nick" << endl;

    cout << "/kick"
         << "\t\t"
         << "/kick nick" << endl;

    cout << "/whois"
         << "\t\t"
         << "/whois nick" << endl;

    cout << "/clear"
         << "\t\t"
         << "/clear" << endl;

    cout << "/help"
         << "\t\t"
         << "/help" << endl;

    cout << endl;
}

void Action::clear() {
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}