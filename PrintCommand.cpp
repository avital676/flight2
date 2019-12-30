
#include <iostream>
#include <string>
#include "command.h"
#include "variables.h"

// Execute print command:
int PrintCommand::execute(int i, vector<string> v) {
    unordered_map<string, varObj*> m =variables::getInstance()->getNameMap();
    if (v[i+1][0]=='"'){
        string toPrint = v[i+1].substr(1, v[i+1].length()-2);
        cout << toPrint << endl;
    }
    else{
        float value = express(v[i+1]);
        cout<<value<<endl;
    }
    numOfPar = 1;
    return numOfPar + 1;
}