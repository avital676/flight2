//
// Created by avital on 12/12/2019.
//

#include "variables.h"
#include <string>
#include <iostream>

using namespace std;

variables* variables::instance = 0;

using namespace std;

variables::variables() {
    initialize();
}

variables* variables::getInstance() {
    if (!instance)
        instance = new variables;
    return instance;
}

void variables::addVar(string name, string s, float value, bool f) {
    mutex_lock.lock();
    varObj* v = new varObj();
    v->setSim(s);
    v->setVal(value);
    v->setF(f);
    nameMap[name] = v;
    simMap[s] = v;
    mutex_lock.unlock();
}

void variables::setVarByName(string name, float value) {
    mutex_lock.lock();
//    if (name =="aileron"){
//        cout<<value;
//        cout<<" value from set"<<endl;
//    }
    if(nameMap.find(name) != nameMap.end()) {
        nameMap.find(name)->second->setVal(value);
    }
//    if (name =="aileron"){
//        cout<<getValueByName("aileron");
//        cout<<" value from set"<<endl;
//    }
    varObj *v = nameMap.find(name)->second;
    q.push(*v);
    mutex_lock.unlock();
}

void variables::setVarBySim(string sim, float value) {
    mutex_lock.lock();
//    if (sim == "/instrumentation/heading-indicator/offset-deg") {
//        cout<<sim<<endl;
//        cout<<value<<endl;
//    }
    if(simMap.find(sim) != simMap.end()) {
        //cout << simMap.find(sim)->second->getVal() << endl;
        simMap.find(sim)->second->setVal(value);
        //cout << simMap.find(sim)->second->getVal() << endl;
    }
    mutex_lock.unlock();
}

float variables::getValueByName(string name) {
    return nameMap[name]->getVal();
}



unordered_map<string,varObj*> variables::getNameMap() {
    return nameMap;
}

vector<pair<string, float>> variables::getChangedVars() {
    vector<pair<string, float>> changedVars;
    while (!q.empty()) {
        pair<string, float> p;
        p.first = q.front().getSim();
        p.second = q.front().getVal();
        changedVars.push_back(p);
        q.pop();
    }
    return changedVars;
}

void variables::initialize() {
    string name;
    name = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    nameArr[0] = name;

    name = "/sim/time/warp";
    nameArr[1] = name;

    name = "/controls/switches/magnetos";
    nameArr[2] = name;

    name = "/instrumentation/heading-indicator/offset-deg";
    nameArr[3] = name;

    name = "/instrumentation/altimeter/indicated-altitude-ft";
    nameArr[4] = name;

    name = "/instrumentation/altimeter/pressure-alt-ft";
    nameArr[5] = name;

    name = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    nameArr[6] = name;

    name = "/instrumentation/attitude-indicator/indicated-roll-deg";
    nameArr[7] = name;

    name = "/instrumentation/attitude-indicator/internal-pitch-deg";
    nameArr[8] = name;

    name = "/instrumentation/attitude-indicator/internal-roll-deg";
    nameArr[9] = name;

    name = "/instrumentation/encoder/indicated-altitude-ft";
    nameArr[10] = name;

    name = "/instrumentation/encoder/pressure-alt-ft";
    nameArr[11] = name;

    name = "/instrumentation/gps/indicated-altitude-ft";
    nameArr[12] = name;

    name = "/instrumentation/gps/indicated-ground-speed-kt";
    nameArr[13] = name;

    name = "/instrumentation/gps/indicated-vertical-speed";
    nameArr[14] = name;

    name = "/instrumentation/heading-indicator/indicated-heading-deg";
    nameArr[15] = name;

    name = "/instrumentation/magnetic-compass/indicated-heading-deg";
    nameArr[16] = name;

    name = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    nameArr[17] = name;

    name = "/instrumentation/turn-indicator/indicated-turn-rate";
    nameArr[18] = name;

    name = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    nameArr[19] = name;

    name = "/controls/flight/aileron";
    nameArr[20] = name;

    name = "/controls/flight/elevator";
    nameArr[21] = name;

    name = "/controls/flight/rudder";
    nameArr[22] = name;

    name = "/controls/flight/flaps";
    nameArr[23] = name;

    name = "/controls/engines/engine/throttle";
    nameArr[24] = name;

    name = "/controls/engines/current-engine/throttle";
    nameArr[25] = name;

    name = "/controls/switches/master-avionics";
    nameArr[26] = name;

    name = "/controls/switches/starter";
    nameArr[27] = name;

    name = "/engines/active-engine/auto-start";
    nameArr[28] = name;

    name = "/controls/flight/speedbrake";
    nameArr[29] = name;

    name = "/sim/model/c172p/brake-parking";
    nameArr[30] = name;

    name = "/controls/engines/engine/primer";
    nameArr[31] = name;

    name = "/controls/engines/current-engine/mixture";
    nameArr[32] = name;

    name = "/controls/switches/master-bat";
    nameArr[33] = name;

    name = "/controls/switches/master-alt";
    nameArr[34] = name;

    name = "/engines/engine/rpm";
    nameArr[35] = name;
}
