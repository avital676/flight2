//
// Created by avital on 12/12/2019.
//

#include "variables.h"
#include <string>
#include <iostream>
#include "string.h"
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
//    cout<<"start add var"<<endl;
//    cout<<"name -  ";
//    cout<<name<<endl;
//    cout<<"sim -  ";
//    cout<<s<<endl;
//    cout<<"value -  ";
  //  cout<<value<<endl;
    mutex_lock.lock();
    varObj* v = new varObj();
    v->setSim(s);
    v->setVal(value);
    v->setF(f);
    nameMap[name] = v;
    simMap[s] = v;
    mutex_lock.unlock();
//    cout<<"stop add var"<<endl;
}

void variables::setVarByName(string name, float value) {
    mutex_lock.lock();
    if(nameMap.find(name) != nameMap.end()) {
        nameMap.find(name)->second->setVal(value);
    }
    varObj *v = nameMap.find(name)->second;
    q.push(*v);
    mutex_lock.unlock();
}

void variables::setVarBySim(string sim, float value) {
    mutex_lock.lock();
    if(simMap.find(sim) != simMap.end()) {
        simMap.find(sim)->second->setVal(value);
    }
    mutex_lock.unlock();
}

float variables::getValueByName(string name) {
    return nameMap[name]->getVal();
}

bool variables::getFbyName(string name) {
    return nameMap[name]->getF();
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
    //varObj *v0 = new varObj;
    string name;
    name = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    nameArr[0] = name;
    //v0->setSim("/instrumentation/airspeed-indicator/indicated-speed-kt");
    //simMap[name] = v0;

    //varObj *v1 = new varObj;
    name = "/sim/time/warp";
    nameArr[1] = name;
    //v1->setSim("/sim/time/warp");
    //simMap[name] = v1;

    //varObj *v2 = new varObj;
    name = "/controls/switches/magnetos";
    nameArr[2] = name;
    //v2->setSim("/controls/switches/magnetos");
    //simMap[name] = v2;

    //varObj *v3 = new varObj;
    name = "/instrumentation/heading-indicator/offset-deg";
    nameArr[3] = name;
    //v3->setSim("/instrumentation/heading-indicator/offset-deg");
    //simMap[name] = v3;

    //varObj *v4 = new varObj;
    name = "/instrumentation/altimeter/indicated-altitude-ft";
    nameArr[4] = name;
    //v4->setSim("/instrumentation/altimeter/indicated-altitude-ft");
    //simMap[name] = v4;

    //varObj *v5 = new varObj;
    name = "/instrumentation/altimeter/pressure-alt-ft";
    nameArr[5] = name;
    //v5->setSim("/instrumentation/altimeter/pressure-alt-ft");
    //simMap[name] = v5;

    //varObj *v6 = new varObj;
    name = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    nameArr[6] = name;
    //v6->setSim("/instrumentation/attitude-indicator/indicated-pitch-deg");
    //simMap[name] = v6;

    //varObj *v7 = new varObj;
    name = "/instrumentation/attitude-indicator/indicated-roll-deg";
    nameArr[7] = name;
    //v7->setSim("/instrumentation/attitude-indicator/indicated-roll-deg");
    //simMap[name] = v7;

    //varObj *v8 = new varObj;
    name = "/instrumentation/attitude-indicator/internal-pitch-deg";
    nameArr[8] = name;
    //v8->setSim("/instrumentation/attitude-indicator/internal-pitch-deg");
    //simMap[name] = v8;

    //varObj *v9 = new varObj;
    name = "/instrumentation/attitude-indicator/internal-roll-deg";
    nameArr[9] = name;
    //v9->setSim("/instrumentation/attitude-indicator/internal-roll-deg");
    //simMap[name] = v9;

    //varObj *v10 = new varObj;
    name = "/instrumentation/encoder/indicated-altitude-ft";
    nameArr[10] = name;
    //v10->setSim("/instrumentation/encoder/indicated-altitude-ft");
    //simMap[name] = v10;


    //varObj *v11 = new varObj;
    name = "/instrumentation/encoder/pressure-alt-ft";
    nameArr[11] = name;
    //v11->setSim("/instrumentation/encoder/pressure-alt-ft");
    //simMap[name] = v11;

    //varObj *v12 = new varObj;
    name = "/instrumentation/gps/indicated-altitude-ft";
    nameArr[12] = name;
    //v12->setSim("/instrumentation/gps/indicated-altitude-ft");
    //simMap[name] = v12;

    //varObj *v13 = new varObj;
    name = "/instrumentation/gps/indicated-ground-speed-kt";
    nameArr[13] = name;
   // v13->setSim("/instrumentation/gps/indicated-ground-speed-kt");
    //simMap[name] = v13;

    //varObj *v14 = new varObj;
    name = "/instrumentation/gps/indicated-vertical-speed";
    nameArr[14] = name;
   // v14->setSim("/instrumentation/gps/indicated-vertical-speed");
    //simMap[name] = v14;

    //varObj *v15 = new varObj;
    name = "/instrumentation/heading-indicator/indicated-heading-deg";
    nameArr[15] = name;
    //v15->setSim("/instrumentation/heading-indicator/indicated-heading-deg");
   // simMap[name] = v15;

    //varObj *v16 = new varObj;
    name = "/instrumentation/magnetic-compass/indicated-heading-deg";
    nameArr[16] = name;
    //v16->setSim("/instrumentation/magnetic-compass/indicated-heading-deg");
    //simMap[name] = v16;

    //varObj *v17 = new varObj;
    name = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    nameArr[17] = name;
    //v17->setSim("/instrumentation/slip-skid-ball/indicated-slip-skid");
    //simMap[name] = v17;

   // varObj *v18 = new varObj;
    name = "/instrumentation/turn-indicator/indicated-turn-rate";
    nameArr[18] = name;
    //v18->setSim("/instrumentation/turn-indicator/indicated-turn-rate");
   // simMap[name] = v18;

   // varObj *v19 = new varObj;
    name = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    nameArr[19] = name;
    //v19->setSim("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
  //  simMap[name] = v19;

   // varObj *v20 = new varObj;
    name = "/controls/flight/aileron";
    nameArr[20] = name;
    //v20->setSim("/controls/flight/aileron");
    //simMap[name] = v20;

    //varObj *v21 = new varObj;
    name = "/controls/flight/elevator";
    nameArr[21] = name;
    //v21->setSim("/controls/flight/elevator");
    //simMap[name] = v21;

   // varObj *v22 = new varObj;
    name = "/controls/flight/rudder";
    nameArr[22] = name;
   // v22->setSim("/controls/flight/rudder");
    //simMap[name] = v22;

   // varObj *v23 = new varObj;
    name = "/controls/flight/flaps";
    nameArr[23] = name;
   // v23->setSim("/controls/flight/flaps");
   // simMap[name] = v23;

   // varObj *v24 = new varObj;
    name = "/controls/engines/engine/throttle";
    nameArr[24] = name;
   // v24->setSim("/controls/engines/engine/throttle");
   // simMap[name] = v24;

   // varObj *v25 = new varObj;
    name = "/controls/engines/current-engine/throttle";
    nameArr[25] = name;
   // v25->setSim("/controls/engines/current-engine/throttle");
   // simMap[name] = v25;

   // varObj *v26 = new varObj;
    name = "/controls/switches/master-avionics";
    nameArr[26] = name;
   // v26->setSim("/controls/switches/master-avionics");
   // simMap[name] = v26;

   // varObj *v27 = new varObj;
    name = "/controls/switches/starter";
    nameArr[27] = name;
   // v27->setSim("/controls/switches/starter");
   // simMap[name] = v27;

   // varObj *v28 = new varObj;
    name = "/engines/active-engine/auto-start";
    nameArr[28] = name;
   // v28->setSim("/engines/active-engine/auto-start");
   // simMap[name] = v28;

   // varObj *v29 = new varObj;
    name = "/controls/flight/speedbrake";
    nameArr[29] = name;
   // v29->setSim("/controls/flight/speedbrake");
   // simMap[name] = v29;

   // varObj *v30 = new varObj;
    name = "/sim/model/c172p/brake-parking";
    nameArr[30] = name;
   // v30->setSim("/sim/model/c172p/brake-parking");
   // simMap[name] = v30;

   // varObj *v31 = new varObj;
    name = "/controls/engines/engine/primer";
    nameArr[31] = name;
   // v31->setSim("/controls/engines/engine/primer");
   // simMap[name] = v31;

   // varObj *v32 = new varObj;
    name = "/controls/engines/current-engine/mixture";
    nameArr[32] = name;
    //v32->setSim("/controls/engines/current-engine/mixture");
   // simMap[name] = v32;

   // varObj *v33 = new varObj;
    name = "/controls/switches/master-bat";
    nameArr[33] = name;
   // v33->setSim("/controls/switches/master-bat");
   // simMap[name] = v33;

   // varObj *v34 = new varObj;
    name = "/controls/switches/master-alt";
    nameArr[34] = name;
   // v34->setSim("/controls/switches/master-alt");
   // simMap[name] = v34;

   // varObj *v35 = new varObj;
    name = "/engines/engine/rpm";
    nameArr[35] = name;
   // v35->setSim("/engines/engine/rpm");
  //  simMap[name] = v35;
}




