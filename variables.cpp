//
// Created by avital on 12/12/2019.
//

#include <iostream>
#include "variables.h"
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

map<string, varStruct*> variables::getSimMap() {
    return simMap;
}



void variables::setVarInMap(string v, varStruct s) {
    mutex_lock.lock();
    nameMap[v] = s;
//        if (s == "->") {
//            vMap[v].right = true;
//        } else if (s == "<-") {
//            vMap[v].right = false;
//        } else if (isdigit(s[0])) {
//            vMap[v].value = stoi(s);
//        } else {
//            vMap[v].sim = s;
//        }
    mutex_lock.unlock();
}

varStruct variables::getVar(string v) {
    return nameMap[v];
}

void variables::initialize(){
    varStruct *v = new varStruct;
    v->sim= "/instrumentation/airspeed-indicator/indicated-speed-kt";
    simMap["airspeed-indicator_indicated-speed-kt"]= v;

    v->sim= "/instrumentation/altimeter/indicated-altitude-ft";
    simMap["altimeter_indicated-altitude-ft"]= v;

    v->sim= "/instrumentation/altimeter/pressure-alt-ft";
    simMap["altimeter_pressure-alt-ft"]= v;

    v->sim= "/instrumentation/attitude-indicator/indicated-pitch-deg";
    simMap["attitude-indicator_indicated-pitch-deg"]= v;

    v->sim= "/instrumentation/attitude-indicator/indicated-roll-deg";
    simMap["attitude-indicator_indicated-roll-deg"]= v;

    v->sim= "/instrumentation/attitude-indicator/internal-pitch-deg";
    simMap["attitude-indicator_internal-pitch-deg"]= v;

    v->sim= "/instrumentation/attitude-indicator/internal-roll-deg";
    simMap["attitude-indicator_internal-roll-deg"]= v;

    v->sim= "/instrumentation/encoder/indicated-altitude-ft";
    simMap["encoder_indicated-altitude-ft"]= v;

    v->sim= "/instrumentation/encoder/pressure-alt-ft";
    simMap["encoder_pressure-alt-ft"]= v;

    v->sim= "/instrumentation/gps/indicated-altitude-ft";
    simMap["gps_indicated-altitude-ft"]= v;

    v->sim= "/instrumentation/gps/indicated-ground-speed-kt";
    simMap["gps_indicated-ground-speed-kt"]= v;

    v->sim= "/instrumentation/gps/indicated-vertical-speed";
    simMap["gps_indicated-vertical-speed"]= v;

    v->sim= "/instrumentation/heading-indicator/indicated-heading-deg";
    simMap["indicated-heading-deg"]= v;

    v->sim= "/instrumentation/magnetic-compass/indicated-heading-deg";
    simMap["magnetic-compass_indicated-heading-deg"]= v;

    v->sim= "/instrumentation/slip-skid-ball/indicated-slip-skid";
    simMap["slip-skid-ball_indicated-slip-skid"]= v;

    v->sim= "/instrumentation/turn-indicator/indicated-turn-rate";
    simMap["turn-indicator_indicated-turn-rate"]= v;

    v->sim= "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    simMap["vertical-speed-indicator_indicated-speed-fpm"]= v;

    v->sim= "/controls/flight/aileron</";
    simMap["flight_aileron"]= v;

    v->sim= "/controls/flight/elevator";
    simMap["flight_elevator"]= v;

    v->sim= "/controls/flight/rudder";
    simMap["flight_rudder"]= v;

    v->sim= "/controls/flight/flaps";
    simMap["flight_flaps"]= v;

    v->sim= "/controls/engines/engine/throttle";
    simMap["engine_throttle"]= v;

    v->sim= "/engines/engine/rpm";
    simMap["engine_rpm"]= v;
}

map<string, varStruct> variables::getNameMap() {
    return nameMap;
}

varStruct* variables::searchSim(string s) {
    map<string, varStruct*> m = variables::getInstance()->getSimMap();
    map<string, varStruct*>::iterator it;
    for ( it = m.begin(); it != m.end(); it++ ) {
        if (it->second->sim == s) {
            // return pointer to the valStruct that has this sim:
            return it->second;
        }
    }
    return nullptr;
}


