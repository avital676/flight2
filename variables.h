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
    unordered_map<string, varObj*> nameMap;
    unordered_map<string, varObj*> simMap;
    mutex mutex_lock;
    void initialize();

public:

    static variables *getInstance();
    string nameArr[36];
    queue<varObj> q;
    void setVarByName(string name, float value);
    void addVar(string name, string s, float value, bool f);
    void setVarBySim(string sim, float value);
    float getValueByName(string name);
    unordered_map<string,varObj*> getNameMap();
    vector<pair<string, float>> getChangedVars();
    float getValueBySimName(string simname);
};

#endif //FLIGHT1_VARIABLES_H

