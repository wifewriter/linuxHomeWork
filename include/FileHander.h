//
// Created by yy on 2020/11/4.
//

#ifndef LINUX_FOR_YY2020_FILEHANDER_H
#define LINUX_FOR_YY2020_FILEHANDER_H
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
//

private:
    int f_fd;
    int index_fd;

};
#endif //LINUX_FOR_YY2020_FILEHANDER_H
