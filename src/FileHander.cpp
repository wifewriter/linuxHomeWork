//
// Created by yy on 2020/11/4.
//
#include "../include/FileHander.h"
#include <iostream>

#ifdef __WIN32__
#include <io.h>
#endif

#ifdef __clang__
#include <dirent.h>
#endif

#include <vector>
#include "../include/GloableDefine.h"
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include "commonHandler.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>

using namespace std;

File_Hander::File_Hander() {
    cout << "File_Hander Init !" << endl;
//    初始化索引文件
    creatIndexFile();
//    初始化一行的字节数
    rowOfbyte = 3 * ATTRIBUTES;
    vector<string> files;
    cout << "starting get table list..." << endl;
    this->getFiles(FILEPATH, files);
    Sum_File = files.size();
//    暂存当前tableFile所存储的文件夹
    temp_Path = FILEPATH;
    temp_Path.append("/");
//    初始化一个存放随机100条属性的数组
//    this->tempRandomData = new char[ATTRIBUTES];
    if (Sum_File > 0) {
        for (int i = 0; i < this->Sum_File; ++i) {
            cout << files[i].c_str() << endl;
        }
        cout << "Enter file name which you want to open" << endl;
        cin >> this->tempFileName;
        temp_Path.append(this->tempFileName);
        if (((f_fd = open(temp_Path.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) < 0)) {
            perror("open ERROR!");
        } else {
            cout << "Open Success!" << endl;
            cout<<"creating index Files"<<endl;
            creatIndexFile();
        }
    } else {
        cout << "No table files are currently created!" << endl;
        cout << "Please enter the name of the table you want to create" << endl;
        cin >> this->tempFileName;
        temp_Path.append(this->tempFileName);
        if ((this->f_fd = open(temp_Path.c_str(), O_RDWR | O_APPEND | O_CREAT) < 0)) {
            perror("open ERROR!");
        } else {
            cout << "Table creation successful" << endl;
            this->Sum_File++;
        }
    }
}

File_Hander::~File_Hander() {
    close(f_fd);
    cout << "File_Hander class Exit!" << endl;
}

void File_Hander::getFiles(string path, vector<string> &files) {

#ifdef __clang__
//根据当前系统来判断是否该引入io.h这个头文件，linux和unix没有io.h头文件。
void File_Hander::getFiles(string path,vector<string>& filenames)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
        return;
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            filenames.push_back(path + "/" + ptr->d_name);
    }
    closedir(pDir);
}
#else
void File_Hander::getFiles(string path , vector<string> &files){
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    p.assign(path).append("/*");
    cout << "The current data file path is：(" << p.c_str() << ")" << endl;
    if ((hFile = _findfirst(p.c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("/").append(fileinfo.name), files);
            } else {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}
#endif


int File_Hander::appendArowToFile() {
    lseek(f_fd, 0, SEEK_END);
    char temp_Cin;
    cout << "Manual(m) or automatic(a)？" << endl;
    cin >> temp_Cin;
    if (temp_Cin == 'm' || temp_Cin == 'M') {
//        手动添加
        cout << "enter" << ATTRIBUTES << "value" << " and separated by a blank space " << endl;
        cout << "Limit range of 00-99" << endl;
        string *tempWriteManual = reinterpret_cast<string *>(new vector<string>[2 * ATTRIBUTES]);
        for (int i = 0; i < 2 * ATTRIBUTES; ++i) {
            cin >> tempWriteManual[i++];
            if (i < 2 * ATTRIBUTES - 1) {
                tempWriteManual[i] += '\t';
            } else {
                tempWriteManual[i] += '\n';
            }
        }
        if (write(f_fd, tempWriteManual->c_str(), 2 * ATTRIBUTES)) {
            cout << "write Successed!" << endl;
            delete[] tempWriteManual;
            return 0;
        } else {
            cout << "write Error!" << endl;
            delete[] tempWriteManual;
            return 1;
        }
    } else if (temp_Cin == 'A' || temp_Cin == 'a') {
//        自动添加
        int Rows = getLineNum();
        int numRows;
        cout << "input how many rows you want to generate" << endl;
        cin >> numRows;
        if (Rows + numRows > MAXROW) {
            cout << "Exceed the maximum allowable number" << endl;
        }
        cout << "Now Generating random 100 attribute values..." << endl;
//        char temp_char_WriteIn[4];
//      设置随机种子，在循环外。
        srand((int) time(0));
        for (int i = 0; i < numRows; ++i) {
            this->importRandomData();
            for (int j = 0; j < 2 * ATTRIBUTES; j += 2) {
//                strcpy(temp_char_WriteIn,numToString(tempRandomData[j]).c_str());
                write(f_fd, &tempRandomData[j], 2 * sizeof(char));
                if (j < 2 * ATTRIBUTES - 2) {
                    char temp[1] = {'\t'};
                    write(f_fd, temp, 1);
                } else {
                    char temp[1] = {'\n'};
                    write(f_fd, temp, 1);
                }
            }
        }
        cout << "There are " << Rows + numRows << "rows in the current table" << endl;
    } else {
        cout << "enter ERROR .back!" << endl;
        return 1;
    }
    return 0;
}

void File_Hander::creatIndexFile() {
//    针对每一个属性，建立对应的索引文件
    int temp_Index_fd;
    string temp_Index_FilePath = INDEXFILEPATH;
    temp_Index_FilePath.append("/index");
    char temp[3];
    int temp_Rows = getLineNum();
    if (temp_Rows > 0) {
        int array[temp_Rows];
        int rowsIndex[temp_Rows];
        memset(array, 0, temp_Rows * sizeof(int));
        memset(temp,'\0',3);
        memset(rowsIndex,0,temp_Rows* sizeof(int));
        for (int i = 0; i < ATTRIBUTES; ++i) {
            if ((temp_Index_fd = open((temp_Index_FilePath + numToString(i)).c_str(), O_RDWR | O_CREAT,S_IRUSR | S_IWUSR)) < 0) {
                perror("indexFile create Error");
            } else {
//            打开文件成功,一下将每一个属性值放入数组缓存中。
                lseek(f_fd,3*i,SEEK_SET);
                for (int j = 0; j < temp_Rows; ++j) {
                    if(read(f_fd,temp,3) > 0) {
                        array[j] = stringToNum((string)temp);
                        lseek(f_fd,(j+1)*(rowOfbyte+1)+3*i,SEEK_SET);
                    } else{
                        continue;
                    }
                }
//                索引行数数组初始化
                for (int k = 0; k < temp_Rows; ++k) {
                    rowsIndex[k] = k;
                }


                close(temp_Index_fd);
            }
        }
    } else {
        cout << "empty file has no indexs！" << endl;
        return;
    }

}

int File_Hander::deleteArowToFile() {
    cout << "enter the NO.rows you want to delete!" << endl;
    int temp_Delete_Rows;
    cin >> temp_Delete_Rows;
//    定位到下一行
    lseek(f_fd, temp_Delete_Rows * rowOfbyte + 1, SEEK_SET);
    char byteBuffer[rowOfbyte];
    int count = read(f_fd, byteBuffer, rowOfbyte + 1);
//    缓存文件结束符
    char tempchar[1] = {'\n'};
    do {
        if (count > 0) {
            lseek(f_fd, -2 * (rowOfbyte + 1), SEEK_CUR);
            write(f_fd, byteBuffer, rowOfbyte);
        } else {
            lseek(f_fd, 0, SEEK_SET);
            write(f_fd, tempchar, 1);
            break;
        }
        lseek(f_fd, rowOfbyte + 1, SEEK_CUR);
        count = read(f_fd, byteBuffer, rowOfbyte + 1);
        if (count == 0) {
//            当前自动删掉一行，则用全0填充
            for (int i = 0; i < rowOfbyte; ++i) {
                if ((i + 1) % 3 == 0) {
                    continue;
                } else {
                    byteBuffer[i] = '0';
                }
            }
            lseek(f_fd, -1 * (rowOfbyte + 1), SEEK_CUR);
            write(f_fd, byteBuffer, rowOfbyte);
            break;
        }
    } while (count > 0);
    return 0;
}

int File_Hander::alterArowToFile() {
    int temp_row = 0;
    int temp_ATT = 0;
    char temp_value[2];
    string temp_str;
    cout << "input the row you want to alter,and the Attribute" << endl;
    cin >> temp_row >> temp_ATT;
    cout << "input the attribute and the value" << endl;
    cin >> temp_str;
    for (int i = 0; i < 2; ++i) {
        temp_value[i] = temp_str[i];
    }
    lseek(f_fd, (temp_row - 1) * (rowOfbyte + 1), SEEK_SET);
    char byteBuffer[rowOfbyte];
    int count = read(f_fd, byteBuffer, rowOfbyte + 1);
    byteBuffer[3 * (temp_ATT - 1)] = temp_value[0];
    byteBuffer[3 * (temp_ATT - 1) + 1] = temp_value[1];
    lseek(f_fd, -1 * (rowOfbyte + 1), SEEK_CUR);
    write(f_fd, byteBuffer, rowOfbyte);
    return 0;
}

void File_Hander::searchFileCondition() {

}

void File_Hander::showCurrentTableData() {
    lseek(f_fd, 0, SEEK_SET);
    char temp_str;
    int No_table = 0;
    int count = 0;
    int rowsNum = getLineNum();
    char buffers[rowOfbyte];
    do {
        cout << "now show --------------------------" << No_table << '-' << No_table + EVERTIMESHOWROWS << "("
             << rowsNum << ")" << "-----------------------------rows" << endl;
//        每次显示10条记录
        for (int i = 0; i < EVERTIMESHOWROWS; ++i) {
            count = read(f_fd, buffers, rowOfbyte);
            lseek(f_fd, 1, SEEK_CUR);
            cout << buffers;
        }
        cout << "any key to next page ,'q' quit!" << endl;
        cin >> temp_str;
        No_table += EVERTIMESHOWROWS;
    } while (temp_str != 'q' && count > 0);
}

int File_Hander::judgeFileExist() {
    if (Sum_File > 0) {
        return 1;
    } else {
        return 0;
    }
}

void File_Hander::importRandomData() {
    for (int i = 0; i < 2 * ATTRIBUTES;) {
        this->tempRandomData[i++] = '0' + (rand() % 100) / 10;
        this->tempRandomData[i++] = '0' + (rand() % 100) % 10;
    }
}

bool File_Hander::judgeAddOrNot() {
    if (this->Sum_File == 0) {
        return true;
    } else {
        return false;
    }
}

int File_Hander::getLineNum(string path) {
    ifstream ReadFile;
    int n = 0;
    string tmp;
    string readPath;
    if (path == "") {
//        没有参数则默认获取当前打开的表文件
        readPath = temp_Path;
    } else {
        readPath = path;
    }
    //ios::in 表示以只读的方式读取文件
    ReadFile.open(readPath, ios::in);
    if (ReadFile.fail()) {
        //文件打开失败:返回0
        return 0;
    } else//文件存在
    {
        while (getline(ReadFile, tmp, '\n')) {
            n++;
        }
        ReadFile.close();
        return n;
    }
}