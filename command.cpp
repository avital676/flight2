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
#include <algorithm>
void acceptFromSimu(int client_socket) {
    cout << "waiting to read from simu" << endl;
    server ser = new server();
    //reading from client
    char buffer[1024] = {0};
    int valread;
    while (keepThreads::getInstance()->is_open) {
        valread = read( client_socket , buffer, 1024);
        //cout << "read" << endl;
        ser.dataToMap(buffer);
    }
}

void sendToSimu(int client_socket) {
    while(keepThreads::getInstance()->is_open) {
        vector<pair<string, float>> changedVars = variables::getInstance()->getChangedVars();
        if(changedVars.empty()) {
            sleep(0.1);
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
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    address.sin_port = htons(port);
    // request connection with server:
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        cerr << "Could not connect to host server" << endl;
        return -2;
    } else { // client is connected
        cout << "opened client" << endl;
        keepThreads::getInstance()->clientTread = thread(sendToSimu, client_socket);
        keepThreads::getInstance()->clientTread.detach();
    }

}

int openServerCommand::execute(int i, vector<string> v) {
    cout << "openserver execute" << endl;
    int port = stoi(v[i + 1]);
    int opened = openSer(port);
    while (opened != 0) {
        opened = openSer(port);
    }
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
    varObj* var;
    string varName;
    // define new var:
    if (v[i] == "var") {
        varName = v[i + 1];
        if (v[i + 2] == "->") {
            variables::getInstance()->addVar(v[i + 1], v[i + 4], 0, true);
            numOfPar = 4;
        } else if (v[i + 2] == "<-") {
            variables::getInstance()->addVar(v[i + 1], v[i + 4], 0, false);
            numOfPar = 4;
        } else if (v[i + 2] == "=") {
            //cout<<v[i+1]<<endl;
            //cout<<v[i+3]<<endl;
            float value = express(v[i + 3]);

            variables::getInstance()->addVar(v[i + 1], "", value, false);
            numOfPar = 3;
        }
    } else { // var already defined:
        float value = express(v[i + 2]);
        variables::getInstance()->setVarByName(v[i], value);
        numOfPar = 2;
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
    int index = com.execute(i,v);
    cout<<"confition Parser execute"<<endl;
    return index;
}

int ifCommand::execute(int i, vector<string> v) {
    int index;
    if (v[i+2] == "{"){
        float value1 = variables::getInstance()->getValueByName(v[i + 1]);
        if (value1 > 0){
            status= true;
            index=3;
        }
    }
    //cout<<v[i+1]<<endl;
    double v1= express(v[i+1]);
   // cout<<v1<<endl;
   // cout<<v[i+3]<<endl;
    double v2= express(v[i+3]);
   // cout<<v2<<endl;
    //if var == exp  {...}
    if (v[i+4] == "{"){
        index=5;
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
    //cout<<status<<endl;
    vector<string> newVector;
    //make new vector for parser.
    int countPare=0;
    while (v[i+index] != "}"){
        newVector.push_back(v[i+index]);
        index++;
    }
   // cout<<"if"<<endl;
    if (status){
        //do the condition in loop
        parser *p = new parser(newVector);
        p->parse();
    }
    //return the next place after }.
    cout<<index+1<<endl;
    return index + 1;

}

int loopCommand::execute(int i, vector<string> v ) {
    numOfPar=0;
    int start = i;
    int index = 0;
   // cout<<" i befoure while -"+to_string(i)<<endl;
    index = checkStatus(i,v, index);
  //  cout<<"2 i befoure while -"+to_string(i)<<endl;
    numOfPar = 0;
    vector<string> newVector;
    int countPare=0;
    //make new vector for parser.
  //  cout<<"3 i befoure while -"+to_string(i)<<endl;
    i=i+index;
    while ((v[i] != "}")){
        newVector.push_back(v[i]);
        i++;
        numOfPar++;
    }
  //  cout<<"i after while - "+ to_string(i)<<endl;
  //  cout<<"num of par - "+ to_string(numOfPar)<<endl;
    parser *p = new parser(newVector);

    while (status){
        // do the condition in loop
        //cout<<"loop"<<endl;
        p->parse();
        status= false;
        checkStatus(start, v, index);
    }
    // return the next place after }.
  //  cout<<"after while"<<endl;
    //cout<<v[index+1]<<endl;
    //cout<<index<<endl;
    return numOfPar + 1+ index;

}

int loopCommand::checkStatus(int i, vector<string> v, int index){
    // while break{...}
   // cout<<"check status"<<endl;
    bool enter=false;
    if (v[i+2]=="{"){
        double v1 = express(v[i+1]);
        if (v1>0){
            enter=true;
            status= true;
            index=3;
        }
    }
    double v1 = express(v[i+1]);
   // cout<<v1;
  //  cout<<"->  right"<<endl;
    double v2 = express(v[i+3]);
   // cout<<v2;
   // cout<<"->  left"<<endl;
    //while breaks == exp{...}
    if (v[i+4] == "{"){
        index=5;
        if (v[i+2] == "=="){
            if (v1 == v2){
                status= true;
                enter=true;

            }
        }
        if (v[i+2] == ">="){
            if (v1 >= v2){
                status= true;
                enter=true;

            }
        }
        if (v[i+2] == "<="){
            if (v1 <= v2){
                status= true;
                enter=true;

            }
        }
        if (v[i+2] == "!="){
            if (v1!=v2){
                status= true;
                enter=true;

            }
        }
        if (v[i+2] == ">"){
            if (v1 >v2){
                status= true;
                enter=true;

            }
        }
        if (v[i+2] == "<"){
            if (v1 <v2 ){
                status= true;
                enter=true;

            }
        }
    }
    if (enter== false){
        status= false;
    }
    return index;
}

double command::express(string s){

Interpreter *i = new Interpreter();
string allVars="";
string var="";
string flag;
    s.erase(remove(s.begin(), s.end(), ' '), s.end());

for (int i =0; i < s.length(); i++){
        //find variables
        if ((s[i]<='z')&&(s[i]>='a')) {
            while((i<s.length())&&(s[i]!='+')&&(s[i]!='-')&&(s[i]!='*')&&(s[i]!='/')&&(s[i]!=')')&&(s[i]!='(')) {
                var += s[i];

                i++;

            }
        }
        //cout<<var<<endl;
        if((s[i]=='+')||(s[i]=='*')||(s[i]=='-')||(s[i]=='/')){
            if (var!="") {


                float value = variables::getInstance()->getValueByName(var);

                allVars += var + "=" + to_string(value) + ";";
                var = "";
            }
        }
    }
    if (var!=""){

        float value = variables::getInstance()->getValueByName(var);

        if (value<0){
            allVars+=var+"="+""+to_string(value)+";";

        }
        else{
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

//int PrintCommand::execute(int i, vector<string> v) {
//    if (v[i + 1][0] == '"') {
//        string strToPrint = v[i + 1].substr(1,v[i + 1].size() - 1);
//        strToPrint.pop_back();
//        cout << strToPrint << endl;
//    } else {
//        cout << express(v[i + 1]) << endl;
//    }
//    numOfPar = 1;
//    return numOfPar + 1;
//}

int PrintCommand::execute(int i, vector<string> v) {
    unordered_map<string, varObj*> m =variables::getInstance()->getNameMap();
    if (m.find(v[i + 1]) != m.end()) {
        float value = m[v[i+1]]->getVal();
        cout<<value<<endl;
    } else {
        //string strToPrint = v[i + 1].substr(1,v[i + 1].size() - 1);
        //strToPrint.pop_back();
        //cout << strToPrint << endl;
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
string command::spaceDelete(string input){
    string output ="";
    for (int i=0; i<input.length(); i++){
        if (input[i]==' '){
            i++;
        }
        else{
            output+=input[i];
        }
    }
    return output;
}
