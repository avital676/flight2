//
// Created by avital on 22/12/2019.
//

#ifndef FLIGHT2_VAROBJ_H
#define FLIGHT2_VAROBJ_H
#include <string>
using namespace std;

class varObj {
private:
    float value;
    string sim;
    bool set;
public:
    varObj();
    void setValue (float v);
    void setSim (string s);
    void setF (bool f);
    float getValue ();
    string getSim ();
    bool getF ();
};


#endif //FLIGHT2_VAROBJ_H
