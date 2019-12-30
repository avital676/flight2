#include <iostream>
#include "variables.h"
#include "parser.h"
#include "lexer.cpp"
#include "keepThreads.h"
#include <string>
#include "Interpreter.h"
#include <algorithm>

int main(int argc, char *argv[]) {
    int noa =0;
    variables::getInstance();
    lexer l;
    vector<string> v = l.lex(argv[1]);
    parser* p = new parser(v);
    keepThreads::getInstance()->is_open = true;
    p->parse();
    keepThreads::getInstance()->is_open = false;
    keepThreads::getInstance()->serverTread.join();
    keepThreads::getInstance()->clientTread.join();
    return 0;
}