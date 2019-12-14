//
// Created by itay on 12/13/19.
//
#include <string>
#ifndef EVEN_DERECH_VARIABLE_H
#define EVEN_DERECH_VARIABLE_H
using namespace std;

class Variable {
    int value, inOrOut;
    string name,sim;
public:
    Variable(int val,int iOu, string n, string s) {
        this->name = name;
        this->value = val;
        this->sim = s;
        this->inOrOut = iOu;
    }
    int getValue(){
        return this->value;
    }
};

#endif //EVEN_DERECH_VARIABLE_H
