//
// Created by matang on 6.11.2019.
//

#ifndef EX1_H
#define EX1_H



#include <string>
#include <string.h>
#include "Expression.h"
#include <unordered_map>
#include "Variable.h"
using namespace std;
int main();
//class of varibels.
/*class Variable: public Expression {
    string name;
    double val;
        public:
    Variable(string name, double value);
    double calculate();
    Variable& operator++();
    Variable& operator--();
    Variable& operator++(int a);
    Variable& operator--(int a);
    Variable& operator+=(double const &other);
    Variable& operator-=(double const &other);
    ~Variable();
};

*/
class UnaryOperator: public Expression {
protected:
    Expression* single;
public:
    explicit UnaryOperator(Expression* exp);
    virtual double calculate() = 0 ;
    ~UnaryOperator();

};
class UPlus : public UnaryOperator{
public:
    explicit UPlus(Expression* exp);
    double calculate() override ;
    ~UPlus();
};
class UMinus : public UnaryOperator{
public:
explicit UMinus(Expression* exp);
    double calculate() override ;
    ~UMinus();
};
class Value : public Expression{
    double num;
    public:
    double calculate() override ;
    ~Value();
    Value(double d);
};
class BinaryOperator : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression* left, Expression* right);
    virtual double calculate() = 0;
    ~BinaryOperator();
};
class Plus : public BinaryOperator {
public:
    Plus(Expression* left, Expression* right);
    ~Plus();
    double calculate() override;
};
class Minus : public BinaryOperator {
public:
    Minus(Expression* left, Expression* right);
    double calculate() override;
    ~Minus();
};
class Mul : public BinaryOperator {
public:
    Mul(Expression* left, Expression* right);
    double calculate() override;
    ~Mul();
};
class Div : public BinaryOperator {
public:
    Div(Expression* left, Expression* right);
    double calculate() override;
    ~Div();
};
class Interpreter{
    unordered_map<string,Variable> vars;
    string str1;
public:
    Interpreter();
    Expression* interpret(string str);
    void setVariables(string var);
    void setMap(unordered_map<string,Variable>& map);
    int NumOFDigit(int num);
    int digitOfPoint(int num , int length);
    int LengthOfVar(int num);

};
#endif //EX1_H
