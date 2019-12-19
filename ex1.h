
#ifndef EX1_EX1_H
#define EX1_EX1_H

#include <string>
#include "Expression.h"
#include "Interpreter.h"

using namespace std;

// Value class:
class Value: public Expression {
private:
    double val;
public:
    Value(double);
    double calculate() override;
};

// Variable class:
class Variable: public Expression {
private:
    string name;
    double value;
public:
    Variable(string, double);
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double);
    Variable& operator-=(double);
    Variable& operator++(int);
    Variable& operator--(int);
    double calculate() override;
};

// BinaryOperator Interface:
class BinaryOperator: public Expression {
protected:
    Expression* right = nullptr;
    Expression* left = nullptr;
public:
    BinaryOperator(Expression* left, Expression* right);
    virtual ~BinaryOperator();
};

// Plus class:
class Plus: public BinaryOperator {
public:
    Plus(Expression *left, Expression *right);
    double calculate() override;
};

// Minus class:
class Minus: public BinaryOperator {
public:
    Minus(Expression *left, Expression *right);
    double calculate() override;
};

// Mul class:
class Mul: public BinaryOperator {
public:
    Mul(Expression *left, Expression *right);
    double calculate() override;
};

// Div class:
class Div: public BinaryOperator {
public:
    Div(Expression *left, Expression *right);
    double calculate() override;
};

// UnaryOperator interface:
class UnaryOperator: public Expression {
protected:
    Expression* exp = nullptr;
public:
    UnaryOperator(Expression* exp);
    virtual ~UnaryOperator();
};

// UPlus class:
class UPlus: public UnaryOperator {
public:
    UPlus(Expression*);
    double calculate() override;
};

// UMinus class:
class UMinus: public UnaryOperator {
public:
    UMinus(Expression*);
    double calculate();
};


#endif //EX1_EX1_H
