
#ifndef FLIGHT2_VAROBJ_H
#define FLIGHT2_VAROBJ_H

#include <string>
using namespace std;

class varObj {
private:
    string sim;
    float val;
    bool set;
public:
    varObj(){};
    string getSim();
    float getVal();
    bool getF();
    void setSim(string s);
    void setVal(float v);
    void setF(bool f);
    ~varObj(){};
};

#endif //FLIGHT2_VAROBJ_H
