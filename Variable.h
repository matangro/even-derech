//
// Created by itay on 12/13/19.
//
#include <string>
#include "Expression.h"
#ifndef EVEN_DERECH_VARIABLE_H
#define EVEN_DERECH_VARIABLE_H
using namespace std;

class Variable : public Expression {
    double val,
    int inOrOut;
    string name,sim;
public:
    Variable(int iOu, string n, string s) {
        this->name = n;
        this->val = 0;
        this->sim = s;
        this->inOrOut = iOu;
    }
    Variable(string name1, double value) {
        this->name = name1;
        this->val = value;
        this->sim = "local Variable";
        this->inOrOut = 2;
    }


    double calculate(){
        return this->val;
    }
    void setValue(double val) {
        this->val = val;
    }

    double getValue(){
        return this->val;
    }
    string getSim() {
        return this->sim;
    }
    int getInOrOut(){
        return this->inOrOut;
    }

};
/*
Variable::Variable(string name1, double value) {
    this->name = name1;
    this->val = value;
    this->sim = nullptr;
    this->inOrOut = 0;
}
Variable::Variable(int iOu, string n, string s) {
    this->name = n;
    this->val = 0;
    this->sim = s;
    this->inOrOut = iOu;
}
 */
#endif //EVEN_DERECH_VARIABLE_H
