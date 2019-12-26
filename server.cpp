//
// Created by avital on 16/12/2019.
//

#include "server.h"
#include "variables.h"
#include <string.h>
#include <iostream>

using namespace std;



server::server(bool do_work) {
    work = do_work;
}

void server::dataToMap(char* data) {
    string s = "";
    int i;
    int counter = 0;
    string sim_name;
    string word1=string(data);
    if (word1 == "") {
        cout << "empty input" << endl;
    }
    //cout << word1 << endl;
    for (i = 0; i < word1.size(); i++) {
        if (data[i] != ',') {
            s += word1[i];
        } else {
            if (counter > 34) {
                break;
            }
           float value = stof(s.c_str());
           variables::getInstance()->setVarBySim(variables::getInstance()->nameArr[counter], value);
//           if (counter == 7) {
//               cout << "roll: " + s << endl;
//           }
//           if (counter == 20) {
//               cout << "ailron: " + s << endl;
//           }
//            if (counter == 21) {
//                cout << "elevator: " + s << endl;
//            }
//            if (counter == 8) {
//                cout << "pitch: " + s << endl;
//            }
           counter++;
           s = "";
        }
    }
    if (s!="") {
        float value = stof(s.c_str());
        variables::getInstance()->setVarBySim(variables::getInstance()->nameArr[counter], value);
        s = "";
    }


}




