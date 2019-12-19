//
// Created by noa on 19/12/2019.
//

#include "keepThreads.h"
using namespace std;
keepThreads* keepThreads::instance=0;
keepThreads* keepThreads::getInstance() {
    if (!instance)
        instance = new keepThreads();
    return instance;
}
