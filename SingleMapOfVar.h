//
// Created by matan on 14.12.2019.
//

#ifndef EVEN_DERECH_SINGLEMAPOFVAR_H
#define EVEN_DERECH_SINGLEMAPOFVAR_H
#include <unordered_map>
#include "Command.h"
#include "Variable.h"

class SingleMapOfVar {
private:
    static unordered_map<string, Command>* map;
    static int num;



    /* Private constructor to prevent instancing. */
    SingleMapOfVar();

public:
    /* Static access method. */
    static unordered_map<string, Command>* getInstance();

};



#endif //EVEN_DERECH_SINGLEMAPOFVAR_H
