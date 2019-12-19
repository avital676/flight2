#include <iostream>
#include "lexer.cpp"
#include "parser.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    lexer l;
    vector<string> v = l.lex();
    parser* p = new parser(v);
    p->parse();
    l.lex();

    return 0;
}
