//
// Created by noa on 12/12/2019.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include "string"
#include "command.h"
#include "client.h"
#include "variables.h"
#include "server.h"
#include "parser.h"
#include "Interpreter.h"


void openServer(string p, bool open) {
    volatile bool work = true;
    server* ser = new server(&work);
    int socketSer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketSer == -1) {
        cerr << "Could not create socket" << endl;
        exit(1);
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port= htons(stoi(p));
    if (bind(socketSer, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Could not bind the socket to an IP" << endl;
        exit(1);
    }
    if (listen(socketSer, 5) == -1) {
        cerr << "Error during listening command" << endl;
        exit(1);
    }
    open = true;
    // accept a client:
    int client_socket = accept(socketSer, (struct sockaddr *) &address,
                               (socklen_t*) &address);
    if (client_socket == -1) {
        cerr << "Error accepting client" << endl;
        exit(1);
    }
    // read from client:
    char buffer[1024] = {0};
    int valRead;
    while (work) {
        valRead = read(client_socket, buffer, 1024);
        // insert values to map:
        ser->dataToMap(buffer);
    }
}

void clientMng(string port, string ip) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        cerr << "Could not create a socket" << endl;
        exit(1);
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    const char* ipConst = ip.c_str();
    address.sin_addr.s_addr = inet_addr(ipConst);
    address.sin_port = htons(stoi(port));
    // request connection with server:
    int is_connect = connect(client_socket, (struct sockaddr*) &address, sizeof(address));
    if (is_connect == -1) {
        cerr << "Could not connect to host server" << endl;
        exit(1);
    } else {
        // client is connected
    }
}


int openServerCommand::execute(int i, vector<string> v) {
    cout << "openserver execute" << endl;
    volatile bool open = false;
    //thread serverT(openServer, v[i + 1], open);
    while (!open) {
        sleep(3);
    }
    return numOfPar + 1;
}

int ConnectCommand::execute(int i, vector<string> v) {
    thread clientT(clientMng, v[i + 1], v[i + 2]);
    return numOfPar + 1;
}

int DefineVarCommand::execute(int i, vector<string> v) {
    cout << "dedine var execute" << endl;
    varStruct *var = new varStruct;
    string varName;
    if (v[i] == "var") {
        varName = v[i + 1];
        if (v[i + 2] == "->") {
            var->sim = v[i + 4];
        } else if (v[i + 2] == "<-") {
            // search sim in simMap:
            string sim = v[i + 4];
            var = variables::getInstance()->searchSim(sim);
        } else if (v[i + 2] == "=") {
            var->value = express(v[i + 3]);
        }
        variables::getInstance()->setVarInMap(varName, *var);
    } else {
        varName = v[i];
        *var = variables::getInstance()->getVar(v[i]);
        var->value = express(v[i + 2]);
        variables::getInstance()->setVarInMap(varName, *var);
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
        varStruct v1=variables::getInstance()->getVar(v[i + 1]);
        if (v1.value>0){
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
    checkStatus(i,v, index);
    vector<string> newVector;
    int countPare=0;
    //make new vector for parser.
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

    while (status){
        // do the condition in loop
        parser *p = new parser(newVector);
        p->parse();
        checkStatus(i, v, index);
    }
    // return the next place after }.
    return index+1;

}

void loopCommand::checkStatus(int i, vector<string> v, int index){
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
}

double command::express(string s){
Interpreter *i = new Interpreter();
string allVars="";
string var="";
for (int i =0; i < s.length(); i++){
    if ((s[i]<'z')&&(s[i]>'a')){
        var+=s[i];
        while((s[i]!='+')&&(s[i]!='*')&&(s[i]!='-')&&(s[i]!='/')){
            var+=s[i];
        }
        float value = variables::getInstance()->getVar(var).value;
        allVars+=var+"="+ to_string(value)+";";
    }
}
if (allVars!=""){
    i->setVariables(allVars);
}
Expression *e=i->interpret(s);
return e->calculate();
}

command::command() {}

