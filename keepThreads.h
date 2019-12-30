
#ifndef FLIGHT2_KEEPTHREADS_H
#define FLIGHT2_KEEPTHREADS_H

#include <thread>

using namespace std;

// keepThreads class- manages the threads in the program:
class keepThreads {
private:
    keepThreads(){};
    static keepThreads* instance;
public:
    static keepThreads* getInstance();
    thread serverTread;
    thread clientTread;
    bool is_open = false;
};

#endif //FLIGHT2_KEEPTHREADS_H
