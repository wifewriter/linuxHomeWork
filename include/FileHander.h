//
// Created by yy on 2020/11/4.
//

#ifndef LINUX_FOR_YY2020_FILEHANDER_H
#define LINUX_FOR_YY2020_FILEHANDER_H

#include <iostream>
#include <string>
#include <vector>
class File_Hander{
public:
    File_Hander();
    ~File_Hander();
//    增
    static int appendArowToFile();
//    删
    static int deleteArowToFile();
//    改
    static int alterArowToFile();
//    查询
    void searchFileCondition();
//    创立索引文件
    void creatIndexFile();
//     判断当前是否存在该表
    int judgeFileExist();
//    用随机数据进行填充
    int importRandomData();
//  判断当前系统是否有文件打开 true为空，false非空
    bool judgeAddOrNot();
//
private:
    int f_fd;
    int index_fd;
    void getFiles(std::string path, std::vector<std::string> &files);
//    当前表数目计数
    unsigned int Sum_File = 0;
    std::string tempFileName;
};
#endif //LINUX_FOR_YY2020_FILEHANDER_H
