//
// Created by matan on 14.12.2019.
//

#ifndef EVEN_DERECH_SINGLEMAPOFVAR_H
#define EVEN_DERECH_SINGLEMAPOFVAR_H
#include <unordered_map>
#include <stack>
#include "Command.h"
#include "Variable.h"
using namespace std;
class SingleMapOfVar {
private:
    static unordered_map<string, Command*>* map;
    static stack<string>* stack1;
    static int num;

    void static initializeMap(unordered_map<string, Command*>* map);


    /* Private constructor to prevent instancing. */
    SingleMapOfVar();

public:
    /* Static access method. */
    static unordered_map<string, Command*>* getInstance();
    static ::stack<string>* getStack();
    static int pushTostack(string str);

};




#endif //EVEN_DERECH_SINGLEMAPOFVAR_H