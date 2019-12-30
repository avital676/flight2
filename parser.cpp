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
    bool enter = false;
    command *c;
    while (i < token.size()) {
        if (token[i] == "") {
            i++;
        }
        unordered_map<string, varObj *> m = variables::getInstance()->getNameMap();
        if (comMap.find(token[i]) != comMap.end()) {
            c = comMap[token[i]];
            i += c->execute(i, token);
            enter = true;
        } else if (m.find(token[i]) != m.end()) {
            i += comMap["var"]->execute(i, token);
            enter = true;
        } else {
            c = new DefineVarCommand;
            i += c->execute(i, token);
            enter = true;
        }

    }
}
parser::~parser(){
    delete comMap["sleep"];
    delete comMap["openDataServer"];
    delete comMap["connectControlClient"];
    delete comMap["var"];
    delete comMap["while"];
    delete comMap["if"];
    delete comMap["Print"];
}
//        if (token[i]=="takeoff") {
//            cout<<"func enterence"<<endl;
//            if (variables::getInstance()->funcMap.find(token[i]) != variables::getInstance()->funcMap.end()) {
//                vector<string> temp = variables::getInstance()->funcMap.find(token[i])->second;
//                command *c = new FuncCommand(token[i + 1]);
//                i += c->execute(0, temp);
//            } else {
//                string name = token[i];
//                cout<<name<<endl;
//                i++;
//                vector<string> temp;
//                int pair =0;
//                while ((token[i] != "}")||(pair!=0)) {
//                    if (token[i].compare("{")) {
//                        pair++;
//                    }
//                    if (token[i].compare("}")){
//                        pair--;
//                    }
//                    temp.push_back(token[i]);
//                    i++;
//                }
//                variables::getInstance()->funcMap[name] = temp;
//            }
//        }
