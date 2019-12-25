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
 //   cout<<"data"<<endl;
 //   cout<<data<<endl;
    string word1=string(data);
//    int index1 = word1.find("\n");
//    if (index1 < word1.length()) {
//        string word2 = word1.substr(index1 + 1, word1.length());
//        size_t index2 = word2.find(index1+1,"\n");
//        //only one \n
//        if (word2 == "") {
//            word1 = word1.substr(0, index1);
//        } else {
//            word1 = word2.substr(0, index2);
//        }
//    }
        if (word1 == "") {
            cout << "empty input" << endl;
        }

   // cout<<"after cut"<<endl;
   // cout << word1 << endl;
    for (i = 0; i < word1.size(); i++) {
        if (data[i] != ',') {
            s += word1[i];
        } else {
           // cout << s << endl;
            float value = stof(s.c_str());
            variables::getInstance()->setVarBySim(variables::getInstance()->nameArr[counter], value);
            counter++;
            s = "";

        }
    }
    if (s!="") {
        float value = stof(s.c_str());
        variables::getInstance()->setVarBySim(variables::getInstance()->nameArr[counter], value);
        //cout << "rpm: " << endl;
        //cout << s + ", " + to_string(value);
        s = "";
        //cout<<variables::getInstance()->getValueByName("rpm")<<endl;

    }

}




