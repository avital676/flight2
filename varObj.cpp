//
// Created by avital on 22/12/2019.
//

#include "varObj.h"
using namespace std;

void varObj::setValue (float v) {
    value = v;
}
void varObj::setSim (string s) {
    sim = s;
}
void varObj::setF (bool f) {
    set = f;
}
float varObj::getValue () {
    return value;
}
string varObj::getSim () {
    return sim;
}
bool varObj::getF () {
    return set;
}

varObj::varObj() {}
