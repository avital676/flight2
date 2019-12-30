
#include <string>
#include <vector>
#include "parser.h"
#include "variables.h"

using namespace std;

// Constructor- initialize commands map:
parser::parser(vector<string> v) {
    token = v;
    command *c = new openServerCommand;
    comMap["openDataServer"] = c;
    c = new ConnectCommand;
    comMap["connectControlClient"] = c;
    c = new DefineVarCommand;
    comMap["var"] = c;
    c = new loopCommand;
    comMap["while"] = c;
    c = new ifCommand;
    comMap["if"] = c;
    c = new PrintCommand;
    comMap["Print"] = c;
    c = new SleepCommand;
    comMap["Sleep"] = c;
}

// Parse the token vector:
void parser::parse() {
    int i = 0;
    command *c;
    while (i < token.size()) {
        if (token[i] == "") {
            i++;
        }
        unordered_map<string, varObj *> m = variables::getInstance()->getNameMap();
        if (comMap.find(token[i]) != comMap.end()) { // current token is a command:
            c = comMap[token[i]];
            i += c->execute(i, token);
        } else if (m.find(token[i]) != m.end()) { // current token is an existing variable
            i += comMap["var"]->execute(i, token);
        } else { // current token is a new var declaration
            c = new DefineVarCommand;
            i += c->execute(i, token);
        }
    }
}

parser::~parser() {
    delete comMap["sleep"];
    delete comMap["openDataServer"];
    delete comMap["connectControlClient"];
    delete comMap["var"];
    delete comMap["while"];
    delete comMap["if"];
    delete comMap["Print"];
}
