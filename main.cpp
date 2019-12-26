#include <iostream>
#include "variables.h"
#include "parser.h"
#include "lexer.cpp"
#include "keepThreads.h"
#include <string>
#include "Interpreter.h"
#include <algorithm>

int main() {






    variables::getInstance();
//    string input = "(h - heading) / 80";
//    string output ="";
//    for (int i=0; i<input.length(); i++){
//        if (input[i]==' '){
//            i++;
//        }
//        else{
//            output+=input[i];
//        }
//    }
//    cout<<output<<endl;
//    string s="h=0.000000;heading=0.000000;";
//    Interpreter *i = new Interpreter();
//    i->setVariables(s);
//    string str = " (h - heading)/80";
//    str.erase(remove(str.begin(), str.end(), ' '), str.end());
//    cout<<str<<endl;
//    Expression *e=i->interpret(str);
//    cout<<e->calculate()<<endl;





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