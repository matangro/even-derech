//
// Created by matan on 14.12.2019.
//

#include "SingleMapOfVar.h"
SingleMapOfVar::SingleMapOfVar() = default;
int SingleMapOfVar::num = 0;
unordered_map<string, Command> * SingleMapOfVar::map = 0;
 unordered_map<string, Command>* SingleMapOfVar::getInstance()
{
     if(num == 0){
         map = new unordered_map<string, Command>();
         num++;
     }
    return (SingleMapOfVar::map);
}