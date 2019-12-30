
#include "keepThreads.h"

using namespace std;

keepThreads* keepThreads::instance = 0;

// Get instance of this class:
keepThreads* keepThreads::getInstance() {
    if (!instance)
        instance = new keepThreads();
    return instance;
}
