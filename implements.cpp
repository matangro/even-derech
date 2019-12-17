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
#include <unordered_map>
#include <list>

using namespace std;


//#include "cmake-build-debug/server.cpp"

#define PORT 8081





int server_run(int argc, char const *argv[]) {
    //create socket
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
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }

    close(socketfd); //closing the listening socket

    //reading from client
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << buffer << std::endl;

    //writing back to client
    char *hello = "Hello, I can hear you! \n";
    send(client_socket, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n" << std::endl;
    return 0;
}



int openServerCommand‬‬::execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables) {
    const char *c = tokens[index].c_str();
    int port = std::atoi(c);
    std::thread thread_object(server_run);
    thread_object.join();
    return 2;
}


int DefineVarCommand::execute(int index, vector<string> &tokens, unordered_map<string, Variable> variables) {
    index++;
    if(tokens[index +1].compare("->")) {
        variables.insert({tokens[index], Variable(1, tokens[index], tokens[index +3])});
    } else {//"<-"
        variables.insert({tokens[index], Variable(0, tokens[index], tokens[index +3])});
    }
    return 5;
}
int UpdateVarCommand::execute(int index, vector<string> &tokens, unordered_map<string, Variable> variables) {
    string str =tokens[index];
    const char* val = tokens[index +2].c_str();
    if(variables.find(str) != (variables.end())){
        variables[str].setValue(atoi(val));
    }
    return 3;
}


int LoopCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables) {

    int index1 = index, progress;
    IfCommand* ifCommand = new IfCommand();

    while (progress = ifCommand->execute(index,tokens,variables)){
        index += progress / 10 - 1;/**כאן נכניס את פלט הפונקציה שיוצרת את רשימת ה-commands ל-while שהוא בעצם התקדמות הindex לאחר קריאת כל הפקודות**/;
        }

    return index1;
}

int IfCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable> variables) {
    list<Command> comands;/**נכניס את הרשימה לפונקציה שתמלא אותה ב-commands**/
    int flag = 0;
    if(tokens[index].compare("while")){
        flag = 1;
    }
    index++;
    int var1 = variables.at(tokens[index]).getValue(), var2 = variables.at(tokens[index + 2]).getValue();
    //finding the operator location(index)
    int operatpr_index = index, condition = 0;
    while (tokens[operatpr_index] != ">" && tokens[operatpr_index] != ">=" && tokens[operatpr_index] != "<=" &&
           tokens[operatpr_index] != "<" && tokens[operatpr_index] != "!=" && tokens[operatpr_index] != "==" ) {
        operatpr_index++;
    }

    if(checkCon(operatpr_index, tokens, variables, var1, var2)) {
        int progress = 0;
        for(auto itr : comands /**לרוץ על רשימת הפקודות שבבלוק**/) {
            progress += itr.execute(index, tokens, variables);
        }
        return progress * 10 + 1;
    }
    return 0;
}

bool IfCommand::checkCon(int operatpr_index, vector<string> &tokens, unordered_map<string, Variable> variables
        , int var1, int var2) {
    if (tokens[operatpr_index] == ">") {
        if(var1 > var2) {
            return true;
        }
    }
    else if (tokens[operatpr_index] == ">=") {
        if(var1 >= var2) {
            return true;
        }

    }
    else if (tokens[operatpr_index] == "<") {
        if(var1 < var2) {
            return true;
        }

    }
    else if (tokens[operatpr_index] == "<=") {
        if(var1 <= var2) {
            return true;
        }

    }
    else if (tokens[operatpr_index] == "==") {
        if(var1 == var2) {
            return true;
        }

    }
    else if (tokens[operatpr_index] == "!=") {
        if(var1 != var2) {
            return true;
        }
    }
    return false;
}


