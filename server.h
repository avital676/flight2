//
// Created by avital on 16/12/2019.
//

#ifndef FLIGHT1_SERVER_H
#define FLIGHT1_SERVER_H

#include <string>
#include <map>

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

};
#endif //FLIGHT1_SERVER_H
