//
// Created by avital on 22/12/2019.
//

#include <string>
using namespace std;

class varObj {
public:
    float value;
    string sim;
    bool set;
    varObj(){};
    void setValue (float v) {
        value = v;
    }
    void setSim (string s) {
        sim = s;
    }
    void setF (bool f) {
        set = f;
    }

};