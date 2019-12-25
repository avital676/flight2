#include <iostream>
#include "lexer.cpp"
#include "parser.h"
#include "variables.h"
#include "keepThreads.h"


#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <cstring>


int main() {

    variables::getInstance();
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