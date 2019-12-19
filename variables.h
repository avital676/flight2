//
// Created by noa on 16/12/2019.
//

#ifndef FLIGHT1_VARIABLES_H
#define FLIGHT1_VARIABLES_H

#include <string>
#include <unordered_map>
#include <mutex>
#include <queue>

using namespace std;

struct varStruct {
    float value;
    string sim;
};

class variables {

private:
    variables();
    static variables *instance;
    unordered_map<string, varStruct> nameMap;
    unordered_map<string, varStruct*> simMap;
    mutex mutex_lock;
    void initialize();

public:
    static variables *getInstance();
    unordered_map<string, varStruct*> getSimMap();
    unordered_map<string, varStruct> getNameMap();
    void setVarInMap(string v, varStruct s);
    //varStruct getVar(string v);
    varStruct* searchSim(string s);
    string nameArr[35];
    queue<varStruct> q;
    varStruct getVarFromName(string v);
    varStruct* getVarFromSim(string v);
};

#endif //FLIGHT1_VARIABLES_H

