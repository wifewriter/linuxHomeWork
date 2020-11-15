//
// Created by yy on 2020/11/7.
//

#ifndef LINUX_FOR_YY2020_COMMONHANDLER_H
#define LINUX_FOR_YY2020_COMMONHANDLER_H
#include <string>
#include <vector>
std::string numToString(int);
int stringToNum(std::string);
int sortIndexArray(int*,int*, int);
std::vector<std::string> splitstring(std::string , char);
void *threadCreatIndexFile(void*);
#endif //LINUX_FOR_YY2020_COMMONHANDLER_H
