//
// Created by itay on 12/12/19.
//

#ifndef EVEN_DERECH_IMPLEMETS_H
#define EVEN_DERECH_IMPLEMETS_H

#include "Command.h"
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm>
#include "Variable.h"
#include "Expression.h"
#include "ex1.h"
#include "SingleMapOfVar.h"

class openServerCommand: public Command{
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class ConnectCommand: public Command{
public:

    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;

};

class DefineVarCommand: public Command{
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class UpdateVarCommand: public Command{
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class PrintCommand: public Command{
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class SleepCommand: public Command{
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
};

class ConditionParser: public Command{
public:
    virtual int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables)=0;
};
class LoopCommand: public ConditionParser{
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;

};
class  IfCommand: public ConditionParser{
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) override ;
    bool checkCon(int index, vector<string>& tokens, unordered_map<string, Variable>& variables, Variable* var1, Variable* var2);
    static int parser(int index, vector<string> arr, unordered_map<string, Variable>& mapOfVar ) {
        Command* c;
        unordered_map<string, Command*>* map= SingleMapOfVar::getInstance();
        if(map->find(arr[index]) != map->end()){
            c = (*map)[arr[index]];
            return c->execute(index,arr,mapOfVar);
        } else{
            c = new UpdateVarCommand();
            return c->execute(index,arr,mapOfVar);
        }
    }
};


#endif// EVE_IMPLEMETS_H
