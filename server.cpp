//
// Created by avital on 16/12/2019.
//

#include "server.h"
#include "variables.h"

using namespace std;




server::server(bool do_work) {
    work = do_work;
}



void server::dataToMap(string data) {
    map<string, varStruct> m = variables::getInstance()->getNameMap();
    string s = "";
    int i;
    for (i = 0; i < data.size(); i++) {
        if (data[i] != ',') {
            s += data[i];
        } else {
            varStruct* v = variables::getInstance()->searchSim(s);
            v->value = stoi(s);
            s = "";
        }
    }
}


