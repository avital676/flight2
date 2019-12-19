//
// Created by avital on 16/12/2019.
//

#ifndef FLIGHT1_SERVER_H
#define FLIGHT1_SERVER_H

#include <string>
#include <map>
#include <netinet/in.h>

using namespace std;
class server{
private:
     bool open;
     bool work;
     string port;
public:
    server(){};
    server(bool work);
    void dataToMap(string data);
    //void setSock(int socketfd, sockaddr_in address);
    //void readFromSimu();
};
#endif //FLIGHT1_SERVER_H
