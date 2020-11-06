//
// Created by yy on 2020/11/4.
//
#include "../include/FileHander.h"

#include <iostream>
#include <io.h>
#include <vector>
#include "../include/GloableDefine.h"
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;

File_Hander::File_Hander() {
    cout<<"文件处理类初始化"<<endl;
    vector<string> files;
    cout<<"开始获取当前数据表..."<<endl;
    this->getFiles(FILEPATH, files);
    this->Sum_File = files.size();
//    暂存当前tableFile所存储的文件夹
    string temp_Path = FILEPATH;
    temp_Path.append("/");
    if(this->Sum_File > 0){
        for (int i = 0; i < this->Sum_File; ++i) {
            cout << files[i].c_str() << endl;
        }
        cout<<"请输入要打开的文件"<<endl;
        cin>>this->tempFileName;
        temp_Path.append(this->tempFileName);
        if((this->f_fd = open(temp_Path.c_str(),O_RDWR|O_APPEND|O_CREAT,S_IRUSR|S_IWUSR) <0)){
            perror("open ERROR!");
        } else{
            cout << "文件打开成功"<<endl;
            this->Sum_File++;
        }
    }
    else{
        cout<<"当前还未创建任何表文件"<<endl;
        cout<<"请输入需要创建的表名English"<<endl;
        cin>>this->tempFileName;
        temp_Path.append(this->tempFileName);
        if((this->f_fd = open(temp_Path.c_str(),O_RDWR|O_APPEND|O_CREAT) <0)){
            perror("open ERROR!");
        } else{
            cout << "文件创建成功"<<endl;
            this->Sum_File++;
        }
    }
}
File_Hander::~File_Hander() {
    close(f_fd);
    cout<<"文件处理类退出"<<endl;
}

void File_Hander::getFiles(string path , vector<string> &files){
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p ;
    p.assign(path).append("/*");
    cout<<"当前数据文件路径是：("<<p.c_str() <<")"<<endl;
    if((hFile = _findfirst(p.c_str(),&fileinfo))!= -1){
        do{
            if((fileinfo.attrib & _A_SUBDIR)){
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                    getFiles( p.assign(path).append("/").append(fileinfo.name), files );
            } else{
                files.push_back(p.assign(path).append("/").append(fileinfo.name) );
            }
        }while (_findnext(hFile,&fileinfo) == 0);
        _findclose(hFile);
    }
}
bool File_Hander::judgeAddOrNot(){
    if(this->Sum_File == 0){
        return true;
    } else{
        return false;
    }
}
