//
// Created by matan on 14.12.2019.
//

#include "SingleMapOfVar.h"
#include "implemets.h"
SingleMapOfVar::SingleMapOfVar() = default;
int SingleMapOfVar::num = 0;

bool SingleMapOfVar::endOfProg = false;
queue<string>* SingleMapOfVar::stack1 = nullptr;
unordered_map<string,Variable>* SingleMapOfVar::mapOfVar = nullptr;
unordered_map<string, Command*>* SingleMapOfVar::map = nullptr;
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
unordered_map<string,Variable>* SingleMapOfVar::getMapOfVar() {
   return mapOfVar;
}
 ::queue<string>* SingleMapOfVar::getStack() {
    if(stack1 == nullptr) {
       stack1 = new ::queue<string>();

    }
    return stack1;
}
int SingleMapOfVar::pushTostack(string str) {
    if (stack1 == nullptr) {
        stack1 = new ::queue<string>();
        stack1->push(str);
        return 1;
    } else {
        stack1->push(str);
        return 1;
    }

}
bool SingleMapOfVar::getBool() {

    return endOfProg;
}
void SingleMapOfVar::setBool(bool s) {
 endOfProg = s;
}
unordered_map<string,Variable>* SingleMapOfVar::getMap(){
    return (SingleMapOfVar::mapOfVar);
}
void SingleMapOfVar::setMap(unordered_map<string,Variable>& map1) {
    mapOfVar = &map1;
}


