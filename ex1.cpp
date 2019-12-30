
#include <iostream>
#include "ex1.h"

// Value:
float Value::calculate() {
    return this->val;
}

Value::Value(double value) {
    this->val = value;
}

// Variable:
Variable& Variable::operator++() {
    this->value+=1;
    return *this;
}

Variable& Variable::operator--() {
    this->value-=1;
    return *this;
}

Variable& Variable::operator+=(float num) {
    this->value+=num;
    return *this;
}

Variable& Variable::operator-=(float num) {
    this->value-=num;
    return *this;
}

Variable& Variable::operator++(int) {
    this->value+=1;
    return *this;
}

Variable& Variable::operator--(int) {
    this->value-=1;
    return *this;
}

float Variable::calculate() {
    return this->value;
}

Variable::Variable(string str, float val) {
    this->name = str;
    this->value = val;
}

// Binary Operator:
BinaryOperator::BinaryOperator(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

BinaryOperator::~BinaryOperator() {
    if (this->left != NULL)
        delete this->left;
    if (this->right != NULL)
        delete this->right;
}

// Plus:
Plus::Plus(Expression *leftExp, Expression *rightExp) : BinaryOperator(left, right) {
    left = leftExp;
    right = rightExp;
}

float Plus::calculate() {
    return (this->left->calculate() + this->right->calculate());
}

// Minus:
Minus::Minus(Expression *leftExp, Expression *rightExp) : BinaryOperator(left, right) {
    left = leftExp;
    right = rightExp;
}

float Minus::calculate() {
    return (this->left->calculate() - this->right->calculate());
}

// Mul:
Mul::Mul(Expression *leftExp, Expression *rightExp) : BinaryOperator(left, right) {
    left = leftExp;
    right = rightExp;
}

float Mul::calculate() {
    return (this->left->calculate() * this->right->calculate());
}

// Div:
Div::Div(Expression *leftExp, Expression *rightExp) : BinaryOperator(left, right) {
    left = leftExp;
    right = rightExp;
}

float Div::calculate() {
    if (this->right->calculate() == 0)
        throw "Exception: can't divide by 0";
    return (this->left->calculate() / this->right->calculate());
}

// Unary Operator:
UnaryOperator::UnaryOperator(Expression *e) {
    this->exp = e;
}

UnaryOperator::~UnaryOperator() {
    if (this->exp!= NULL)
        delete this->exp;
}

// UPlus:
UPlus::UPlus(Expression *e) : UnaryOperator(exp) {
    this->exp = e;
}

float UPlus::calculate() {
    return this->exp->calculate();
}

// UMinus:
UMinus::UMinus(Expression *e) : UnaryOperator(exp) {
    this->exp = e;
}

float UMinus::calculate() {
    return (-1) * this->exp->calculate();
}
