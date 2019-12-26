
#ifndef EX1_EX1_H
#define EX1_EX1_H

#include <string>
#include "Expression.h"
#include "Interpreter.h"

using namespace std;

// Value class:
class Value: public Expression {
private:
    float val;
public:
    Value(double);
    float calculate() override;
};

// Variable class:
class Variable: public Expression {
private:
    string name;
    float value;
public:
    Variable(string, float);
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(float);
    Variable& operator-=(float);
    Variable& operator++(int);
    Variable& operator--(int);
    float calculate() override;
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
    float calculate() override;
};

// Minus class:
class Minus: public BinaryOperator {
public:
    Minus(Expression *left, Expression *right);
    float calculate() override;
};

// Mul class:
class Mul: public BinaryOperator {
public:
    Mul(Expression *left, Expression *right);
    float calculate() override;
};

// Div class:
class Div: public BinaryOperator {
public:
    Div(Expression *left, Expression *right);
    float calculate() override;
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
    float calculate() override;
};

// UMinus class:
class UMinus: public UnaryOperator {
public:
    UMinus(Expression*);
    float calculate();
};


#endif //EX1_EX1_H
