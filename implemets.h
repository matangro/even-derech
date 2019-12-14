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

class openServerCommand‬‬: public Command {
    int port;
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables);
};

class ConnectCommand: public Command {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables);
};

class DefineVarCommand: public Command {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables);
};

class PrintCommand: public Command {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables);
};

class SleepCommand: public Command {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables);
};

class ConditionParser: public Command{
protected:
    list<Command> commands;//the commands between the {} of the while loop
    Command condition;//is a command with boolean execute
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables);
};
class LoopCommand: public ConditionParser{
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables);
};
class  IfCommand: public ConditionParser {
public:
    int execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables);
};


#endif //EX3_IMPLEMETS_H
