//
// Created by yy on 2020/11/4.
//

#ifndef LINUX_FOR_YY2020_FILEHANDER_H
#define LINUX_FOR_YY2020_FILEHANDER_H

#include <iostream>
#include <string>
#include <vector>
#include <GloableDefine.h>
class File_Hander{
public:
    File_Hander();
    ~File_Hander();
//    增
    int appendArowToFile();
//    删
    int deleteArowToFile();
//    改
    int alterArowToFile();
//    查询
    void searchFileCondition();
//    查看当前打开的文件内容
    void showCurrentTableData();
//     判断当前是否存在表
    int judgeFileExist();
//    随机获取一行数据，有100条属性
    void importRandomData();
//  判断当前系统是否有文件打开 true为空，false非空
    bool judgeAddOrNot();
//  获取当前文件行数,缺省获取当前打开的表文件行数
    int getLineNum(std::string path = "");
    //    创立索引文件
    void creatIndexFile();
private:
    int f_fd;
    int index_fd;
    void getFiles(std::string path, std::vector<std::string> &files);
//    当前表数目计数
    unsigned int Sum_File = 0;
//    存放当前文件名
    std::string tempFileName;

//    存放一行的字节数
    int rowOfbyte;
//    存放当前一行的随机数
    char tempRandomData[2*ATTRIBUTES];
//    存放当前打开文件路径
    std::string temp_Path;
//存放当前打开文件的行数
     int RowsTotal;
//    线程静态函数
    static void *threadCreatIndexFile(void*);
};

#endif //LINUX_FOR_YY2020_FILEHANDER_H
