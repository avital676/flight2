#include <iostream>
#include "lexer.cpp"
#include "parser.h"
#include "keepThreads.h"
#include "variables.h"

int main() {
    variables::getInstance();
    std::cout << "Hello, World!" << std::endl;
    lexer l;
    vector<string> v = l.lex();
    parser* p = new parser(v);
    p->parse();
    l.lex();
    keepThreads::getInstance()->is_open = false;
    keepThreads::getInstance()->serverTread.join();
    keepThreads::getInstance()->clientTread.join();
    return 0;
}
