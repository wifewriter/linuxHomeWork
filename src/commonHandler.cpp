//
// Created by yy on 2020/11/7.
//

#include "commonHandler.h"
#include <string>
#include <sstream>
#include <FileHander.h>
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
/**
 *  对数组进行排序和添加索引
 * @param a 待排序数组
 * @param b 索引行数数组
 * @param length
 * @return int
 */
int sortIndexArray(int a[],int b[],int length){
//    冒泡排序
    int temp;
    bool flag = true;
    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < length-i; ++j) {
            if(a[j]>a[j+1]){
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
//                更换索引
                temp = b[j+1];
                b[j+1] = b[j];
                b[j] = temp;
                flag = false;
            }
        }
        if(flag)
            break;
    }
}
vector<string> splitstring(string str,char sp){
    vector<string> r;
    string tmpstr;
    while (!str.empty()){
        int ind = str.find_first_of(sp);
        if (ind == -1){
            r.push_back(str);
            str.clear();
        }
        else{
            r.push_back(str.substr(0, ind));
            str = str.substr(ind + 1, str.size() - ind - 1);
        }
    }
    return r;

}
void *threadCreatIndexFile(void* arg){
    File_Hander *arg1 = (File_Hander *)arg;
    arg1->creatIndexFile();
    return NULL;
}