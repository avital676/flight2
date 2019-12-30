
#include <iostream>
#include <string>
#include "command.h"
#include "variables.h"
#include <thread>

// Execute sleep command:
int SleepCommand::execute(int i, vector<string> v) {
    float timeToSleep = express(v[i+1]);
    chrono::milliseconds duration((int)timeToSleep);
    this_thread::sleep_for(duration);
    numOfPar = 1;
    return numOfPar + 1;
}
