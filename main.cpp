#include <iostream>
#include "lexer.cpp"
#include "parser.h"
#include "variables.h"
#include "keepThreads.h"


#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <cstring>


int main() {
    string ip = "127.0.0.1";
    int port = 5402;
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        cerr << "Could not create a socket" << endl;
        return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    cout << ip << endl;
    const char* ipConst = ip.c_str();
    address.sin_addr.s_addr = inet_addr(ipConst);
    address.sin_port = htons(port);
    cout << port << endl;
    cout << ip << endl;
    // request connection with server:
    int is_connect = connect(client_socket, (struct sockaddr*) &address, sizeof(address));
    if (is_connect == -1) {
        cerr << "Could not connect to host server" << endl;
        return -2;
    } else { // client is connected
        int is_sent;
        int autostart = 1;
        cout << "opened client" << endl;
        string sim = "/engines/active-engine/auto-start";
        char strV[]="";
        string s = "set " + sim + " " + to_string(autostart) + " \r\n";
        cout << s << endl;
        char strToSend[s.length()+1];
        strcpy(strToSend, s.c_str());
        is_sent = send(client_socket, strToSend, strlen(strV), 0);
        if (is_sent == -1) {
            cerr << "error sending message" << endl;
        }
    }


//
//
//    variables::getInstance();
//    std::cout << "Hello, World!" << std::endl;
//    lexer l;
//    vector<string> v = l.lex();
//    parser* p = new parser(v);
//    keepThreads::getInstance()->is_open = true;
//    p->parse();
//    l.lex();
//    keepThreads::getInstance()->is_open = false;
//    keepThreads::getInstance()->serverTread.join();
//    keepThreads::getInstance()->clientTread.join();
    return 0;
}
