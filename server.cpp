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
    unordered_map<string, varObj> nameMap = variables::getInstance()->getNameMap();
    unordered_map<string, varObj*> simMap = variables::getInstance()->getSimMap();
    string s = "";
    int i;
    int counter = 0;
    string sim_name;
    size_t index1 = string(data).find("\n");
    string word1=string(data);
    string word2=word1.substr(index1 + 1,word1.length());
    size_t index2=word2.find("\n");
    //only one \n
    if (word2 == ""){
        word1=word1.substr(0,index1);
    }
    else{
        word1=word2.substr(0, index2);
    }
    ////// CHECK /n take only between 2 \n!!!!!!!!!!

    for (i = 0; i < word1.size(); i++) {
        if (data[i] != ',') {
            s += word1[i];
        } else {
            sim_name = variables::getInstance()->nameArr[counter];
            varObj *v = variables::getInstance()->getVarFromSim(sim_name);
            cout << v->getSim() << endl;
            v->setVal(stof(s.c_str()));
            variables::getInstance()->setVarInSimMap(sim_name, v);
            counter++;

            s = "";

        }
    }
    if (s!="") {
        cout << s << endl;
        sim_name = variables::getInstance()->nameArr[counter];
        unordered_map<string, varObj*> m = variables::getInstance()->getSimMap();
        varObj *v = variables::getInstance()->getVarFromSim(sim_name);
        cout << v->getSim() << endl;
        cout << v->getVal() << endl;
        v->setVal(stof(s.c_str()));
        variables::getInstance()->setVarInSimMap(sim_name, v);
        s = "";
    }
}

//void server::dataToMap(char* data) {
//    unordered_map<string, varStruct> nameMap = variables::getInstance()->getNameMap();
//    unordered_map<string, varStruct*> simMap = variables::getInstance()->getSimMap();
//    string s = "";
//    int i;
//    int counter = 0;
//    string sim_name;
//    size_t index1 = string(data).find("\n");
//    string word1=string(data);
//    string word2=word1.substr(index1 + 1,word1.length());
//    size_t index2=word2.find("\n");
//    //only one \n
//    if (word2 == ""){
//        word1=word1.substr(0,index1);
//    }
//    else{
//        word1=word2.substr(0, index2);
//    }
//    ////// CHECK /n take only between 2 \n!!!!!!!!!!
//    cout<<word1<<endl;
//    for (i = 0; i < word1.size(); i++) {
//        if (data[i] != ',') {
//            s += word1[i];
//        } else {
//            // if(counter<=35) {
//            cout << s << endl;
//            sim_name = variables::getInstance()->nameArr[counter];
//            //cout << variables::getInstance()->getVarFromSim(name)->sim << endl;
//            varStruct *v = variables::getInstance()->getVarFromSim(sim_name);
//            v->value = stof(s.c_str());
//            variables::getInstance()->setVarInSimMap(sim_name, *v);
//            counter++;
//            //cout << s <<endl;
//            s = "";
//            // }
//        }
//    }
//    sim_name = variables::getInstance()->nameArr[counter];
//    varStruct *v = variables::getInstance()->getVarFromSim(sim_name);
//    v->value = stof(s.c_str());
//    variables::getInstance()->setVarInSimMap(sim_name, *v);
//}




