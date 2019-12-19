//
// Created by avital on 12/12/2019.
//

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

unordered_map<string, varStruct*> variables::getSimMap() {
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

varStruct variables::getVarFromName(string v) {
    return nameMap[v];
}

varStruct* variables::getVarFromSim(string v) {
    return simMap[v];
}

void variables::initialize(){
    varStruct *v = new varStruct;
    string name;
    name = "airspeed-indicator_indicated-speed-kt";
    nameArr[0] = name;
    v->sim= "/instrumentation/airspeed-indicator/indicated-speed-kt";
    simMap[name]= v;

    name = "switches_magnetos";
    nameArr[0] = name;
    v->sim= "/controls/switches/magnetos";
    simMap[name]= v;

    name = "heading-indicator_offset-deg";
    nameArr[0] = name;
    v->sim= "//instrumentation/heading-indicator/offset-deg";
    simMap[name]= v;

    name = "altimeter_indicated-altitude-ft";
    nameArr[0] = name;
    v->sim= "/instrumentation/altimeter/indicated-altitude-ft";
    simMap[name]= v;

    name = "altimeter_pressure-alt-ft";
    nameArr[0] = name;
    v->sim= "/instrumentation/altimeter/pressure-alt-ft";
    simMap[name]= v;

    name = "attitude-indicator_indicated-pitch-deg";
    nameArr[0] = name;
    v->sim= "/instrumentation/attitude-indicator/indicated-pitch-deg";
    simMap[name]= v;

    name = "attitude-indicator_indicated-roll-deg";
    nameArr[0] = name;
    v->sim= "/instrumentation/attitude-indicator/indicated-roll-deg";
    simMap[name]= v;

    name = "attitude-indicator_internal-pitch-deg";
    nameArr[0] = name;
    v->sim= "/instrumentation/attitude-indicator/internal-pitch-deg";
    simMap[name]= v;

    name = "attitude-indicator_internal-roll-deg";
    nameArr[0] = name;
    v->sim= "/instrumentation/attitude-indicator/internal-roll-deg";
    simMap[name]= v;

    name = "encoder_indicated-altitude-ft";
    nameArr[0] = name;
    v->sim= "/instrumentation/encoder/indicated-altitude-ft";
    simMap[name]= v;

    name = "encoder_pressure-alt-ft";
    nameArr[0] = name;
    v->sim= "/instrumentation/encoder/pressure-alt-ft";
    simMap[name]= v;

    name = "gps_indicated-altitude-ft";
    nameArr[0] = name;
    v->sim= "/instrumentation/gps/indicated-altitude-ft";
    simMap[name]= v;

    name = "gps_indicated-ground-speed-kt";
    nameArr[0] = name;
    v->sim= "//instrumentation/gps/indicated-ground-speed-kt";
    simMap[name]= v;

    name = "gps_indicated-vertical-speed";
    nameArr[0] = name;
    v->sim= "/instrumentation/gps/indicated-vertical-speed";
    simMap[name]= v;

    name = "indicated-heading-deg";
    nameArr[0] = name;
    v->sim= "/instrumentation/heading-indicator/indicated-heading-deg";
    simMap[name]= v;

    name = "magnetic-compass_indicated-heading-deg";
    nameArr[0] = name;
    v->sim= "/instrumentation/magnetic-compass/indicated-heading-deg";
    simMap[name]= v;

    name = "slip-skid-ball_indicated-slip-skid";
    nameArr[0] = name;
    v->sim= "/instrumentation/slip-skid-ball/indicated-slip-skid";
    simMap[name]= v;

    name = "turn-indicator_indicated-turn-rate";
    nameArr[0] = name;
    v->sim= "/instrumentation/turn-indicator/indicated-turn-rate";
    simMap[name]= v;

    name = "vertical-speed-indicator_indicated-speed-fpm";
    nameArr[0] = name;
    v->sim= "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    simMap[name]= v;

    name = "tflight_aileron";
    nameArr[0] = name;
    v->sim= "/controls/flight/aileron";
    simMap[name]= v;

    name = "flight_rudder";
    nameArr[0] = name;
    v->sim= "/controls/flight/rudder";
    simMap[name]= v;

    name = "flight_flaps";
    nameArr[0] = name;
    v->sim= "/controls/flight/flaps";
    simMap[name]= v;

    name = "engine_throttle";
    nameArr[0] = name;
    v->sim= "/controls/engines/engine/throttle";
    simMap[name]= v;

    name = "current-engine_throttle";
    nameArr[0] = name;
    v->sim= "/controls/engines/current-engine/throttle";
    simMap[name]= v;

    name = "switches_master-avionics";
    nameArr[0] = name;
    v->sim= "/controls/switches/master-avionics";
    simMap[name]= v;

    name = "switches_starter";
    nameArr[0] = name;
    v->sim= "/controls/switches/starter";
    simMap[name]= v;

    name = "active-engine_auto-start";
    nameArr[0] = name;
    v->sim= "/engines/active-engine/auto-start";
    simMap[name]= v;

    name = "flight_speedbrake";
    nameArr[0] = name;
    v->sim= "/controls/flight/speedbrake";
    simMap[name]= v;

    name = "c172p_brake-parking";
    nameArr[0] = name;
    v->sim= "/sim/model/c172p/brake-parking";
    simMap[name]= v;

    name = "engine_primer";
    nameArr[0] = name;
    v->sim= "/controls/engines/engine/primer";
    simMap[name]= v;

    name = "current-engine_mixture";
    nameArr[0] = name;
    v->sim= "/controls/engines/current-engine/mixture";
    simMap[name]= v;

    name = "switches_master-bat";
    nameArr[0] = name;
    v->sim= "/controls/switches/master-bat";
    simMap[name]= v;

    name = "switches_master-alt";
    nameArr[0] = name;
    v->sim= "/controls/switches/master-alt";
    simMap[name]= v;

    name = "engine_rpm";
    nameArr[0] = name;
    v->sim= "/engines/engine/rpm";
    simMap[name]= v;
}

unordered_map<string, varStruct> variables::getNameMap() {
    return nameMap;
}

varStruct* variables::searchSim(string s) {
    unordered_map<string, varStruct*> m = variables::getInstance()->getSimMap();
    unordered_map<string, varStruct*>::iterator it;
    for ( it = m.begin(); it != m.end(); it++ ) {
        if (it->second->sim == s) {
            // return pointer to the valStruct that has this sim:
            return it->second;
        }
    }
    return nullptr;
}


