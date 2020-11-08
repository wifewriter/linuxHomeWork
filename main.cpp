#include <iostream>
#include <fcntl.h>
#include "FileHander.h"
#include "GloableDefine.h"
#include <process.h>

using namespace std;
int main() {
    cout<< "linux 2020 homework 202021230110 yangyang"<< endl;
    File_Hander* temp_File = new File_Hander;
    bool system_Flag = true;
    char temp_Cin;
    if(temp_File->judgeAddOrNot()){
//        没有任何文件
        cout<<"No Files"<<endl;
        return 0;
    }
    else{
        cout << "enter the system(y/n)?" << endl;
        cin>>temp_Cin;
        if (temp_Cin == 'y') {
            system_Flag = true;
        }
        else {
            system_Flag = false;
            delete temp_File;
        }
        while (system_Flag) {
//            清屏
//            system("cls");
//          增
            cout<<"a-------InsertData"<<endl;
//            删
            cout<<"b-------DeleteData"<<endl;
//            改
            cout<<"c-------UpdateData"<<endl;
//            查
            cout<<"d-------SearchData"<<endl;
//          查看当前数据
            cout<<"e-------ShowData"<<endl;
            cin>>temp_Cin;
            if(temp_Cin =='a' ||temp_Cin =='b' ||temp_Cin =='c' ||temp_Cin =='d'||temp_Cin =='e'){
                switch(temp_Cin){
                    case 'a':
                        if(temp_File->appendArowToFile())
                            continue;
                        break;
                    case 'b':
                        if(temp_File->deleteArowToFile())
                            continue;
                        break;
                    case 'c':
                        temp_File->alterArowToFile();
                        break;
                    case 'd':
                        temp_File->searchFileCondition();
                        break;
                    case 'e':
                        temp_File->showCurrentTableData();
                        break;
                    default:
                        continue;
                }
            }
        }
        return 0;
    }
}
