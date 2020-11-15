//
// Created by yy on 2020/11/7.
//

#include "commonHandler.h"
#include <string>
#include <sstream>
using namespace std;
string numToString(int i){
    stringstream ss;
    ss<<i;
    return ss.str();
}
int stringToNum(string s){
    int num;
    stringstream ss(s);
    ss>>num;
    return num;
}
int sortIndexArray(int a[],int b[],int length){
    for (int i = 0; i < length; ++i) {
        
    }
}