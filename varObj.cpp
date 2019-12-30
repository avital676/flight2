//
// Created by avital on 22/12/2019.
//

#include "varObj.h"

string varObj::getSim() {
    return sim;
}

float varObj::getVal() {
    return val;
}

void varObj::setSim(string s) {
    sim = s;
}

void varObj::setVal(float v) {
    val = v;
}

void varObj::setF(bool f) {
    set = f;
}

bool varObj::getF() {
    return set;
}
