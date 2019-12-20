//
// Created by matang on 6.11.2019.
//
#include <iostream>
#include  "ex1.h"
#include <queue>
#include <stack>
#include <regex>
#include "Variable.h"
// constractor
Value::Value( double newnum)  {
    this->num =  newnum;
}
UnaryOperator::UnaryOperator( Expression* exp) : Expression(){
    this->single = exp;
}
UPlus::UPlus(Expression* exp)  : UnaryOperator(exp) {}
UMinus::UMinus(Expression* exp)  : UnaryOperator(exp) {}
BinaryOperator::BinaryOperator(Expression* left1, Expression* right1) :Expression() {
    this->left = left1;
    this->right = right1;
}
Plus::Plus(Expression* left1, Expression* right1)  : BinaryOperator(left1, right1) {}
Minus::Minus(Expression* left1, Expression* right1)  : BinaryOperator(left1, right1) {}
Mul::Mul(Expression* left1, Expression* right1)  : BinaryOperator(left1, right1) {}
Div::Div(Expression* left1, Expression* right1)  : BinaryOperator(left1, right1) {}

// calculate

double Value::calculate(){
    return this->num;
}
double UPlus::calculate(){
    return UnaryOperator::single->calculate();
}
double UMinus::calculate(){
    return -UnaryOperator::single->calculate();
}
double Plus::calculate(){
    return (BinaryOperator::left->calculate() + BinaryOperator::right->calculate());
}
double Minus::calculate(){
    return (BinaryOperator::left->calculate() - BinaryOperator::right->calculate());
}
double Mul::calculate(){
    return (BinaryOperator::left->calculate() * BinaryOperator::right->calculate());
}
double Div::calculate(){
    double temp = BinaryOperator::right->calculate();
    if (temp == 0) {
        throw "division by zero";
    } else {
        return (BinaryOperator::left->calculate() / temp);
    }

}
/*
// operator of variable
Variable& Variable::operator++() {
    this->val = this->val + 1 ;
    return *this;
}
Variable& Variable::operator--() {
    this->val = this->val - 1 ;
    return *this;
}
Variable& Variable::operator++(int a) {
    this->val = this->val + 1 ;
    a++;
    return *this;
}
Variable& Variable::operator--(int a) {
    this->val = this->val + 1 ;
    a++;
    return *this;
}
Variable& Variable::operator+=(double const &other) {
    this->val = this->val + other;
    return *this;
}
Variable& Variable::operator-=(double const &other) {
    this->val = this->val - other;
    return *this;
}
*/
//desconstractors

Value::~Value(){
}
/*
Variable::~Variable() {
}
 */
UPlus::~UPlus(){
}
UMinus::~UMinus() {
}

UnaryOperator::~UnaryOperator() {
    delete this->single;
}
BinaryOperator::~BinaryOperator() {
    delete this->left;
    delete this->right;
}

Plus::~Plus() {
}
Minus::~Minus() {
}
Mul::~Mul() {
}
Div::~Div() {

}
//interpreted
Interpreter::Interpreter() {
}
Expression* Interpreter::interpret(string str) {
    this->str1 = str;
    int  i = 0;
    int length = 0;
    int temp;
    double k =1;
    double num1 ;
    Expression* temp1;
    Expression* temp2;
    stack <Expression*>* staE = new stack<Expression*>();
    stack<char>* staC = new stack<char>();
    map<char, int>* mapOfOperator = new map<char, int>();
    mapOfOperator->insert({'+',0});
    mapOfOperator->insert({'-',0});
    mapOfOperator->insert({'*',1});
    mapOfOperator->insert({'/',1});
    int size = str.size();
    // the while is running on all the leters in the string
    while (i<size) {
        num1 = 0;
        k=1;
        if(str[i] == 32){
            i++;
            continue;
        }
        //if is variable
        if((str[i]>=97) && (str[i]<=122)) {
            length = LengthOfVar(i);
            string a = str.substr(i, length);
            int flag = 1;
            for(auto c:this->vars){
                if(!(c.first.compare(a))) {
                    flag = 0;
                    staE->push(new Variable(a,c.second.getValue()));
                    i+=length;
                    continue;
                }
            }
            if(flag) {
                throw " the variable not exist in the map";
            } else{
                continue;
            }


        }
        // if is number
        if((isdigit(str[i]))||(str[i] == '.')) {
            length = NumOFDigit(i);
            // if we  have point in the number
            if ((temp = digitOfPoint(i,length))!=-1) {
                for (int j = temp; j>0 ; j--) {

                    num1+= (str[i+j-1] - '0')*k;
                    k=k*10;
                }
                k = 1;
                for (int j = temp+1; j<length ; j++) {
                    k=k/10;
                    num1+= (str[i+j] - '0')*k;
                }

            }
                //if we dont have point in the number
            else {
                for (int j = length; j>0 ; j--) {

                    num1+= (str[i+j-1] - '0')*k;
                    k=k*10;
                }
            }
            staE->push(new Value(num1));
            i = i + length;
            // if the char is ( or
        } else if (str[i] == '(') {
            staC->push(str[i]);
            i++;
        }
            // if the char is )
        else if (str[i] == ')') {

            while(staC->top()!='(') {

                temp1 = staE->top();
                staE->pop();
                char c = staC->top();
                staC->pop();
                // switch case on the operator char.
                switch (c) {
                    case '&':
                        staE->push(new UMinus(temp1));
                        break;
                    case '$':
                        staE->push(new UPlus(temp1));
                        break;
                    case '*':
                        temp2 = staE->top();
                        staE->pop();
                        staE->push(new Mul(temp2,temp1));
                        break;
                    case '/':
                        temp2 = staE->top();
                        staE->pop();
                        staE->push(new Div(temp2,temp1));
                        break;
                    case '+':
                        temp2 = staE->top();
                        staE->pop();
                        staE->push(new Plus(temp2,temp1));
                        break;
                    case '-':
                        temp2 = staE->top();
                        staE->pop();
                        staE->push(new Minus(temp2,temp1));
                        break;
                }
            }

            staC->pop();
            i++;
        }
            // if the char is operator
        else {

            if ((str[i] == '-')&&(str[i-1] == '(')) {
                staC->push('&');
            }
            else if ((str[i] == '+')&&(str[i-1] == '(')) {
                staC->push('$');
            }
            else if ((str[i] == '-')&&(i==0)) {
                staC->push('&');
            }
            else if ((str[i] == '+')&&(i ==0)) {
                staC->push('$');
            }
            else {
                // check if we have 2 binary operation in in a row
                if ((i != 0)){
                    if((str[i-1] == '+')||(str[i-1] == '-')) {
                        throw "illegal math expression";
                    } else if ((str[i-1] == '*')||(str[i-1] == '/')) {
                        throw "illegal math expression";
                    }
                }

                // if we have primary operator it do this in this while
                while ((!staC->empty())&&(staC->top() != '(')){
                    if ((staC->top() != '(')&&(mapOfOperator->at(str[i]) < mapOfOperator->at(staC->top()))) {
                        char c = staC->top();
                        staC->pop();
                        temp1 = staE->top();
                        staE->pop();
                        switch (c) {
                            case '&':
                                staE->push(new UMinus(temp1));
                                break;
                            case '$':
                                staE->push(new UPlus(temp1));
                                break;
                            case '*':
                                temp2 = staE->top();
                                staE->pop();
                                staE->push(new Mul(temp2,temp1));
                                break;
                            case '/':
                                temp2 = staE->top();
                                staE->pop();
                                staE->push(new Div(temp2,temp1));
                                break;
                            case '+': staE->push(new Plus(temp2,temp1));
                                break;
                            case '-': staE->push(new Minus(temp2,temp1));
                                break;
                        }
                    } else {
                        break;
                    }
                }
                staC->push(str[i]);

            }
            i++;
        }

    }

    while (staC->size()!=0) {
        char c = staC->top();
        staC->pop();
        temp1 = staE->top();
        staE->pop();
        switch (c) {
            case '&':
                staE->push(new UMinus(temp1));
                break;
            case '$':
                staE->push(new UPlus(temp1));
                break;
            case '*':
                temp2 = staE->top();
                staE->pop();
                staE->push(new Mul(temp2,temp1));
                break;
            case '/':
                temp2 = staE->top();
                staE->pop();
                staE->push(new Div(temp2,temp1));
                break;
            case '+':
                temp2 = staE->top();
                staE->pop();
                staE->push(new Plus(temp2,temp1));
                break;
            case '-': temp2 = staE->top();
                staE->pop();
                staE->push(new Minus(temp2,temp1));
                break;
        }
    }

    temp1 = staE->top();
    delete staC;
    delete staE;
    delete mapOfOperator;
    return temp1;
}
/**
 * the function return the length of the number
 * @param num
 * @return
 */
int Interpreter::NumOFDigit(int num) {
    int i = num;
    while ((isdigit(str1[i]))||(str1[i] == '.')) {
        i++;
    }

    return (i-num);
}
/**
 * return the index of the point in the number.
 * @param num
 * @param length
 * @return
 */
int  Interpreter::digitOfPoint(int num , int length) {
    for (int i = 0; i<length; i++) {
        if (this->str1[num+i] == '.') {
            return (i);
        }
    }
    return -1;
}
/**
 * put the variables in map.
 * @param var
 */
void Interpreter::setVariables(string var){
    /*
    bool flag = false;
    string varib="";
    string numb="";
    int length = var.length();
    for (int i = 0; i< length; i++) {
        if (var[i] == '=') {
            flag = true;
            continue;
        }
        else if(var[i]==';') {
            regex reg("[a-zA-Z]+[0-9|a-z|A-Z]*");
            if (!(regex_match(varib,reg))) {
                throw "bad variable";
            }
            regex reg2("[0-9]+[.]?[0-9]*");
            if (!(regex_match(numb,reg2))) {
                throw "bad number!";
            }
            double temp = stod(numb);
            for(auto c:this->vars){
                if(!(c.first.compare(varib))) {
                    this->vars.erase(varib);
                }
            }
            this->vars.insert({varib,temp});
            varib.clear();
            numb.clear();
            flag = false;
            continue;
        } else {
            if(!flag) {
                string a = string(1,var[i]);
                varib.append(a);
            } else {
                if((var[i]<48)||(var[i]>57)) {
                    if (var[i] !='.') {
                        throw "illegal variable assignment!";
                    }
                }
                string a = string(1,var[i]);
                numb.append(a);
            }
        }
    }
    if (numb.length() >0) {
        regex reg("[a-zA-Z]+[0-9|a-z|A-Z]*");
        if (!(regex_match(varib,reg))) {
            throw "bad variable";
        }
        regex reg2("[0-9]+[.]?[0-9]*");
        if (!(regex_match(numb,reg2))) {
            throw "bad value to variable";
        }
        double temp = stod(numb);
        for(auto c:this->vars){
            if(!(c.first.compare(varib))) {
                this->vars.erase(varib);
            }
        }
        this->vars.insert({varib,temp});
    }
*/
}
/**
 * return the length of the variable.
 * @param num
 * @return
 */
int Interpreter::LengthOfVar(int num) {
    int i = num;
    int flag =0;
    while (i<this->str1.size()) {
        if ((this->str1[i] =='+')||(this->str1[i] =='-')){
            break;
        }
        if((this->str1[i] =='/')||(this->str1[i] =='*')) {
            break;
        }
        if ((this->str1[i] =='(')||(this->str1[i] ==')')){
            break;
        }
        if(this->str1[i]== ' '){
            flag =1;
            i--;
            break;
        }
        i++;
    }
    return (i-num+flag);
}
void Interpreter::setMap(unordered_map<string, Variable>& map) {
    this->vars = map;
}
