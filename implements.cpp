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
#include "SingleMapOfVar.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include "Expression.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ex1.h"

#include <arpa/inet.h>
//#include <pthread.h>

#include <utility>
#include <list>
using namespace std;


//#include "cmake-build-debug/server.cpp"

#define PORT 8081
std::condition_variable cv;



void client1(){
    queue<string>* sta = SingleMapOfVar::getStack();
    string ip = sta->front();
    sta->pop();
    string tempPort= sta->front();
    sta->pop();

    int port = stoi(tempPort);


    unordered_map<string, Variable>* variables = SingleMapOfVar::getMap();


    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        //return -1;
    }
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); //give me any IP allocated for my machine
    address.sin_port = htons(5402);
    if( connect(socketfd, (struct sockaddr*)&address, sizeof(address)) ==-1) {
        cout<<"can't connect to sim"<< endl;
    }
    cout<<"client is conected"<<endl;
    bool endOfProgg = SingleMapOfVar::getBool();
    // noting to the server that the client is connected
    cv.notify_one();
    while (!(endOfProgg)) {
        if(sta->empty()) {
            this_thread::sleep_for(5ms);
        } else{
            string nameOfVar = sta->front();
            sta->pop();
            Variable b = variables->at(nameOfVar);
            float p = b.getValue();
            string temp = to_string(p);
            string massage = "set " + b.getSim().substr(1,b.getSim().length()-1) +" "+ temp +"\r\n" ;
            cout<<"the clieant sent to the sim: " +massage<<endl;
            send(socketfd, massage.c_str(), strlen(massage.c_str()), 0);
        }
        endOfProgg = SingleMapOfVar::getBool();
    }
    cout<<"end of clieant"<< endl;
}

void server_run() {
    sleep(5);
    queue<string>* sta = SingleMapOfVar::getStack();
    string port = sta->front();
    int tempPort = stoi(port);
    sta->pop();
    unordered_map<string,Variable>* variables = SingleMapOfVar::getMapOfVar();
    unordered_map<string,float > serverMap;
    vector<string> map;
    map.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
    map.push_back("/sim/time/warp");
    map.push_back("/controls/switches/magnetos");
    map.push_back("/instrumentation/heading-indicator/offset-deg");
    map.push_back("/instrumentation/altimeter/indicated-altitude-ft");
    map.push_back("/instrumentation/altimeter/pressure-alt-ft");
    map.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    map.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
    map.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
    map.push_back("/instrumentation/attitude-indicator/internal-roll-deg");
    map.push_back("/instrumentation/encoder/indicated-altitude-ft");
    map.push_back("/instrumentation/encoder/pressure-alt-ft");
    map.push_back("/instrumentation/gps/indicated-altitude-ft");
    map.push_back("/instrumentation/gps/indicated-ground-speed-kt");
    map.push_back("/instrumentation/gps/indicated-vertical-speed");
    map.push_back("/instrumentation/heading-indicator/indicated-heading-deg");
    map.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    map.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    map.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
    map.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    map.push_back("/controls/flight/aileron");
    map.push_back("/controls/flight/elevator");
    map.push_back("/controls/flight/rudder");
    map.push_back("/controls/flight/flaps");
    map.push_back("/controls/engines/engine/throttle");
    map.push_back("/controls/engines/current-engine/throttle");
    map.push_back("/controls/switches/master-avionics");
    map.push_back("/controls/switches/starter");
    map.push_back("/engines/active-engine/auto-start");
    map.push_back("/controls/flight/speedbrake");
    map.push_back("/sim/model/c172p/brake-parking");
    map.push_back("/controls/engines/engine/primer");
    map.push_back("/controls/engines/current-engine/mixture");
    map.push_back("/controls/switches/master-bat");
    map.push_back("/controls/switches/master-alt");
    map.push_back("/engines/engine/rpm");
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        //return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(tempPort);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        //return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        //return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }


    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
    SingleMapOfVar::setBool(false);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        //return -4;
    }


    close(socketfd); //closing the listening socket
    cout<<"server work"<< endl;
    //char buffer[2048] = {"0.000000,0.000000,1.193444,12.000000,40.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,270.010010,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000"};
    char buffer[2048] ={0};
    int i = 0;
    while (!SingleMapOfVar::getBool()) {
        i=0;
      int valread = read(client_socket, buffer, 2048);
      //cout<<buffer<<endl;
      for (int j=0; j < 36; j++) {

          if (buffer[i] == ',') {
              i++;
          }
          int num = 0, div = 0, flag = 0;
          num = buffer[i] - '0';
          i++;
          while (buffer[i] != ',' && buffer[i] != '\n') {
              if (buffer[i] == '.') {
                  flag = 1;
                  i++;
                  continue;
              }
              num *= 10;
              num += (buffer[i] - '0');
              i++;
              if (flag == 1) {
                  if (div == 0) {
                      div += 10;
                  } else {
                      div *= 10;
                  }

              }
          }
          float result = (float) num;
          if (div != 0) {
              result = (float) num / div;
          }
          if(j==5) {
              cout<< result<<endl;
          }
          //cout<<result<<endl;
          serverMap[map[j]] = result;// = atoi((const char*)buffer[i]);
      }
      //variables = SingleMapOfVar::getMapOfVar();
      for (auto& pair :*variables){
          if(pair.second.getInOrOut()==0){
              string temp = pair.second.getSim();
              /*if(!pair.first.compare("rpm")) {
                  cout<<"rpm before is " << pair.second.getValue()<<endl;
              }*/
              //cout<<pair.first<<endl;
              float a = serverMap[temp];
              variables->at(pair.first).setValue(a);
              //pair.second.setValue(a);
              /*if(!pair.first.compare("rpm")) {
                  cout<<"rpm after is " << pair.second.getValue()<<endl;
              }*/
              //cout<<pair.second.getValue()<<endl;
          }
      }

    }

}



int openServerCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables) {
    const char *c = tokens[index+1].c_str();
    int port = std::atoi(c);
    queue<string>* sta = SingleMapOfVar::getStack();
    SingleMapOfVar::setBool(true);
    sta ->push(c);
    //server_run();
    std::thread thread_object(server_run);
    thread_object.detach();
    while (SingleMapOfVar::getBool()){}
    //thread_object.join();
    return 2;
}


int DefineVarCommand::execute(int index, vector<string> &tokens, unordered_map<string, Variable>& variables) {
    index++;
    if(!tokens[index +1].compare("->")) {
        variables.insert({tokens[index], Variable(1, tokens[index], tokens[index +3])});
    } else if(tokens[index+1][0]=='='){
        const char* val = tokens[index +2].c_str();
        Interpreter* i1 = new Interpreter();
        i1->setMap(variables);
        Expression* e4 = nullptr;
        e4 = i1->interpret(val);
        double temp = e4->calculate();
        variables.insert({tokens[index], Variable(2, tokens[index], "null")});
        variables.at(tokens[index]).setValue(temp);
        return 4;
    }
    else {//"<-"
        variables.insert({tokens[index], Variable(0, tokens[index], tokens[index +3])});
    }
    return 5;
}
int UpdateVarCommand::execute(int index, vector<string> &tokens, unordered_map<string, Variable>& variables) {
    string str =tokens[index];
    const char* val = tokens[index +2].c_str();
    Interpreter* i1 = new Interpreter();
    i1->setMap(variables);
    Expression* e4 = nullptr;
    e4 = i1->interpret(val);
    double temp = e4->calculate();
    cout<<"we updait the var " << str <<endl;
    if(variables.find(str) != (variables.end())){
        //cout<<variables.at(str).getValue()<<endl;
        variables.at(str).setValue(temp);
        //cout<<variables.at(str).getValue()<<endl;
        cout<<"we find the var in the map " << str << "the inOrOut is " << variables.at(str).getInOrOut()<<endl;

        if(variables.at(str).getInOrOut() == 1) {
            SingleMapOfVar::pushTostack(str);
            cout<<"we put the var " + str +"to the stack"<<endl;
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
           // cout<<progress<<endl;
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
    int flag = 0;
    if(!tokens[index].compare("Print")){
        flag++;
        index++;
    }
    string s = tokens[index];
    if(variables.find(s)!= variables.end()){
        double temp = variables.at(s).getValue();
        cout<<temp<<endl;
    } else{
        cout<<s<<endl;
    }
    return 1+flag;
}
int SleepCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables){
    int flag = 0;
    int secend = 0;
    if(!tokens[index].compare("Sleep")){
        flag++;
        index++;
    }
    string s = tokens[index];
    int time = stoi(s);
    //chrono::milliseconds* temp =new (time, ratio<1,1000>());
    //chrono::duration timeToSleep =chrono::duration<int, ratio>(time,new ratio<1,1000>());
    if(time>1000){
        secend = time/2500;
        time = time%1000;
    }
    this_thread::__sleep_for(chrono::seconds(secend),chrono::milliseconds(time));
    return 1+flag;
}

int ConnectCommand::execute(int index, vector<string>& tokens, unordered_map<string, Variable>& variables){

    int flag =0;
    if(!tokens[index].compare("connectControlClient")){
        index++;
        flag++;
    }
    string ip = tokens[index];
    string port = tokens[index+1];
    queue<string>* sta = SingleMapOfVar::getStack();
    sta->push(ip);
    sta->push(port);
    //int numOfPort = stoi(port);
    std::thread thread1(client1);
    //client(ip, numOfPort, variables);
    thread1.detach();
    return 2+flag;

}
