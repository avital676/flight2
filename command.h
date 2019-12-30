
#ifndef UNTITLED6_COMMAND_H
#define UNTITLED6_COMMAND_H

#include <map>
#include <vector>

using namespace std;

// command class:
class command {
public:
    command();
    int numOfPar;
    virtual int execute(int, vector<string>){};
    float express(string s);
    ~command(){};
};

// open server command class:
class openServerCommand : public command {
public:
    int numOfPar = 1;
    int execute(int, vector<string>) override ;
    ~openServerCommand(){};
};

int openSer(int port);
void acceptFromSimu(int client_socket);
void dataToMap(char* data);

// connect command:
class ConnectCommand : public command {
public:
    int numOfPar = 2;
    int execute(int, vector<string>) override ;
    ~ConnectCommand(){};
};

int openCli(int port, string ip);

// define var command:
class DefineVarCommand : public command {
public:
    int numOfPar = 2;
    int execute(int, vector<string>) override ;
    ~DefineVarCommand(){};
};

// condition parser:
class ConditionParser: public command {
private:
    command com;
protected:
    bool status= false;
public:
    ConditionParser(){};
    ConditionParser(string);
    void setCom(command a);
    int execute(int, vector<string>) override;
    ~ConditionParser(){};
    int checkStatus(int i, vector<string> v, int index);

};

// if command:
class ifCommand: public ConditionParser{
public:
    ifCommand(){}
    int execute(int, vector<string>) override ;
    ~ifCommand(){};
};

// loop command:
class loopCommand: public ConditionParser{
public:
    int execute(int, vector<string>) override ;
    ~loopCommand(){};
};

// Print command:
class PrintCommand: public command {
public:
    int execute(int, vector<string>) override ;
    ~PrintCommand(){};
};

// Sleep command:
class SleepCommand: public command {
public:
    int execute(int, vector<string>) override ;
    ~SleepCommand(){};
};

#endif //UNTITLED6_COMMAND_H
