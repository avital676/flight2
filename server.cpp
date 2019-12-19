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
    unordered_map<string, varStruct> m = variables::getInstance()->getNameMap();
    string s = "";
    int i;
    int counter = 0;
    string name;
    for (i = 0; i < data.size(); i++) {
        if (data[i] != ',') {
            s += data[i];
        } else {
            name = variables::getInstance()->nameArr[counter];
            counter++;
            varStruct v = variables::getInstance()->getVar(name);
            v.value = stoi(s);
            variables::getInstance()->setVarInMap(name, v);
            s = "";
        }
    }
}



