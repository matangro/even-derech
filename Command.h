//
// Created by itay on 12/12/19.
//
#include <vector>
#include <string>
#include <unordered_map>
#include "Variable.h"
#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

using namespace std;

class Command {
public:
    virtual int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables)=0;
};

#endif //EX3_COMMAND_H
