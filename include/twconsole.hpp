#pragma once
#ifndef _TW_CONSOLE_H_
#define _TW_CONSOLE_H_

#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>

//使用指定颜色的字体输出
void COLOR_PRINT(const char* s,int color);

//使用指定颜色和背景的字体输出
void COLOR_PRINT2(const char* s, int front_color,int back_color);

/*  颜色说明：
 * 0 = 黑色       8 = 灰色
 * 1 = 蓝色       9 = 淡蓝色
 * 2 = 绿色       10 = 淡绿色
 * 3 = 浅绿色     11 = 淡浅绿色
 * 4 = 红色       12 = 淡红色
 * 5 = 紫色       13 = 淡紫色
 * 6 = 黄色       14 = 淡黄色
 * 7 = 白色       15 = 亮白色 
 */

#endif //_TW_CONSOLE_H_