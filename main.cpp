#include <iostream>
#import  <istream>
#import <fstream>
#include <vector>
#import <cstring>

using namespace std;


int parenth(string line,int index, vector<string> &arr) {
    int j,flag =0,i;
        for (j=index+1;j<line.length();j++) {
            if(line[j]==')'){
                break;
            }
        }
        string a = line.substr(index+1,(j-index-1));
        i=0;
        while ((j=a.find(',',i))!=string::npos){
            flag = 1;

            arr.push_back(a.substr(i,(j-i-1)));
            i=j+1;
        }
        //if we dont have , in the sograim;
        if(!flag) {
            arr.push_back(a);
        } else {
            arr.push_back(a.substr(i,(a.length()-i)));
        }

        return a.length();
}
void lexer(ifstream &file,vector<string>& arr){
    string line,temp;
    int i,j,k,l;
    int length;
    while (getline(file, line)){
        length = line.size();
        i=0;
        j=0;
       for(i=0;i<length;i++) {
           if (line[i] == ' ') {
               arr.push_back(line.substr(j, (i - j)));
               j = i + 1;
           } else if (line[i] == '(') {
               if (j != i) {
                   arr.push_back(line.substr(j, (i - j)));
               }
               j = i + 1;
               k = parenth(line, i, arr);
               i = i + k + 2;
               j = j + k + 2;


           }
       }
       if(j!=i){
           arr.push_back(line.substr(j, (i - j)));
       }
    }

}
int main(int args, char* argv[]) {
    ifstream infile(argv[1]);
    vector<string> arr;
    lexer(infile,arr);
    printf("hello");
    return 0;
}