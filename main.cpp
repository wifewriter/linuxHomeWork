#include <iostream>
#include <fcntl.h>
#include "FileHander.h"
#include "GloableDefine.h"
#include <process.h>

using namespace std;
int main() {
    cout<< "linux 2020 作业 202021230110 杨洋"<< endl;
    File_Hander* temp_File = new File_Hander;
    bool system_Flag = true;
    char temp_Cin;
    if(temp_File->judgeAddOrNot()){
//        没有任何文件
        cout<<"没有文件"<<endl;
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
            system("cls");

        }
        return 0;
    }


}
