#include <iostream>
#include "variables.h"
#include "parser.h"
#include "lexer.cpp"
#include "keepThreads.h"
#include <string>
#include "Interpreter.h"
#include <algorithm>

int main(int argc, char *argv[]) {

    //aileron = -roll / 70

//    command* c = new command();
//    float aileron;
//    float roll = -0.0543;
//    variables::getInstance()->addVar("ailron", "", aileron, false);
//    variables::getInstance()->addVar("roll", "", roll, false);
//    aileron = c->express("-roll / 70");
//    cout<<aileron<<endl;
//    Interpreter* i = new Interpreter();
//    i->setVariables("roll=-0.0543;");
//    Expression *e=i->interpret("-roll/70");
//    cout << e->calculate() << endl;

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