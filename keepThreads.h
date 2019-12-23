//
// Created by noa on 19/12/2019.
//

#ifndef FLIGHT2_KEEPTHREADS_H
#define FLIGHT2_KEEPTHREADS_H

#include <thread>
using namespace std;
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
