
#include "ex1.h"
#include "Interpreter.h"
#include <regex>
#include <iostream>

using namespace std;

Expression* Interpreter::interpret(string str) {
    makeQueue(str);
    return makeExp();
}

void Interpreter::makeQueue(string str) {
    stack<string> strStk;
    string num;
    string var;
    string s;
    char c;
    char ch;
    int flag = 0; // flag for "("
    for (unsigned int i = 0; i < str.length(); i++) {
        s = c = str.at(i);
        if (c == '(') {
            strStk.push(s);
            flag += 1;
        } else if (c == ')') {
            if (flag < 1)
                throw "Exception: can't interpret";
            while (strStk.top() != "(") {
                postfix.push(strStk.top());
                strStk.pop();
            }
            strStk.pop();
            flag -= 1;
        } else if ((isdigit(c)) || c == 46) { // number:
            num.append(s);
            if (i == str.length() - 1) {
                postfix.push(num);
                num.clear();
            } else if (((str.at(i + 1) != '.') && (!isdigit(str.at(i + 1))))) {
                postfix.push(num);
                num.clear();
            }
        } else if (isalpha(c)) { // variable:
            if (i != str.length() - 1) {
                // check where the variable name ends:
                for (unsigned int j = i + 1; j < str.length(); j++) {
                    var = ch = str.at(j);
                    if (isdigit(ch) || isalpha(ch) || ch == '_') {
                        s.append(var);
                        i++;
                    } else {
                        break;
                    }
                }
            }
            if (varExist(s)) {
                postfix.push(s);
            } else {
                throw "Exception: can't interpret";
            }
        } else if (c == '+' || c == '-' || c =='*' || c == '/') { // unary operator
            if (i == str.length() - 1) {
                throw "Exception: invalid expression";
            } else if (!isdigit(str.at(i + 1)) && !isalpha(str.at(i + 1)) && str.at(i + 1) != '(')
                throw "Exception: invalid expression";
            if ((c == '+') && (i == 0)) { // change unary plus to @
                strStk.push("@");
            } else if ((c == '+') && (str.at(i - 1) == '(')) {
                strStk.push("@");
            } else if ((c == '-') && (i == 0)) { // change unary minus to $
                strStk.push("$");
            } else if ((c == '-') && (str.at(i - 1) == '(')) {
                strStk.push("$");
            } else { // binary operator
                if (i == str.length() - 1) {
                    throw "Exception: invalid expression";
                } else if (!isdigit(str.at(i + 1)) && !isalpha(str.at(i + 1)) && str.at(i + 1) != '(')
                    throw "Exception: invalid expression";
                while (!strStk.empty()) {
                    if (getPre(s) <= getPre(strStk.top())) {
                        postfix.push(strStk.top());
                        strStk.pop();
                    } else {
                        break;
                    }
                }
                strStk.push(s);
            }
        } else {
            throw "Exception: invalid character";
        }
    }
    while (!strStk.empty()) {
        postfix.push(strStk.top());
        strStk.pop();
    }
}

int Interpreter::getPre(string s) {
    map<string, int>::iterator iter;
    iter = preMap.find(s);
    if(iter != preMap.end())
        return iter->second;
    else
        throw "Exception: operator problem";
}

Expression* Interpreter::convertToVar(string name) {
    double val;
    map<string, double>::iterator iter;
    iter = vMap.find(name);
    if(iter != vMap.end())
        val = iter->second;
    else
        throw "Exception: variables value not found";
    return new Variable(name, val);
}

Interpreter::Interpreter() {
    // create precedence map:
    preMap["("] = 0;
    preMap["+"] = preMap["-"] = 1;
    preMap["*"] = preMap["/"] = 2;
    preMap[")"] = 3;
    preMap["@"] = preMap["$"] = 4; // unary operators
}

bool Interpreter::varExist(string name) {
    return vMap.count(name) > 0;
}

Expression *Interpreter::makeExp() {
    stack<Expression*> stk;
    char oper;
    Expression* right;
    Expression* left;
    Expression* exp;
    while (!postfix.empty()) {
        if (isdigit(postfix.front()[0])) { // number
            stk.push(new Value(stod(postfix.front())));
            postfix.pop();
        } else if (isalpha(postfix.front()[0])) { // variable
            stk.push(convertToVar(postfix.front()));
            postfix.pop();
        } else { // operator
            oper = postfix.front()[0];
            if (oper == '+' || oper == '-' || oper == '*' || oper == '/') { // binary operator
                right = stk.top();
                stk.pop();
                left = stk.top();
                stk.pop();
                switch (oper) {
                    case '+':
                        stk.push(new Plus(left, right));
                        break;
                    case '-':
                        stk.push(new Minus(left, right));
                        break;
                    case '*':
                        stk.push(new Mul(left, right));
                        break;
                    case '/':
                        stk.push(new Div(left, right));
                        break;
                }
            } else if (oper == '@' || oper == '$') { // unary operator
                exp = stk.top();
                stk.pop();
                switch (oper) {
                    case '@':
                        stk.push(new UPlus(exp));
                        break;
                    case '$':
                        stk.push(new UMinus(exp));
                }
            } else {
                throw "Exception: invalid operator";
            }
            postfix.pop();
        }
    }
    return stk.top();
}

void Interpreter::setVariables(string str) {
    cout<< "inside "<<endl;
    // split string:
    string segment;
    vector<string> v;
    string name;
    string val;
    unsigned int start = 0;
    for (unsigned int i = 0; i < str.length(); i++) {
        if (str.at(i) == ';') {
            v.push_back(str.substr(start, i - start));
            start = i + 1;
        }
    }
    // if the string didn't end with ';':
    if (start < str.length() - 1)
        v.push_back(str.substr(start, str.length() - start));
    for (string & s : v) {
        // check if name starts with a letter:
        if (!isalpha(s[0])) {
            throw "Exception: invalid variable";
        }
        // insert to string map:
        int pos = s.find("=");
        name = s.substr(0, pos);
        val = s.substr(pos + 1);
        // check name:
        regex regName("^[a-zA-Z0-9_]+$");
        if(!regex_match(name,regName))
            throw "Exception: invalid variable";
        // check val:
        //error
//        if ((!isdigit(val[0])) || (!isdigit(val.back())))
//            throw "Exception: invalid variable";
        regex regVal("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$");
        if(!regex_match(val,regVal))
            throw "Exception: invalid variable";
        // valid name and value:
        vMap[name] = stod(val);
    }
}
