//
// Created by noa on 12/12/2019.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <cstring>
#include "command.h"
#include "variables.h"
#include "server.h"
#include "parser.h"
#include "Interpreter.h"
#include "keepThreads.h"

void acceptFromSimu(int client_socket) {
    cout << "waiting to read from simu" << endl;
    server ser = new server();
    //reading from client
    char buffer[1024] = {0};
    int valread;
    while (keepThreads::getInstance()->is_open) {
        valread = read( client_socket , buffer, 1024);
        cout << "read" << endl;
        ser.dataToMap(buffer);
    }
}

void sendToSimu(int client_socket) {
    int is_sent;
    while(keepThreads::getInstance()->is_open) {
        queue<varObj> q = variables::getInstance()->q;
        char strV[]="";
        if(q.empty()) {
            sleep(0.1);
        } else {
            while (!q.empty()) {
                string s = "set " + q.front().getSim().substr(1,-1) + " " + to_string(q.front().getVal()) + "\r\n";
                //cout << s << endl;
                char strToSend[s.length()+1];
                strcpy(strToSend, s.c_str());
                is_sent = send(client_socket, strToSend, strlen(strV), 0);
                if (is_sent == -1) {
                    cerr << "error sending message" << endl;
                }
                q.pop();
            }
        }
    }
}

int openSer(int port) {
    sleep(10);
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }

    if (listen(socketfd, 5) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        return -3;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }
    cout << port << endl;
    keepThreads::getInstance()->is_open = true;
    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);

    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return -4;
    }

    close(socketfd);

    keepThreads::getInstance()->serverTread = thread(acceptFromSimu, client_socket);
    return 0;
}


int openCli(int port, string ip) {
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
        cout << "opened client" << endl;
        keepThreads::getInstance()->clientTread = thread(sendToSimu, client_socket);
    }

}

int openServerCommand::execute(int i, vector<string> v) {
    cout << "openserver execute" << endl;
    int port = stoi(v[i + 1]);
    int opened = openSer(port);
    while (opened != 0) {
        opened = openSer(port);
    }
    unordered_map<string,varObj*> m = variables::getInstance()->getSimMap();
    return numOfPar + 1;
}

int ConnectCommand::execute(int i, vector<string> v) {
    sleep(5);
    int port = stoi(v[i + 2]);
    openCli(port, v[i + 1]);
    cout << "client connected" << endl;
    return numOfPar + 1;
}

int DefineVarCommand::execute(int i, vector<string> v) {
    //cout << "define var execute" << endl;
    varObj* var = new varObj;
    string varName;
    // define new var:
    if (v[i] == "var") {
        varName = v[i + 1];
        if (v[i + 2] == "->") {
            string sim = v[i + 4];
            var = variables::getInstance()->searchSim(sim);
            //var->setSim(v[i + 4]);
            var->setF(true);
            numOfPar = 4;
        } else if (v[i + 2] == "<-") {
            // search sim in simMap:
            string sim = v[i + 4];
            var->setF(false);
            var = variables::getInstance()->searchSim(sim);
            numOfPar = 4;
        } else if (v[i + 2] == "=") {
            var->setVal(express(v[i + 3]));
            numOfPar = 3;
        }
        variables::getInstance()->getNameMap()->insert({varName,var});
        //variables::getInstance()->setVarInNameMap(varName, *var);
        //variables::getInstance()->setVarInSimMap(var->getSim(), *var);
    } else { // var already defined:
        varName = v[i];
        *var = variables::getInstance()->getVarFromName(v[i]);
        var->setVal(express(v[i + 2]));
        variables::getInstance()->getNameMap()->insert({varName,var});
        //variables::getInstance()->setVarInNameMap(varName, *var);
        numOfPar = 2;
    }
    if (var->getF()) {
        variables::getInstance()->q.push(*var);
    }
    return numOfPar + 1;
}

void ConditionParser::setCom(class command a) {
    com = a;
}

ConditionParser::ConditionParser(string loop){
    if (loop.compare("if")){
        command *a= new ifCommand;
        this->setCom(*a);
    }
    if (loop.compare("while")){
        command *a= new loopCommand;
        this->setCom(*a);
    }
}

int ConditionParser::execute(int i, vector<string> v ) {
    return com.execute(i,v);
}

int ifCommand::execute(int i, vector<string> v) {
    int index;
    //if var  {...}
    if (v[i+2] == "{"){
        varObj v1=variables::getInstance()->getVarFromName(v[i + 1]);
        if (v1.getVal()>0){
            status= true;
            index=i+3;
        }
    }
   double v1= express(v[i+1]);
    double v2= express(v[i+3]);
    //if var == exp  {...}
    if (v[i+4] == "{"){
        index=i+5;
        if (v[i+2] == "=="){
            if (v1 == v2){
                status= true;
            }
        }
        if (v[i+2] == ">="){
            if (v1 >= v2){
                status= true;
            }
        }
        if (v[i+2]=="<="){
            if (v1 <= v2){
                status= true;
            }
        }
        if (v[i+2] == "!="){
            if (v1!=v2){
                status= true;
            }
        }
        if (v[i+2] == ">"){
            if (v1>v2){
                status= true;
            }
        }
        if (v[i+2] == "<"){
            if (v1<v2){
                status= true;
            }
        }
    }
    vector<string> newVector;
    //make new vector for parser.
    int countPare=0;
    while ((v[index] != "}")||(countPare!=0)){
        if (v[index] == "{") {
            countPare++;
        }
        if (v[index] == "}"){
            countPare--;
        }
        newVector.push_back(v[index]);
        index++;
    }
    if (status){
        //do the condition in loop
        parser *p = new parser(newVector);
        p->parse();
    }
    //return the next place after }.
    return index + 1;

}

int loopCommand::execute(int i, vector<string> v ) {
    int index = i;
    index = checkStatus(i,v, index);
    vector<string> newVector;
    int countPare=0;
    //make new vector for parser.
    while ((v[index] != "}")||(countPare!=0)){
//        if (v[index] == "{") {
//            countPare++;
//        }
//        if (v[index] == "}"){
//            countPare--;
//        }
        newVector.push_back(v[index]);
        index++;
    }

    while (status){
        // do the condition in loop
        cout<<"loop"<<endl;
        parser *p = new parser(newVector);
        p->parse();
        checkStatus(i, v, index);
    }
    // return the next place after }.
    return index+1;

}

int loopCommand::checkStatus(int i, vector<string> v, int index){
    // while break{...}
    if (v[i+2]=="{"){
        double v1 = express(v[i+1]);
        if (v1>0){
            status= true;
            index=i+3;
        }
    }
    double v1= express(v[i+1]);
    double v2= express(v[i+3]);
    //while breaks == exp{...}
    if (v[i+4] == "{"){
        index=i+5;
        if (v[i+2] == "=="){
            if (v1 == v2){
                status= true;
            }
        }
        if (v[i+2] == ">="){
            if (v1 >= v2){
                status= true;
            }
        }
        if (v[i+2] == "<="){
            if (v1<= v2){
                status= true;
            }
        }
        if (v[i+2] == "!="){
            if (v1!=v2){
                status= true;
            }
        }
        if (v[i+2] == ">"){
            if (v1 >v2){
                status= true;
            }
        }
        if (v[i+2] == "<"){
            if (v1 <v2 ){
                status= true;
            }
        }
    }
    return index;
}

double command::express(string s){
Interpreter *i = new Interpreter();
string allVars="";
string var="";

for (int i =0; i < s.length(); i++){
        //find variables
        if ((s[i]<='z')&&(s[i]>='a')) {
            var += s[i];
        }
        if((s[i]=='+')||(s[i]=='*')||(s[i]=='-')||(s[i]=='/')){
            float value = variables::getInstance()->getVarFromName(var).getVal();
            allVars+=var+"="+ to_string(value)+";";
            var="";
        }
    }
    if (var!=""){
        float value = variables::getInstance()->getVarFromName(var).getVal();
        allVars+=var+"="+ to_string(value)+";";
    }

    if (allVars!=""){
        i->setVariables(allVars);
    }
    Expression *e=i->interpret(s);
    return e->calculate();
}



command::command() {}

int PrintCommand::execute(int i, vector<string> v) {
    unordered_map<string, varObj*> *m =variables::getInstance()->getNameMap();
    unordered_map<string, varObj*> simMap =variables::getInstance()->getSimMap();
    if (m->find(v[i + 1]) != m->end()) {
        //cout << variables::getInstance()->getVarFromName(v[i + 1]).getVal() <<endl;
        ////
        string simName = variables::getInstance()->getVarFromName(v[i + 1]).getSim();
        cout << variables::getInstance()->getVarFromSim(simName).getVal();
        cout<<"              print";
    } else {
        cout << v[i + 1] << endl;
    }

    numOfPar = 1;
    return numOfPar + 1;
}

int SleepCommand::execute(int i, vector<string> v) {
    sleep(atof(v[i + 1].c_str()) / 1000);
    numOfPar = 1;
    return numOfPar + 1;
}
