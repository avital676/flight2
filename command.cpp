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
  //  cout << "waiting to read from simu" << endl;
    server ser = new server();
    //reading from client
    char buffer[1024] = {0};
    int valread;
    while (keepThreads::getInstance()->is_open) {
        valread = read( client_socket , buffer, 1024);
        ser.dataToMap(buffer);
    }
}

void sendToSimu(int client_socket) {
    if (keepThreads::getInstance()->is_open== false){
        cout<<"client is close"<<endl;
    }
    while(keepThreads::getInstance()->is_open) {
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

int openSer(int port) {

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
      //  std::cout<<"Server is now listening ..."<<std::endl;
    }
  //  cout << port << endl;
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
      //  cout << "opened client" << endl;
        keepThreads::getInstance()->clientTread = thread(sendToSimu, client_socket);
       // keepThreads::getInstance()->clientTread.detach();
    }

}

int openServerCommand::execute(int i, vector<string> v) {
   // cout << "openserver execute" << endl;
    double calculate = express(v[i+1]);
    int port = (int)calculate;
    int opened = openSer(port);
    while (opened != 0) {
        opened = openSer(port);
    }
    return numOfPar + 1;
}

int ConnectCommand::execute(int i, vector<string> v) {
    double calculate = express(v[i+2]);
    int port = (int)calculate;
    openCli(port, v[i + 1]);
  //  cout << "client connected" << endl;
    return numOfPar + 1;
}

int DefineVarCommand::execute(int i, vector<string> v) {
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
 //   cout<<"confition Parser execute"<<endl;
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
    float v1= express(v[i+1]);
    float v2= express(v[i+3]);
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
    vector<string> newVector;
    //make new vector for parser.
    int countPare=0;
    while (v[i+index] != "}"){
        newVector.push_back(v[i+index]);
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
    numOfPar = 0;
    int start = i;
    int index = 0;
    index = checkStatus(i,v, index);
    numOfPar = 0;
    vector<string> newVector;
    int countPare=0;
    //make new vector for parser.
    i=i+index;
    while ((v[i] != "}")){
        newVector.push_back(v[i]);
        i++;
        numOfPar++;
    }
    parser *p = new parser(newVector);
    while (status){
        p->parse();
        status= false;
        checkStatus(start, v, index);
    }
    return numOfPar + 1+ index;
}

int loopCommand::checkStatus(int i, vector<string> v, int index){
    // while breaks{...}
    bool enter=false;
    if (v[i+2]=="{"){
        float v1 = express(v[i+1]);
        if (v1>0){
            enter=true;
            status= true;
            index=3;
        }
    }
    float v1 = express(v[i+1]);
    float v2 = express(v[i+3]);
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

float command::express(string s){
    Interpreter *i = new Interpreter();
    string allVars="";
    string var="";
    string flag;
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    for (int i =0; i < s.length(); i++){
        //find variables
        if ((s[i]<='z')&&(s[i]>='a')||(s[i]<='Z')&&(s[i]>='A')) {
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

    float result = e->calculate();
    return result;

}

command::command() {}


int PrintCommand::execute(int i, vector<string> v) {
    unordered_map<string, varObj*> m =variables::getInstance()->getNameMap();
    if (m.find(v[i + 1]) != m.end()) {
        float value = m[v[i+1]]->getVal();
        cout<<value<<endl;
    } else {
        //cut the " "
        string toPrint = v[i+1].substr(1, v[i+1].length()-2);
        cout << toPrint << endl;
    }
    numOfPar = 1;
    return numOfPar + 1;
}

int SleepCommand::execute(int i, vector<string> v) {
    float timeToSleep = express(v[i+1]);
    chrono::milliseconds duration((int)timeToSleep);
    this_thread::sleep_for(duration);

    numOfPar = 1;
    return numOfPar + 1;
}

string command::spaceDelete(string input) {
    string output = "";
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ' ') {
            i++;
        } else {
            output += input[i];
        }
    }
    return output;
}

FuncCommand::FuncCommand(string s){
    value = s;
}
int FuncCommand::execute(int i, vector<string> v ) {
    int found = v[0].find("var");
    string name="";
    found++;
    //add the var in the start
    if ((found != string::npos)) {
        while(found< v[0].length()) {
            name += v[0][found];
            found++;
        }
        variables::getInstance()->addVar(name, "", stof(this->value), false);
    }
    //delete the start of the vector
    v.erase(v.begin());
    v.erase(v.begin()+1);

    parser *p = new parser(v);
        p->parse();
        return 1;
    }

