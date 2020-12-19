#pragma once
#ifndef _TW_GDI_HPP_
#define _TW_GDI_HPP_

#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <GdiPlus.h>
#include <cmath>

#pragma comment(lib, "Gdiplus.lib")

//将字符串转为宽字符串
LPCWSTR ConvertChartoWchar(const char* s); 

void RGBChange(int* a, int* b, int* c);     


//filename:截图保存路径,   hWnd:要截图的窗口句柄，全屏截图则为NULL
void ScreenCapture(const char * filename, HWND hWnd);

// 绘制实心矩形
void DrawRectangle(
    int x,
    int y,         //矩形左上角x,y坐标
    int width,     //宽
    int height,    //高
    int r, int g, int b, //RGB
    HWND hwnd
);

//绘制点
void DrawPoint(
    int x,
    int y,         //坐标
    int width,     //点的直径
    short r,      
    short g,
    short b,
    HWND hwnd
);

//绘制直线
void DrawLine(
    int sx,             //起点x
    int sy,             //起点y
    int ex,             //终点x
    int ey,             //终点y
    int width,           //线宽
    int r, int g ,int b,  //颜色RGB      
    HWND hwnd
);

//绘制bmp位图
void DrawBMP(       //自动获取位图的尺寸并在指定位置显示（不缩放）
    const char * path,
    int x,
    int y, //BMP图像要显示的位置，左上顶点的xy坐标
    HWND hwnd  //绘制目标窗口的句柄，若为NULL则为整个屏幕
);

//计算旋转直线
void RotateLine(
    int st_x,       
    int st_y,       //起点坐标
    int angle,      //线段所成角，→为0°，↓为90°，依次类推
    int l,          //线段长度
    int * ed_x,     //终点坐标
    int * ed_y
);

//指定起点和角度绘制直线
void DrawLineA(
    int x,
    int y,
    int angle,
    int l,
    int w,
    int r,int g,int b,
    HWND hwnd
);


class cat
{

private:
    int x, y;   //全屏幕位置坐标
    int r, g, b;
    int angle;
    int w;
    int auto_shade; //自动渐变色
    const double pi = 3.14159;
    HWND hwnd;

public:
    //初始化，初始颜色为白色
    cat(HWND hwnd,int _x, int _y);

    void setWidth(int width);
    
    void autoShade(int state);

    void setColor(int r,int g,int b);
    
     //颜色变换
    void changeColor();            
 
     //颜色变换重载：传入rgb变换函数
    void changeColor(void (*rgbchange)(int*,int*,int*));      


    //随机变换一次颜色
    void randColor();             

    //向前移动指定距离(绘画)
    void forward(int dist);
  
    //向后移动指定距离(绘画)
    void backward(int dist);
   
    //移动但不绘画
    void move(int dist);

    int getAngle();
    
    void setAngle(int ang);
 
    void right(int ang);

    void left(int ang);

};

#endif //_TW_GDI_HPP_