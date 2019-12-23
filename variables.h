//
// Created by noa on 16/12/2019.
//

#ifndef FLIGHT1_VARIABLES_H
#define FLIGHT1_VARIABLES_H

#include <string>
#include <unordered_map>
#include <mutex>
#include <queue>
#include "varObj.h"

using namespace std;

//struct varStruct {
//    float value;
//    string sim;
//    bool set;
//};

class variables {

private:
    variables();
    static variables *instance;
    //unordered_map<string, varObj*> nameMap;
    //unordered_map<string, varObj*> simMap;
    mutex mutex_lock;
    void initialize();

public:
    unordered_map<string, varObj*> nameMap= unordered_map<string, varObj*>();
    unordered_map<string, varObj*> simMap=unordered_map<string, varObj*>();
    static variables *getInstance();
    //unordered_map<string, varObj*> getSimMap();
    //unordered_map<string, varObj*>* getNameMap();
    void setVarInNameMap(string v, varObj& s);
    void setVarInSimMap(string v, varObj& s);
    //varStruct getVar(string v);
    varObj* searchSim(string s);
    string nameArr[36];
    queue<varObj> q;
    varObj* getVarFromName(string v);
    varObj* getVarFromSim(string v);

};

#endif //FLIGHT1_VARIABLES_H

