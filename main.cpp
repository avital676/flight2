#include <iostream>
#include "lexer.cpp"
#include "parser.h"
#include "keepThreads.h"

int main() {
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
