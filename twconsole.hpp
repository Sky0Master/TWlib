#pragma once
#ifndef _TW_CONSOLE_H_
#define _TW_CONSOLE_H_

#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>

void COLOR_PRINT(const char* s,int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
    printf(s);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);   //改回白色
    
}
void COLOR_PRINT2(const char* s, int front_color,int back_color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | back_color*16 |FOREGROUND_INTENSITY | front_color);
	printf(s);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);  
}

/*
0 = 黑色       8 = 灰色
1 = 蓝色       9 = 淡蓝色
2 = 绿色       10 = 淡绿色
3 = 浅绿色     11 = 淡浅绿色
4 = 红色       12 = 淡红色
5 = 紫色       13 = 淡紫色
6 = 黄色       14 = 淡黄色
7 = 白色       15 = 亮白色 
*/

#endif //_TW_CONSOLE_H_