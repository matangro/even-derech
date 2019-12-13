//
// Created by itay on 12/12/19.
//

#ifndef EX3_IMPLEMETS_H
#define EX3_IMPLEMETS_H

#include "Command.h"
#include <string>
#include <list>

class openServerCommand‬‬: public Command {
    int port;
public:
    int execute(int index, string tokens[]);
};

class ConnectCommand: public Command {
public:
    int execute();
};

class DefineVarCommand: public Command {
public:
    int execute();
};

class ComandParser: public Command{
protected:
    list<Command> commands;//the commands between the {} of the while loop
    Command condition;//is a command with boolean execute
public:
    int execute();
};
class LoopCommand: public ComandParser{
public:
    int execute();
};
class  IfCommand: public ComandParser {
public:
    int execute();
};

#endif //EX3_IMPLEMETS_H
