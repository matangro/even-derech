//
// Created by itay on 12/12/19.
//

#ifndef EX3_IMPLEMETS_H
#define EX3_IMPLEMETS_H

#include "Command.h"
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include "Variable.h"

class openServerCommand: public Command {
public:

    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override;
};

class ConnectCommand: public Command {
public:
   //static void client(int args, char argv[]);
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class DefineVarCommand: public Command {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class UpdateVarCommand: public Command {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class PrintCommand: public Command {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class SleepCommand: public Command {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class ConditionParser: public Command{

public:
    virtual int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables)=0 ;
};
class LoopCommand: public ConditionParser{
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;

};
class  IfCommand: public ConditionParser {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
    bool checkCon(int index, vector<string>& tokens, unordered_map<string, Variable>& variables, int var1, int var2);
};


#endif //EX3_IMPLEMETS_H
