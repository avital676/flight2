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

//unordered_map<string, varObj*> variables::getSimMap() {
//    return simMap;
//}

void variables::setVarInNameMap(string v, varObj& s) {
    mutex_lock.lock();
    nameMap[v] = &s;
    mutex_lock.unlock();
}

void variables::setVarInSimMap(string v, varObj& s) {
    mutex_lock.lock();
    simMap[v] = &s;
    mutex_lock.unlock();
}

varObj* variables::getVarFromName(string v) {
    return nameMap[v];
}

varObj* variables::getVarFromSim(string v) {
    return simMap[v];
}

void variables::initialize() {
    //varObj *v0 = new varObj;
    string name;
    name = "airspeed-indicator_indicated-speed-kt";
    nameArr[0] = name;
    //v0->setSim("/instrumentation/airspeed-indicator/indicated-speed-kt");
    //simMap[name] = v0;

    //varObj *v1 = new varObj;
    name = "time_warp";
    nameArr[1] = name;
    //v1->setSim("/sim/time/warp");
    //simMap[name] = v1;

    //varObj *v2 = new varObj;
    name = "switches_magnetos";
    nameArr[2] = name;
    //v2->setSim("/controls/switches/magnetos");
    //simMap[name] = v2;

    //varObj *v3 = new varObj;
    name = "heading-indicator_offset-deg";
    nameArr[3] = name;
    //v3->setSim("/instrumentation/heading-indicator/offset-deg");
    //simMap[name] = v3;

    //varObj *v4 = new varObj;
    name = "altimeter_indicated-altitude-ft";
    nameArr[4] = name;
    //v4->setSim("/instrumentation/altimeter/indicated-altitude-ft");
    //simMap[name] = v4;

    //varObj *v5 = new varObj;
    name = "altimeter_pressure-alt-ft";
    nameArr[5] = name;
    //v5->setSim("/instrumentation/altimeter/pressure-alt-ft");
    //simMap[name] = v5;

    //varObj *v6 = new varObj;
    name = "attitude-indicator_indicated-pitch-deg";
    nameArr[6] = name;
    //v6->setSim("/instrumentation/attitude-indicator/indicated-pitch-deg");
    //simMap[name] = v6;

    //varObj *v7 = new varObj;
    name = "attitude-indicator_indicated-roll-deg";
    nameArr[7] = name;
    //v7->setSim("/instrumentation/attitude-indicator/indicated-roll-deg");
    //simMap[name] = v7;

    //varObj *v8 = new varObj;
    name = "attitude-indicator_internal-pitch-deg";
    nameArr[8] = name;
    //v8->setSim("/instrumentation/attitude-indicator/internal-pitch-deg");
    //simMap[name] = v8;

    //varObj *v9 = new varObj;
    name = "attitude-indicator_internal-roll-deg";
    nameArr[9] = name;
    //v9->setSim("/instrumentation/attitude-indicator/internal-roll-deg");
    //simMap[name] = v9;

    //varObj *v10 = new varObj;
    name = "encoder_indicated-altitude-ft";
    nameArr[10] = name;
    //v10->setSim("/instrumentation/encoder/indicated-altitude-ft");
    //simMap[name] = v10;


    //varObj *v11 = new varObj;
    name = "encoder_pressure-alt-ft";
    nameArr[11] = name;
    //v11->setSim("/instrumentation/encoder/pressure-alt-ft");
    //simMap[name] = v11;

    //varObj *v12 = new varObj;
    name = "gps_indicated-altitude-ft";
    nameArr[12] = name;
    //v12->setSim("/instrumentation/gps/indicated-altitude-ft");
    //simMap[name] = v12;

    //varObj *v13 = new varObj;
    name = "gps_indicated-ground-speed-kt";
    nameArr[13] = name;
   // v13->setSim("/instrumentation/gps/indicated-ground-speed-kt");
    //simMap[name] = v13;

    //varObj *v14 = new varObj;
    name = "gps_indicated-vertical-speed";
    nameArr[14] = name;
   // v14->setSim("/instrumentation/gps/indicated-vertical-speed");
    //simMap[name] = v14;

    //varObj *v15 = new varObj;
    name = "indicated-heading-deg";
    nameArr[15] = name;
    //v15->setSim("/instrumentation/heading-indicator/indicated-heading-deg");
   // simMap[name] = v15;

    //varObj *v16 = new varObj;
    name = "magnetic-compass_indicated-heading-deg";
    nameArr[16] = name;
    //v16->setSim("/instrumentation/magnetic-compass/indicated-heading-deg");
    //simMap[name] = v16;

    //varObj *v17 = new varObj;
    name = "slip-skid-ball_indicated-slip-skid";
    nameArr[17] = name;
    //v17->setSim("/instrumentation/slip-skid-ball/indicated-slip-skid");
    //simMap[name] = v17;

   // varObj *v18 = new varObj;
    name = "turn-indicator_indicated-turn-rate";
    nameArr[18] = name;
    //v18->setSim("/instrumentation/turn-indicator/indicated-turn-rate");
   // simMap[name] = v18;

   // varObj *v19 = new varObj;
    name = "vertical-speed-indicator_indicated-speed-fpm";
    nameArr[19] = name;
    //v19->setSim("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
  //  simMap[name] = v19;

   // varObj *v20 = new varObj;
    name = "flight_aileron";
    nameArr[20] = name;
    //v20->setSim("/controls/flight/aileron");
    //simMap[name] = v20;

    //varObj *v21 = new varObj;
    name = "flight_elevator";
    nameArr[21] = name;
    //v21->setSim("/controls/flight/elevator");
    //simMap[name] = v21;

   // varObj *v22 = new varObj;
    name = "flight_rudder";
    nameArr[22] = name;
   // v22->setSim("/controls/flight/rudder");
    //simMap[name] = v22;

   // varObj *v23 = new varObj;
    name = "flight_flaps";
    nameArr[23] = name;
   // v23->setSim("/controls/flight/flaps");
   // simMap[name] = v23;

   // varObj *v24 = new varObj;
    name = "engine_throttle";
    nameArr[24] = name;
   // v24->setSim("/controls/engines/engine/throttle");
   // simMap[name] = v24;

   // varObj *v25 = new varObj;
    name = "current-engine_throttle";
    nameArr[25] = name;
   // v25->setSim("/controls/engines/current-engine/throttle");
   // simMap[name] = v25;

   // varObj *v26 = new varObj;
    name = "switches_master-avionics";
    nameArr[26] = name;
   // v26->setSim("/controls/switches/master-avionics");
   // simMap[name] = v26;

   // varObj *v27 = new varObj;
    name = "switches_starter";
    nameArr[27] = name;
   // v27->setSim("/controls/switches/starter");
   // simMap[name] = v27;

   // varObj *v28 = new varObj;
    name = "active-engine_auto-start";
    nameArr[28] = name;
   // v28->setSim("/engines/active-engine/auto-start");
   // simMap[name] = v28;

   // varObj *v29 = new varObj;
    name = "flight_speedbrake";
    nameArr[29] = name;
   // v29->setSim("/controls/flight/speedbrake");
   // simMap[name] = v29;

   // varObj *v30 = new varObj;
    name = "c172p_brake-parking";
    nameArr[30] = name;
   // v30->setSim("/sim/model/c172p/brake-parking");
   // simMap[name] = v30;

   // varObj *v31 = new varObj;
    name = "engine_primer";
    nameArr[31] = name;
   // v31->setSim("/controls/engines/engine/primer");
   // simMap[name] = v31;

   // varObj *v32 = new varObj;
    name = "current-engine_mixture";
    nameArr[32] = name;
    //v32->setSim("/controls/engines/current-engine/mixture");
   // simMap[name] = v32;

   // varObj *v33 = new varObj;
    name = "switches_master-bat";
    nameArr[33] = name;
   // v33->setSim("/controls/switches/master-bat");
   // simMap[name] = v33;

   // varObj *v34 = new varObj;
    name = "switches_master-alt";
    nameArr[34] = name;
   // v34->setSim("/controls/switches/master-alt");
   // simMap[name] = v34;

   // varObj *v35 = new varObj;
    name = "engine_rpm";
    nameArr[35] = name;
   // v35->setSim("/engines/engine/rpm");
  //  simMap[name] = v35;
}

//unordered_map<string, varObj*>* variables::getNameMap() {
//    return &nameMap;
//}

varObj* variables::searchSim(string s) {
    unordered_map<string, varObj*> m = variables::getInstance()->simMap;
    unordered_map<string, varObj*>::iterator it;
    for ( it = m.begin(); it != m.end(); it++ ) {
        if (it->second->getSim() == s) {
            // return pointer to the valStruct that has this sim:
            return it->second;
        }
    }
   // return ;
}


