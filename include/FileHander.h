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
//
private:
    int f_fd = -1;
    static int index_fd;
    void getFiles(std::string path, std::vector<std::string> &files);
//    当前表数目计数
    unsigned int Sum_File = 0;
    std::string tempFileName;
    //    创立索引文件
    void creatIndexFile();
    char tempRandomData[ATTRIBUTES];
};

#endif //LINUX_FOR_YY2020_FILEHANDER_H
