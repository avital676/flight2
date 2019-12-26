
#ifndef EX1_INTERPRETER_H
#define EX1_INTERPRETER_H

#include "ex1.h"
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <queue>

using namespace std;

class Interpreter {
private:
    queue<string> postfix; // postfix string queue
    map<string, int> preMap; // precedence map
    map<string, float> vMap; // variables map
public:
    Interpreter();
    Expression* interpret(string);
    int getPre(string);
    void makeQueue(string);
    Expression* makeExp();
    bool varExist(string);
    Expression *convertToVar(string);
    void setVariables(string);
};

#endif //EX1_INTERPRETER_H
