
#include <iostream>
#include <string>
#include "command.h"
#include "variables.h"

// Execute print command:
int PrintCommand::execute(int i, vector<string> v) {
    unordered_map<string, varObj*> m =variables::getInstance()->getNameMap();
    if (m.find(v[i + 1]) != m.end()) {
        float value = m[v[i+1]]->getVal();
        cout<<value<<endl;
    } else {
        //cut the " "
        string toPrint = v[i+1].substr(1, v[i+1].length()-2);
        cout << toPrint << endl;
    }
    numOfPar = 1;
    return numOfPar + 1;
}