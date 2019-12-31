//
// Created by matan on 14.12.2019.
//

#ifndef EVEN_DERECH_SINGLEMAPOFVAR_H
#define EVEN_DERECH_SINGLEMAPOFVAR_H
#include <unordered_map>
#include <stack>
#include <queue>
#include "Command.h"
#include "Variable.h"

using namespace std;
class SingleMapOfVar {
private:
    static unordered_map<string, Command*>* map;
    static queue<string>* stack1;
    static unordered_map<string,Variable>* mapOfVar;

    static bool endOfProg;
    static int num;

    void static initializeMap(unordered_map<string, Command*>* map);


    /* Private constructor to prevent instancing. */
    SingleMapOfVar();

public:
    /* Static access method. */
    static unordered_map<string, Command*>* getInstance();
    static ::queue<string>* getStack();
    static int pushTostack(string str);
    static unordered_map<string,Variable>* getMapOfVar();
    static bool getBool();
    static void setBool(bool s);
    static unordered_map<string,Variable>* getMap();
    static void setMap(unordered_map<string,Variable>& map1);

};




#endif //EVEN_DERECH_SINGLEMAPOFVAR_H