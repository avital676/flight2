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
//
void variables::initialize(){
    varStruct *v0 = new varStruct;
    string name;
    name = "airspeed-indicator_indicated-speed-kt";
    nameArr[0] = name;
    v0->sim= "/instrumentation/airspeed-indicator/indicated-speed-kt";
    simMap.insert({name, v0});
    //simMap[name]= v;

    varStruct *v1 = new varStruct;
    name = "time_warp";
    nameArr[1] = name;
    v1->sim= "/sim/time/warp";
    simMap[name]= v1;

    varStruct *v2 = new varStruct;
    name = "switches_magnetos";
    nameArr[2] = name;
    v2->sim= "/controls/switches/magnetos";
    simMap[name]= v2;

    varStruct *v3 = new varStruct;
    name = "heading-indicator_offset-deg";
    nameArr[3] = name;
    v3->sim= "/instrumentation/heading-indicator/offset-deg";
    simMap[name]= v3;

    varStruct *v4 = new varStruct;
    name = "altimeter_indicated-altitude-ft";
    nameArr[4] = name;
    v4->sim= "/instrumentation/altimeter/indicated-altitude-ft";
    simMap[name]= v4;

    varStruct *v5 = new varStruct;
    name = "altimeter_pressure-alt-ft";
    nameArr[5] = name;
    v5->sim= "/instrumentation/altimeter/pressure-alt-ft";
    simMap[name]= v5;

    varStruct *v6 = new varStruct;
    name = "attitude-indicator_indicated-pitch-deg";
    nameArr[6] = name;
    v6->sim= "/instrumentation/attitude-indicator/indicated-pitch-deg";
    simMap[name]= v6;

    varStruct *v7 = new varStruct;
    name = "attitude-indicator_indicated-roll-deg";
    nameArr[7] = name;
    v7->sim= "/instrumentation/attitude-indicator/indicated-roll-deg";
    simMap[name]= v7;

    varStruct *v8 = new varStruct;
    name = "attitude-indicator_internal-pitch-deg";
    nameArr[8] = name;
    v8->sim= "/instrumentation/attitude-indicator/internal-pitch-deg";
    simMap[name]= v8;

    varStruct *v9 = new varStruct;
    name = "attitude-indicator_internal-roll-deg";
    nameArr[9] = name;
    v9->sim= "/instrumentation/attitude-indicator/internal-roll-deg";
    simMap[name]= v9;

    varStruct *v10 = new varStruct;
    name = "encoder_indicated-altitude-ft";
    nameArr[10] = name;
    v10->sim= "/instrumentation/encoder/indicated-altitude-ft";
    simMap[name]= v10;

    varStruct *v11 = new varStruct;
    name = "encoder_pressure-alt-ft";
    nameArr[11] = name;
    v11->sim= "/instrumentation/encoder/pressure-alt-ft";
    simMap[name]= v11;

    varStruct *v12 = new varStruct;
    name = "gps_indicated-altitude-ft";
    nameArr[12] = name;
    v12->sim= "/instrumentation/gps/indicated-altitude-ft";
    simMap[name]= v12;

    varStruct *v13 = new varStruct;
    name = "gps_indicated-ground-speed-kt";
    nameArr[13] = name;
    v13->sim= "//instrumentation/gps/indicated-ground-speed-kt";
    simMap[name]= v13;

    varStruct *v14 = new varStruct;
    name = "gps_indicated-vertical-speed";
    nameArr[14] = name;
    v14->sim= "/instrumentation/gps/indicated-vertical-speed";
    simMap[name]= v14;

    varStruct *v15 = new varStruct;
    name = "indicated-heading-deg";
    nameArr[15] = name;
    v15->sim= "/instrumentation/heading-indicator/indicated-heading-deg";
    simMap[name]= v15;

    varStruct *v16 = new varStruct;
    name = "magnetic-compass_indicated-heading-deg";
    nameArr[16] = name;
    v16->sim= "/instrumentation/magnetic-compass/indicated-heading-deg";
    simMap[name]= v16;

    varStruct *v17 = new varStruct;
    name = "slip-skid-ball_indicated-slip-skid";
    nameArr[17] = name;
    v17->sim= "/instrumentation/slip-skid-ball/indicated-slip-skid";
    simMap[name]= v17;

    varStruct *v18 = new varStruct;
    name = "turn-indicator_indicated-turn-rate";
    nameArr[18] = name;
    v18->sim= "/instrumentation/turn-indicator/indicated-turn-rate";
    simMap[name]= v18;

    varStruct *v19 = new varStruct;
    name = "vertical-speed-indicator_indicated-speed-fpm";
    nameArr[19] = name;
    v19->sim= "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    simMap[name]= v19;

    varStruct *v20 = new varStruct;
    name = "tflight_aileron";
    nameArr[20] = name;
    v20->sim= "/controls/flight/aileron";
    simMap[name]= v20;

    varStruct *v21 = new varStruct;
    name = "flight_rudder";
    nameArr[21] = name;
    v21->sim= "/controls/flight/rudder";
    simMap[name]= v21;

    varStruct *v22 = new varStruct;
    name = "flight_flaps";
    nameArr[22] = name;
    v22->sim= "/controls/flight/flaps";
    simMap[name]= v22;

    varStruct *v23 = new varStruct;
    name = "engine_throttle";
    nameArr[23] = name;
    v23->sim= "/controls/engines/engine/throttle";
    simMap[name]= v23;

    varStruct *v24 = new varStruct;
    name = "current-engine_throttle";
    nameArr[24] = name;
    v24->sim= "/controls/engines/current-engine/throttle";
    simMap[name]= v24;

    varStruct *v25 = new varStruct;
    name = "switches_master-avionics";
    nameArr[25] = name;
    v25->sim= "/controls/switches/master-avionics";
    simMap[name]= v25;

    varStruct *v26 = new varStruct;
    name = "switches_starter";
    nameArr[26] = name;
    v26->sim= "/controls/switches/starter";
    simMap[name]= v26;

    varStruct *v27 = new varStruct;
    name = "active-engine_auto-start";
    nameArr[27] = name;
    v27->sim= "/engines/active-engine/auto-start";
    simMap[name]= v27;

    varStruct *v28 = new varStruct;
    name = "flight_speedbrake";
    nameArr[28] = name;
    v28->sim= "/controls/flight/speedbrake";
    simMap[name]= v28;

    varStruct *v29 = new varStruct;
    name = "c172p_brake-parking";
    nameArr[29] = name;
    v29->sim= "/sim/model/c172p/brake-parking";
    simMap[name]= v29;

    varStruct *v30 = new varStruct;
    name = "engine_primer";
    nameArr[30] = name;
    v30->sim= "/controls/engines/engine/primer";
    simMap[name]= v30;

    varStruct *v31 = new varStruct;
    name = "current-engine_mixture";
    nameArr[31] = name;
    v31->sim= "/controls/engines/current-engine/mixture";
    simMap[name]= v31;

    varStruct *v32 = new varStruct;
    name = "switches_master-bat";
    nameArr[32] = name;
    v32->sim= "/controls/switches/master-bat";
    simMap[name]= v32;

    varStruct *v33 = new varStruct;
    name = "switches_master-alt";
    nameArr[33] = name;
    v33->sim= "/controls/switches/master-alt";
    simMap[name]= v33;

    varStruct *v34 = new varStruct;
    name = "engine_rpm";
    nameArr[34] = name;
    v34->sim= "/engines/engine/rpm";
    simMap[name]= v34;
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


