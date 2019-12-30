
#include <iostream>
#include <string>
#include "command.h"
#include "variables.h"

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
