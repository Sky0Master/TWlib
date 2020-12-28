#pragma once
#ifndef _TW_IO_HPP_
#define _TW_IO_HPP_

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <direct.h>

//返回全部文本为一个string
 std::string read_Textfile(const char* filename);             

//从文件开头位置写入 返回成功写入的字节数
 std::size_t write_Textfile(const char* filename, std::string text); 

//在文件末尾添加文本 返回成功写入的字节数
 std::size_t append_Textfile(const char* filename, std::string text);


//创建目录,失败返回1
 int create_Directory(const char* folderpath);


//删除目录,失败返回1
 int delete_Directory(const char* folderpath);

 //获取文件大小
 size_t getFileSize(const char* filename);


 // 读取二进制文件，返回文件大小
 size_t readBinaryFile(const char* filename,unsigned char* & data);  //unsigned char也可写作byte，BYTE


 //写入二进制文件
 size_t writeBinaryFile(const char* filename,const unsigned char* data, size_t size);  //size：要写入的数据大小(单位：字节)


template<typename OB>
void saveObject(const char* filename, OB & object); //传入要保存的对象引用


template<typename OB>
void readObject(const char* filename, OB* object); //传入读取之后对象存储的指针


#endif  //_TW_IO_HPP_
