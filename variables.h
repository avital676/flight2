//
// Created by noa on 16/12/2019.
//

#ifndef FLIGHT1_VARIABLES_H
#define FLIGHT1_VARIABLES_H

#include <string>
#include <map>
#include <mutex>

using namespace std;

struct varStruct {
    float value;
    string sim;
};

class variables {

private:
    variables();
    static variables *instance;
    map<string, varStruct> nameMap;
    map<string, varStruct*> simMap;
    mutex mutex_lock;
    void initialize();

public:
    static variables *getInstance();
    map<string, varStruct *> getSimMap();
    map<string, varStruct> getNameMap();
    void setVarInMap(string v, varStruct s);
    varStruct getVar(string v);
    varStruct* searchSim(string s);
    void printNameMap();
    };

#endif //FLIGHT1_VARIABLES_H

