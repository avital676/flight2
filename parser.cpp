//
// Created by avital on 12/12/2019.
//

#include <string>
#include <vector>
#include "parser.h"
#include "variables.h"
#include <iostream>
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
    c = new PrintCommand;
    comMap["Print"] = c;
    c = new SleepCommand;
    comMap["Sleep"] = c;
}

void parser::parse() {
    int i = 0;
    command* c;
    while (i < token.size()) {
        //unordered_map<string, varObj*> m =variables::getInstance()->nameMap;
        unordered_map<string, varObj*> m =variables::getInstance()->getNameMap();
        //unordered_map<string, varObj*> simMap =variables::getInstance()->simMap;
        if (comMap.find(token[i]) != comMap.end()) {
            c = comMap[token[i]];
            i += c->execute(i, token);
        } else if (m.find(token[i]) != m.end()) {
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

