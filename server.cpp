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
    unordered_map<string, varStruct> nameMap = variables::getInstance()->getNameMap();
    unordered_map<string, varStruct*> simMap = variables::getInstance()->getSimMap();
    string s = "";
    int i;
    int counter = 0;
    string name;
    size_t index1 = string(data).find("\n");
    string word1=string(data);
    string word2=word1.substr(index1,word1.length());
    size_t index2=word2.find("\n");
    //only one \n
    if (index2==string::npos){
        word1=word1.substr(0,index1);
    }
    else{
        word1=word1.substr(index1+1, index2);
    }
    ////// CHECK /n take only between 2 \n!!!!!!!!!!
    for (i = 0; i < strlen(data); i++) {
        if (data[i] != ',') {
            s += data[i];
        } else {
            if(counter<35) {
                name = variables::getInstance()->nameArr[counter];
                //cout << variables::getInstance()->getVarFromSim(name)->sim << endl;
                varStruct *v = variables::getInstance()->getVarFromSim(name);
                v->value = atof(s.c_str());
                variables::getInstance()->setVarInMap(name, *v);
                counter++;
                s = "";
            }
        }
    }
}



