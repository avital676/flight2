#include <iostream>
#include "variables.h"
#include "parser.h"
#include "lexer.cpp"
#include "keepThreads.h"
#include <string>
#include "Interpreter.h"

int main() {
    variables::getInstance();
//    string s="alt=-372.033875";
//
//    Interpreter *i = new Interpreter();
//    i->setVariables(s);
//    Expression *e=i->interpret("alt");
    std::cout << "Hello, World!" << std::endl;
    cout<<"noaooaoaooaoaoooaoa"<<endl;
    lexer l;
    vector<string> v = l.lex();
    parser* p = new parser(v);
    keepThreads::getInstance()->is_open = true;
    p->parse();
    l.lex();
    keepThreads::getInstance()->is_open = false;
    keepThreads::getInstance()->serverTread.join();
    keepThreads::getInstance()->clientTread.join();
    return 0;
}