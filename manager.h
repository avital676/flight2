//
// Created by avital on 17/12/2019.
//

#ifndef FLIGHT1_MANAGER_H
#define FLIGHT1_MANAGER_H

#include <thread>
#include "Interpreter.h"
#include "ex1.h"
#include "server.h"
#include "client.h"
#include "variables.h"
#include "command.h"
#include "lexer.cpp"
#include "parser.h"


class manager {
private:

    manager(){};
    static manager* instance;
public:
    static manager *getInstance();

};





#endif //FLIGHT1_MANAGER_H
