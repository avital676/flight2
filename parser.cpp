//
// Created by avital on 12/12/2019.
//

#include <string>
#include <vector>
#include "parser.h"
#include "variables.h"

using namespace std;

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
}

void parser::parse() {
    int i = 0;
    command* c;
    //map<string,varStruct> m = variables::getInstance()->getNameMap();
    while (i < token.size()) {
        if (comMap.find(token[i]) != comMap.end()) {
            c = comMap[token[i]];
            i += c->execute(i, token);
        } else if (variables::getInstance()->getNameMap().find(token[i]) != variables::getInstance()->getNameMap().end()) {
            i+=comMap["var"] -> execute(i, token);
//            varStruct var = variables::getInstance()->getVar(token[i]);
//            var.value = c->express(token[i + 2]);
//            variables::getInstance()->setVarInMap(token[i], var);
        } else {
            c = new DefineVarCommand;
            i += c->execute(i, token);
        }
    }
}

