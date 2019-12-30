
#ifndef FLIGHT1_VARIABLES_H
#define FLIGHT1_VARIABLES_H

#include <string>
#include <unordered_map>
#include <mutex>
#include <queue>
#include "varObj.h"

using namespace std;

class variables {

private:
    variables();
    static variables *instance;
    unordered_map<string, varObj*> nameMap;
    unordered_map<string, varObj*> simMap;
    mutex mutex_lock;
    void initialize();
public:
    unordered_map<string, vector <string> > funcMap;
    static variables *getInstance();
    string nameArr[36];
    queue<varObj> q;
    void setVarByName(string name, float value);
    void addVar(string name, string s, float value, bool f);
    void setVarBySim(string sim, float value);
    float getValueByName(string name);
    unordered_map<string,varObj*> getNameMap();
    vector<pair<string, float>> getChangedVars();
    ~variables();
};

#endif //FLIGHT1_VARIABLES_H
