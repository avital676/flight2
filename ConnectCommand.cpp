
#include "command.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <cstring>
#include "variables.h"
#include "keepThreads.h"
#include <algorithm>

// Exectute connect command:
int ConnectCommand::execute(int i, vector<string> v) {
    double calculate = express(v[i+2]);
    int port = (int)calculate;
    openCli(port, v[i + 1]);
    return numOfPar + 1;
}

// send data to simulator:
void sendToSimu(int client_socket) {
    while(keepThreads::getInstance()->is_open) {
        // get the vars who's values were changed and update the simulator:
        vector<pair<string, float>> changedVars = variables::getInstance()->getChangedVars();
        if(changedVars.empty()) {
        } else {
            for (int i = 0; i < changedVars.size(); i++) {
                pair<string, float> p = changedVars[i];
                string s = "set " + p.first + " " + to_string(p.second) + "\r\n";
                const char *msg = s.c_str();
                int is_sent = send(client_socket, msg, strlen(msg), 0);
                if (is_sent == -1) {
                    cerr << "error sending message" << endl;
                }
                char buffer[1024] = {0};
                int valread = read( client_socket , buffer, 1024);
            }
        }
    }
    close(client_socket);
}

// Open a connection with the simulator:
int openCli(int port, string ip) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        cerr << "Could not create a socket" << endl;
        return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    address.sin_port = htons(port);
    // request connection with server:
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        cerr << "Could not connect to host server" << endl;
        return -2;
    } else { // client is connected
        keepThreads::getInstance()->clientTread = thread(sendToSimu, client_socket);
    }
}
