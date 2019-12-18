//
// Created by matan on 14.12.2019.
//

#include "SingleMapOfVar.h"
SingleMapOfVar::SingleMapOfVar() = default;
int SingleMapOfVar::num = 0;
unordered_map<string, Command*> * SingleMapOfVar::map = 0;
void  SingleMapOfVar::initializeMap(unordered_map<string, Command*>* map) {
    (*map)["openDataServer"] = new openServerCommand();
    (*map)["connectControlClient"] =new ConnectCommand();
    (*map)["var"] = new DefineVarCommand();
    (*map)["while"] =new LoopCommand();
    (*map)["Print"] = new PrintCommand();
    (*map)["Sleep"] = new SleepCommand();

}
 unordered_map<string, Command*>* SingleMapOfVar::getInstance()
{
     if(num == 0){
         map = new unordered_map<string, Command*>();
            initializeMap(map);
         num++;
     }
    return map;
}