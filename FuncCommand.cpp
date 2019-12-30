//
// Created by avital on 30/12/2019.
//

#include "command.h"
#include "variables.h"
#include "parser.h"

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