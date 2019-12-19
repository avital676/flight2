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

varStruct variables::getVar(string v) {
    return nameMap[v];
}

void variables::initialize(){
    varStruct *v = new varStruct;
    string name;
    name = "airspeed-indicator_indicated-speed-kt";
    nameArr[0] = name;
    v->sim= "/instrumentation/airspeed-indicator/indicated-speed-kt";
    simMap[name]= v;

    name="altimeter_indicated-altitude-ft";
    nameArr[1]=name;
    v->sim= "/instrumentation/altimeter/indicated-altitude-ft";
    simMap["altimeter_indicated-altitude-ft"]= v;

    name="altimeter_pressure-alt-ft";
    nameArr[2]=name;
    v->sim= "/instrumentation/altimeter/pressure-alt-ft";
    simMap["altimeter_pressure-alt-ft"]= v;

    name="attitude-indicator_indicated-pitch-deg";
    nameArr[3]=name;
    v->sim= "/instrumentation/attitude-indicator/indicated-pitch-deg";
    simMap["attitude-indicator_indicated-pitch-deg"]= v;

    name="attitude-indicator_indicated-roll-deg";
    nameArr[4]=name;
    v->sim= "/instrumentation/attitude-indicator/indicated-roll-deg";
    simMap["attitude-indicator_indicated-roll-deg"]= v;

    name="attitude-indicator_internal-pitch-deg";
    nameArr[5]=name;
    v->sim= "/instrumentation/attitude-indicator/internal-pitch-deg";
    simMap["attitude-indicator_internal-pitch-deg"]= v;

    name="attitude-indicator_internal-roll-deg";
    nameArr[6]=name;
    v->sim= "/instrumentation/attitude-indicator/internal-roll-deg";
    simMap["attitude-indicator_internal-roll-deg"]= v;

    name="encoder_indicated-altitude-ft";
    nameArr[7]=name;
    v->sim= "/instrumentation/encoder/indicated-altitude-ft";
    simMap["encoder_indicated-altitude-ft"]= v;

    name="encoder_pressure-alt-ft";
    nameArr[8]=name;
    v->sim= "/instrumentation/encoder/pressure-alt-ft";
    simMap["encoder_pressure-alt-ft"]= v;

    name="gps_indicated-altitude-ft";
    nameArr[9]=name;
    v->sim= "/instrumentation/gps/indicated-altitude-ft";
    simMap["gps_indicated-altitude-ft"]= v;

    name="gps_indicated-ground-speed-kt";
    nameArr[10]=name;
    v->sim= "/instrumentation/gps/indicated-ground-speed-kt";
    simMap["gps_indicated-ground-speed-kt"]= v;

    name="gps_indicated-vertical-speed";
    nameArr[11]=name;
    v->sim= "/instrumentation/gps/indicated-vertical-speed";
    simMap["gps_indicated-vertical-speed"]= v;

    name="indicated-heading-deg";
    nameArr[12]=name;
    v->sim= "/instrumentation/heading-indicator/indicated-heading-deg";
    simMap["indicated-heading-deg"]= v;

    name="magnetic-compass_indicated-heading-deg";
    nameArr[13]=name;
    v->sim= "/instrumentation/magnetic-compass/indicated-heading-deg";
    simMap["magnetic-compass_indicated-heading-deg"]= v;

    name="slip-skid-ball_indicated-slip-skid";
    nameArr[14]=name;
    v->sim= "/instrumentation/slip-skid-ball/indicated-slip-skid";
    simMap["slip-skid-ball_indicated-slip-skid"]= v;

    name="turn-indicator_indicated-turn-rate";
    nameArr[15]=name;
    v->sim= "/instrumentation/turn-indicator/indicated-turn-rate";
    simMap["turn-indicator_indicated-turn-rate"]= v;

    name="vertical-speed-indicator_indicated-speed-fpm";
    nameArr[16]=name;
    v->sim= "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    simMap["vertical-speed-indicator_indicated-speed-fpm"]= v;

    name="flight_aileron";
    nameArr[17]=name;
    v->sim= "/controls/flight/aileron</";
    simMap["flight_aileron"]= v;

    name="flight_elevator";
    nameArr[18]=name;
    v->sim= "/controls/flight/elevator";
    simMap["flight_elevator"]= v;

    name="flight_rudder";
    nameArr[19]=name;
    v->sim= "/controls/flight/rudder";
    simMap["flight_rudder"]= v;

    name="flight_flaps";
    nameArr[20]=name;
    v->sim= "/controls/flight/flaps";
    simMap["flight_flaps"]= v;

    name="engine_throttle";
    nameArr[21]=name;
    v->sim= "/controls/engines/engine/throttle";
    simMap["engine_throttle"]= v;

    name="engine_rpm";
    nameArr[22]=name;
    v->sim= "/engines/engine/rpm";
    simMap["engine_rpm"]= v;

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


