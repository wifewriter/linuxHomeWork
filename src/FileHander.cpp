//
// Created by yy on 2020/11/4.
//
#include <iostream>
#include "../include/FileHander.h"
#include <io.h>
#include <vector>
#include "../include/GloableDefine.h"
#include <string>
using namespace std;

File_Hander::File_Hander() {
    cout<<"文件处理类初始化"<<endl;
    vector<string> files;
    getFiles(FILEPATH,files);
    f_fd = open()
}
File_Hander::~File_Hander() {
    close(f_fd);
    cout<<"文件处理类退出"<<endl;
}
void File_Hander::getFiles(string path,vector<string> &files){
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p ;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo))!= -1){
        do{
            if((fileinfo.attrib & _A_SUBDIR)){
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
            } else{
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
            }
        }while (_findnext(hFile,&fileinfo) == 0);
        _findclose(hFile);
    }
}