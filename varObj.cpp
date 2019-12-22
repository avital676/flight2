//
// Created by avital on 22/12/2019.
//

#include <string>
using namespace std;

class varObj {
private:
    float value;
    string sim;
    bool set;
public:
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
    float getValue () {
        return value;
    }
    string getSim () {
        return sim;
    }
    bool getF () {
        return set;
    }
};