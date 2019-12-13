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



int openServerCommand‬‬::execute(int index, vector<string>& tokens, map<string, int> variables) {
    const char *c = tokens[index].c_str();
    int port = std::atoi(c);
    std::thread thread_object(server_run);
    thread_object.join();
    return 2;
}

int LoopCommand::execute(int index, vector<string>& tokens, map<string, int> variables) {

    while (this->condition.execute(index, tokens)){
        for(auto itr : this->commands ) {
            itr.execute(index, tokens);
        }
    }
}

int IfCommand::execute(int index, vector<string>& tokens, map<string, int> variables) {
    int operatpr_index = index, condition = 0;
    while (tokens[operatpr_index] != ">" && tokens[operatpr_index] != ">=" && tokens[operatpr_index] != "<=" &&
           tokens[operatpr_index] != "<" && tokens[operatpr_index] != "!=" && tokens[operatpr_index] != "==" ) {
        operatpr_index++;
    }
    if (tokens[operatpr_index] == ">") {
        if(>) {
            condition = 1;
        }
    }
    else if (tokens[operatpr_index] == ">=") {
        if(>=) {
            condition = 1;
        }

    }
    else if (tokens[operatpr_index] == "<") {
        if(<) {
            condition = 1;
        }

    }
    else if (tokens[operatpr_index] == "<=") {
        if(<=) {
            condition = 1;
        }

    }
    else if (tokens[operatpr_index] == "==") {
        if(==) {
            condition = 1;
        }

    }
    else if (tokens[operatpr_index] == "!=") {
        if(!=) {
            condition = 1;
        }

    }
    if() {
        for(auto itr : this->commands ) {
            itr.execute(index, tokens);
        }
    }
}


