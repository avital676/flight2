
#ifndef FLIGHT1_PARSER_H
#define FLIGHT1_PARSER_H

#include <vector>
#include <string>
#include <map>
#include <thread>
#include "command.h"

using namespace std;

class parser {
    map<string, command*> comMap;
    vector<string> token;
public:
    parser(vector<string> v);
    void parse();
};

#endif //FLIGHT1_PARSER_H
