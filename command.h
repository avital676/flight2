//
// Created by noa on 12/12/2019.
//

#ifndef UNTITLED6_COMMAND_H
#define UNTITLED6_COMMAND_H

#include <map>
#include <vector>


using namespace std;



class command {
private:
    void getMng(void (&mng)());
public:
    command();
    int numOfPar;
    virtual int execute(int, vector<string>){} ;
    double express(string s);

};

void openServer(string p, bool &open);

class openServerCommand: public command {
public:
    int numOfPar = 1;
    //void openServer(string p, bool &open);
    int execute(int, vector<string>) override ;
};

void clientMng(string port, string ip);

class ConnectCommand : public command{
public:
    int numOfPar = 2;
    int execute(int, vector<string>) override ;
};

class DefineVarCommand : public command {
public:
    int numOfPar = 2;
    int execute(int, vector<string>) override ;
};
class ConditionParser: public command{
    command com;
public:
    ConditionParser(){}
    ConditionParser(string);
    void setCom(command a);
    int execute(int, vector<string>) override;

};
class ifCommand: public ConditionParser{
public:
    //int numOfPar = ;
    bool status = false;
    ifCommand(){}
    int execute(int, vector<string>) override ;

    };

class loopCommand: public ConditionParser{
public:
    bool status = false;
    void checkStatus(int i, vector<string> v, int index);

        int execute(int, vector<string>) override ;
};

#endif //UNTITLED6_COMMAND_H
