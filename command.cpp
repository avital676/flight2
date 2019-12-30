
#include <iostream>
#include <string>
#include "command.h"
#include "variables.h"
#include "Interpreter.h"
#include <algorithm>

// Constructor:
command::command() {}

// Find variables in a given string, set them in an interpreter and use the interpreter to calculate it:
float command::express(string s){
    Interpreter *i = new Interpreter();
    string allVars="";
    string var="";
    string flag;
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    for (int i =0; i < s.length(); i++){
        // find variables:
        if ((s[i]<='z')&&(s[i]>='a')||(s[i]<='Z')&&(s[i]>='A')) {
            while((i<s.length())&&(s[i]!='+')&&(s[i]!='-')&&(s[i]!='*')&&(s[i]!='/')&&(s[i]!=')')&&(s[i]!='(')) {
                var += s[i];
                i++;
            }
        }
        if((s[i]=='+')||(s[i]=='*')||(s[i]=='-')||(s[i]=='/')){
            if (var!="") {
                float value = variables::getInstance()->getValueByName(var);
                allVars += var + "=" + to_string(value) + ";";
                var = "";
            }
        }
    }
    if (var!=""){
        float value = variables::getInstance()->getValueByName(var);
        if (value<0){
            allVars+=var+"="+""+to_string(value)+";";
        }
        else{
            allVars+=var+"="+ to_string(value)+";";
        }
    }
    if (allVars!=""){
        i->setVariables(allVars);
    }
    Expression *e=i->interpret(s);
    float result = e->calculate();
    return result;
}
