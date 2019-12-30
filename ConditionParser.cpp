
#include <string>
#include "command.h"
#include "parser.h"
#include <algorithm>

// Set the command field of the condition parser:
void ConditionParser::setCom(class command innerCom) {
    com = innerCom;
}

// Execute the condition command:
int ConditionParser::execute(int i, vector<string> v ) {
    int index = com.execute(i,v);
    return index;
}

// Execute if command:
int ifCommand::execute(int i, vector<string> v) {
    int index = 0;
    // check if condition is satisfied and get the index of last string in the if command:
    index = checkStatus(i,v, index);
    // create a vector of lines to parse:
    vector<string> newVector;
    while (v[i + index] != "}"){
        newVector.push_back(v[i + index]);
        index++;
    }
    if (status) {
        //do the condition in loop:
        parser *p = new parser(newVector);
        p->parse();
    }
    // return the index after '}':
    return index + 1;
}

// Execute loop command:
int loopCommand::execute(int i, vector<string> v ) {
    numOfPar = 0;
    int start = i;
    int index = 0;
    // check if the condition is satisfied and get index of last string in loop:
    index = checkStatus(i,v, index);
    numOfPar = 0;
    vector<string> newVector;
    // create a vector to parse:
    i = i + index;
    while ((v[i] != "}")){
        newVector.push_back(v[i]);
        i++;
        numOfPar++;
    }
    // parse the strings in vector:
    parser *p = new parser(newVector);
    while (status){
        p->parse();
        status= false;
        checkStatus(start, v, index);
    }
    return numOfPar + 1 + index;
}

// Check if a condition is satisfied:
int ConditionParser::checkStatus(int i, vector<string> v, int index){
    // while expression {...} :
    bool enter = false;
    if (v[i + 2] == "{") {
        float v1 = express(v[i+1]);
        if (v1 > 0){
            enter = true;
            status = true;
            index = 3;
        }
    }
    float v1 = express(v[i + 1]);
    float v2 = express(v[i + 3]);
    // while v1 == v2 {...} :
    if (v[i + 4] == "{"){
        index = 5;
        if (v[i + 2] == "=="){
            if (v1 == v2){
                status = true;
                enter = true;

            }
        }
        if (v[i + 2] == ">="){
            if (v1 >= v2){
                status = true;
                enter = true;

            }
        }
        if (v[i + 2] == "<="){
            if (v1 <= v2){
                status = true;
                enter = true;

            }
        }
        if (v[i + 2] == "!="){
            if (v1 != v2){
                status = true;
                enter = true;

            }
        }
        if (v[i + 2] == ">"){
            if (v1 > v2){
                status = true;
                enter = true;

            }
        }
        if (v[i + 2] == "<"){
            if (v1 < v2 ){
                status = true;
                enter = true;

            }
        }
    }
    if (!enter){
        status = false;
    }
    return index;
}

// Constructor:
ConditionParser::ConditionParser(string cond){
    if (cond.compare("if")){
        command *a = new ifCommand;
        this->setCom(*a);
    }
    if (cond.compare("while")){
        command *a = new loopCommand;
        this->setCom(*a);
    }
}
