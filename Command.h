//
// Created by itay on 12/12/19.
//
#include <vector>
#include <string>
#include <map>
#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

using namespace std;

class Command {
public:
    virtual int execute(int index, vector<string>& tokens, map<string, int> variables){}
};

#endif //EX3_COMMAND_H