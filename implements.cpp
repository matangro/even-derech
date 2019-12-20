//
// Created by itay on 12/12/19.
//

#include <thread>
#include <iostream>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include "implemets.h"
#include <vector>
#include <map>
#include <unordered_map>
#include "Expression.h"
#include "ex1.h"
#include <utility>
#include <list>
using namespace std;


//#include "cmake-build-debug/server.cpp"

#define PORT 8081





int server_run() {
    //create socket
    vector<pair<string, float>> map;
    map.push_back( make_pair("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    map.push_back( make_pair("/instrumentation/altimeter/indicated-altitude-ft", 0));
    map.push_back( make_pair("/instrumentation/altimeter/pressure-alt-ft", 0));
    map.push_back(make_pair("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    map.push_back(make_pair("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
    map.push_back(make_pair("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
    map.push_back(make_pair("/instrumentation/attitude-indicator/internal-roll-deg", 0));
    map.push_back(make_pair("/instrumentation/encoder/indicated-altitude-ft", 0));
    map.push_back(make_pair("/instrumentation/encoder/pressure-alt-ft", 0));
    map.push_back(make_pair("/instrumentation/gps/indicated-altitude-ft", 0));
    map.push_back(make_pair("/instrumentation/gps/indicated-ground-speed-kt", 0));
    map.push_back(make_pair("/instrumentation/gps/indicated-vertical-speed", 0));
    map.push_back(make_pair("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    map.push_back(make_pair("/instrumentation/magnetic-compass/indicated-heading-deg",0));
    map.push_back(make_pair("/instrumentation/slip-skid-ball/indicated-slip-skid",0));
    map.push_back(make_pair("/instrumentation/turn-indicator/indicated-turn-rate",0));
    map.push_back(make_pair("/instrumentation/vertical-speed-indicator/indicated-speed-fpm",0));
    map.push_back(make_pair("/controls/flight/aileron",0));
    map.push_back(make_pair("/controls/flight/elevator",0));
    map.push_back(make_pair("/controls/flight/rudder",0));
    map.push_back(make_pair("/controls/flight/flaps",0));
    map.push_back(make_pair("/controls/engines/engine/throttle",0));
    map.push_back(make_pair("/engines/engine/rpm",0));

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(PORT);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
   /* int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }

    close(socketfd); //closing the listening socket

    //reading from client*/
    char buffer[2048] = {1,'.',5,5,',',1,',',2,',',3,',',4,',',5,',',6,',',7,',',8,',',9,',',10,',',11,',',12,
                         ',',13,',',14,',',15,',',16,',',17,',',18,',',19,',',20,',',21,',',22};
    int i = 0;
//    int valread = read(client_socket, buffer, 2048);
    for (int j; j<23;j++){
        if(buffer[i] == ',') {
            i++;
        }
        int num = 0,div = 0,flag = 0;
        num = buffer[i] - '0' + 48;
        i++;
        while (buffer[i] != ',' && buffer[i] != NULL) {
            if (buffer[i] == '.') {
                flag = 1;
                i++;
                continue;
            }
            num*=10;
            num += (buffer[i]-'0' + 48);
            i++;
            if (flag == 1) {
                if(div == 0) {
                    div +=10;
                } else {
                    div *=10;
                }

            }
        }
        float result = (float)num;
        if(div != 0) {
            result = (float)num / div;
        }
        map[j].second = result;// = atoi((const char*)buffer[i]);
    }
    std::cout << buffer << std::endl;

    //writing back to client
    char *hello = "Hello, I can hear you! \n";
//    send(client_socket, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n" << std::endl;
    return 0;
}



int openServerCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) {
    const char *c = tokens[index].c_str();
    int port = std::atoi(c);
    server_run();
//    thread thread_object(server_run,port,);
    //thread_object.join();
    return 2;
}


int DefineVarCommand::execute(int index, vector<string> &tokens, unordered_map<string, Variable>& variables) {
    index++;
    if(tokens[index +1].compare("->")) {
        variables.insert({tokens[index], Variable(1, tokens[index], tokens[index +3])});
    } else {//"<-"
        variables.insert({tokens[index], Variable(0, tokens[index], tokens[index +3])});
    }
    return 5;
}
int UpdateVarCommand::execute(int index, vector<string> &tokens, unordered_map<string, Variable>& variables) {string str =tokens[index];
    const char* val = tokens[index +2].c_str();
    Interpreter* i1 = new Interpreter();
    i1->setMap(variables);
    Expression* e4 = nullptr;
    e4 = i1->interpret(val);
    double temp = e4->calculate();
    if(variables.find(str) != (variables.end())){
        variables.at(str).setValue(temp);
        if(variables.at(str).getInOrOut() == 1) {
            SingleMapOfVar::pushTostack(str);
        }
    }

    return 3;
}


int LoopCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) {
    int temp_index = index,progress, flag = 1 ;
    IfCommand* ifCommand = new IfCommand();
    progress = (ifCommand->execute(index,tokens,variables)-1)/10;
    while ((ifCommand->execute(index,tokens,variables)) % 10){
    }
    return progress;
}

int IfCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) {
    if(!(tokens[index].compare("while"))){
        index++;
    }
    Variable *var1, *var2;
    if (variables.find(tokens[index]) == variables.end()) {
        const char *c = tokens[index].c_str();
        var1 = new Variable(0,"",""); //std::atoi(c);
        var1->setValue(atoi(c));
    } else {
        var1 =  &variables.at(tokens[index]);
    }
    if (variables.find(tokens[index+2]) == variables.end()) {
        const char *c = tokens[index+2].c_str();
        var2 = new Variable(0,"",""); //std::atoi(c);
        var2->setValue(atoi(c));
    } else {
        var2 =  &variables.at(tokens[index]);
    }
    //finding the operator location(index)
    int operatpr_index = index;
    while (tokens[operatpr_index] != ">" && tokens[operatpr_index] != ">=" && tokens[operatpr_index] != "<=" &&
           tokens[operatpr_index] != "<" && tokens[operatpr_index] != "!=" && tokens[operatpr_index] != "==" ) {
        operatpr_index++;
    }
    int progress = 4, currentProgress;
    int temp_index = index + 4; /** כדי לדלג על הסוגריים הפותחים**/
    if (checkCon(operatpr_index, tokens, variables, var1, var2)) {
        while (tokens[temp_index].compare("}") != 0) {
            currentProgress = IfCommand::parser(temp_index, tokens, variables);
            temp_index += currentProgress;
            progress += currentProgress;
            cout<<progress<<endl;
        }
        progress += 2;
        return progress * 10 + 1;
        }
    return 0;
    }



bool IfCommand::checkCon(int operatpr_index, vector<string> &tokens, unordered_map<string, Variable>& variables
        , Variable* var1, Variable* var2) {
    if (tokens[operatpr_index] == ">") {
        if(var1->getValue() > var2->getValue()) {
            return true;
        }
    }
    else if (tokens[operatpr_index] == ">=") {
        if(var1->getValue() >= var2->getValue()) {
            return true;
        }

    }
    else if (tokens[operatpr_index] == "<") {
        if(var1->getValue() < var2->getValue()) {
            return true;
        }

    }
    else if (tokens[operatpr_index] == "<=") {
        if(var1->getValue() <= var2->getValue()) {
            return true;
        }

    }
    else if (tokens[operatpr_index] == "==") {
        if(var1->getValue() == var2->getValue()) {
            return true;
        }

    }
    else if (tokens[operatpr_index] == "!=") {
        if(var1->getValue() != var2->getValue()) {
            return true;
        }
    }
    return false;
}

int PrintCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables){
    return 0;
}
int SleepCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables){

}
int ConnectCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables){

}
