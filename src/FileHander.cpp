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
#include <time.h>
#include <stdlib.h>
#include "commonHandler.h"
#include <unistd.h>
using namespace std;

File_Hander::File_Hander() {
    cout<<"File_Hander Init !"<<endl;
    vector<string> files;
    cout<<"starting get table list..."<<endl;
    this->getFiles(FILEPATH, files);
    Sum_File = files.size();
//    暂存当前tableFile所存储的文件夹
    string temp_Path = FILEPATH;
    temp_Path.append("/");
//    初始化一个存放随机100条属性的数组
//    this->tempRandomData = new char[ATTRIBUTES];
    if(Sum_File > 0){
        for (int i = 0; i < this->Sum_File; ++i) {
            cout << files[i].c_str() << endl;
        }
        cout<<"Enter file name which you want to open"<<endl;
        cin>>this->tempFileName;
        temp_Path.append(this->tempFileName);
        if((f_fd = open(temp_Path.c_str(),O_RDWR|O_APPEND|O_CREAT,S_IRUSR|S_IWUSR) <0)){
            perror("open ERROR!");
        } else{
            cout << "Open Success!"<<endl;
        }
    }
    else{
        cout<<"No table files are currently created!"<<endl;
        cout<<"Please enter the name of the table you want to create"<<endl;
        cin>>this->tempFileName;
        temp_Path.append(this->tempFileName);
        if((this->f_fd = open(temp_Path.c_str(),O_RDWR|O_APPEND|O_CREAT) <0)){
            perror("open ERROR!");
        } else{
            cout << "Table creation successful"<<endl;
            this->Sum_File++;
        }
    }
}
File_Hander::~File_Hander() {
    close(f_fd);
    cout<<"File_Hander class Exit!"<<endl;
}
void File_Hander::getFiles(string path , vector<string> &files){
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p ;
    p.assign(path).append("/*");
    cout<<"The current data file path is：("<<p.c_str() <<")"<<endl;
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

void File_Hander::creatIndexFile() {

}
int File_Hander::appendArowToFile() {
    char temp_Cin;
    cout<<"Manual(m) or automatic(a)？"<<endl;
    cin>>temp_Cin;
    if(temp_Cin == 'm' || temp_Cin =='M'){
//        手动添加
        cout << "enter"<<ATTRIBUTES<<"value"<<" and separated by a blank space "<<endl;
        cout<<"Limit range of 00-99"<<endl;
        string* tempWriteManual = reinterpret_cast<string *>(new vector<string>[2*ATTRIBUTES]);
        for (int i = 0; i < 2*ATTRIBUTES ; ++i) {
            cin>>tempWriteManual[i++];
            if(i<2*ATTRIBUTES-1){
                tempWriteManual[i] += '\t';
            } else{
                tempWriteManual[i] += '\n';
            }
        }
        if(write(f_fd,tempWriteManual->c_str(),2*ATTRIBUTES)){
            cout<<"write Successed!"<<endl;
            delete[] tempWriteManual;
            return 0;
        } else{
            cout<<"write Error!"<<endl;
            delete[] tempWriteManual;
            return 1;
        }
    }
    else if(temp_Cin =='A' || temp_Cin == 'a'){
//        自动添加
        int numRows;
        cout<<"input how many rows you want to generate"<<endl;
        cin>>numRows;
        cout<<"Now Generating random 100 attribute values..."<<endl;
        for (int i = 0; i < numRows; ++i) {
            this->importRandomData();
            for (int j = 0; j < ATTRIBUTES; ++j) {
                write(f_fd,&(tempRandomData[j]), sizeof(char));
                if(j<ATTRIBUTES-1) {
                    char temp[1] = {'\t'};
                    write(f_fd, temp, 1);
                } else{
                    char temp[1] = {'\n'};
                    write(f_fd, temp, 1);
                }
            }
        }
    } else{
        cout<<"输入错误，返回"<<endl;
        return 1;
    }
    return 0;
}


int File_Hander::deleteArowToFile() {
    return 0;

}
int File_Hander::alterArowToFile() {
    return 0;

}
void File_Hander::searchFileCondition() {

}
void File_Hander::showCurrentTableData() {


}
int File_Hander::judgeFileExist() {

    return 0;
}

void File_Hander::importRandomData() {
    srand((int)clock());
    for (int i = 0; i < 2*ATTRIBUTES; ++i) {
        this->tempRandomData[i++] = '0'+rand()%100;
    }
}
bool File_Hander::judgeAddOrNot(){
    if(this->Sum_File == 0){
        return true;
    } else{
        return false;
    }
}

