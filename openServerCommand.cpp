
#include "command.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <string>
#include "variables.h"
#include "keepThreads.h"

// Execute open server command:
int openServerCommand::execute(int i, vector<string> v) {
    double calculate = express(v[i+1]);
    int port = (int)calculate;
    int opened = openSer(port);
    // try to open the server until it opens:
    while (opened != 0) {
        opened = openSer(port);
    }
    return numOfPar + 1;
}

// Open server to communicate with the simulator:
int openSer(int port) {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }

    if (listen(socketfd, 5) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    }
    keepThreads::getInstance()->is_open = true;
    // accept a client:
    int client_socket = accept(socketfd, (struct sockaddr *)&address, (socklen_t*)&address);
    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return -4;
    }
    close(socketfd);
    // activate the server thread for accepting data from the simulator:
    keepThreads::getInstance()->serverTread = thread(acceptFromSimu, client_socket);
    return 0;
}

// Accept data from the simulator:
void acceptFromSimu(int client_socket) {
    // read from client:
    char buffer[1024] = {0};
    int valread;
    // while program is open, read from client:
    while (keepThreads::getInstance()->is_open) {
        valread = read( client_socket , buffer, 1024);
        dataToMap(buffer);
    }
}

// Insert given data into variables map:
void dataToMap(char* data) {
    string s = "";
    int i;
    int counter = 0;
    string sim_name;
    string line = string(data);
    // iterate line and update values in map according to the variables sim:
    for (i = 0; i < line.size(); i++) {
        if (data[i] != ',') {
            s += line[i];
        } else {
            if (counter > 34) {
                break;
            }
            float value = stof(s.c_str());
            variables::getInstance()->setVarBySim(variables::getInstance()->nameArr[counter], value);
            counter++;
            s = "";
        }
    }
    if (s!="") {
        float value = stof(s.c_str());
        variables::getInstance()->setVarBySim(variables::getInstance()->nameArr[counter], value);
        s = "";
    }
}
