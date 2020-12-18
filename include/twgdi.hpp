#pragma once
#ifndef _TW_GDI_HPP_
#define _TW_GDI_HPP_

#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <GdiPlus.h>
#include <dxgi.h>
#include <cmath>

#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

inline LPCWSTR ConvertChartoWchar(const char* s) //将字符串转为宽字符串
{
    int num = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
    wchar_t* w_s = new wchar_t[num];
    MultiByteToWideChar(0, 0, s, -1, w_s, num);
    return w_s;
}

inline void RGBChange(int* a, int* b, int* c)      //RGB渐变 
{
    static int da = 1;
    static int db = 1;
    static int dc = 1;
    if (*a >= 255 || *a <= 0) da = -da;
    if (*b >= 255 || *b <= 0) db = -db;
    if (*c >= 255 || *c <= 0) dc = -dc;
    *a += da;
    *b += db;
    *c += dc;
}

void ScreenCapture(const char * filename, HWND hWnd)  //截图保存路径,要截图的窗口句柄，全屏截图则为NULL
{

    HDC hdc = CreateDC("DISPLAY", NULL, NULL, NULL);
    int32_t ScrWidth = 0, ScrHeight = 0;
    RECT rect = { 0 };
    if (hWnd == NULL)
    {
        ScrWidth = GetDeviceCaps(hdc, HORZRES);
        ScrHeight = GetDeviceCaps(hdc, VERTRES);
    }
    else
    {
        GetWindowRect(hWnd, &rect);
        ScrWidth = rect.right - rect.left;
        ScrHeight = rect.bottom - rect.top;
    }
    HDC hmdc = CreateCompatibleDC(hdc);

    HBITMAP hBmpScreen = CreateCompatibleBitmap(hdc, ScrWidth, ScrHeight);
    HBITMAP holdbmp = (HBITMAP)SelectObject(hmdc, hBmpScreen);

    BITMAP bm;
    GetObject(hBmpScreen, sizeof(bm), &bm);

    BITMAPINFOHEADER bi = { 0 };
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bm.bmWidth;
    bi.biHeight = bm.bmHeight;
    bi.biPlanes = bm.bmPlanes;
    bi.biBitCount = bm.bmBitsPixel;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = bm.bmHeight * bm.bmWidthBytes;
    // 图片的像素数据
    char* buf = new char[bi.biSizeImage];
    BitBlt(hmdc, 0, 0, ScrWidth, ScrHeight, hdc, rect.left, rect.top, SRCCOPY);
    GetDIBits(hmdc, hBmpScreen, 0L, (DWORD)ScrHeight, buf, (LPBITMAPINFO)&bi, (DWORD)DIB_RGB_COLORS);

    BITMAPFILEHEADER bfh = { 0 };
    bfh.bfType = ((WORD)('M' << 8) | 'B');
    bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    DWORD dwWrite;
    WriteFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwWrite, NULL);
    WriteFile(hFile, &bi, sizeof(BITMAPINFOHEADER), &dwWrite, NULL);
    WriteFile(hFile, buf, bi.biSizeImage, &dwWrite, NULL);
    CloseHandle(hFile);
    hBmpScreen = (HBITMAP)SelectObject(hmdc, holdbmp);
}

void DrawRectangle(
int x,  
int y,         //矩形左上角x,y坐标
int width,     //宽
int height,    //高
int r,int g,int b //RGB
)
{

    HWND hwnd;
    HDC hdc;
    RECT rec;
    hwnd = GetDesktopWindow();
    hdc = GetDC(hwnd);
    //Rectangle(hdc,x, y, x + width, y + height);
    rec.left = x;
    rec.top = y;
    rec.right = x + width;
    rec.bottom = y + height;
    
    HBRUSH hbrush=CreateSolidBrush(RGB(r, g, b));
    FillRect(hdc, &rec, hbrush);
    ReleaseDC(hwnd, hdc);
    DeleteObject(hbrush);
}


void DrawPoint(
    int x,
    int y,         //坐标
    int width,     //点的直径
    short r,      
    short g,
    short b
)
{
    HWND hwnd;
    HDC hdc;
    HPEN hpen;
    hwnd = GetDesktopWindow();  
    hdc = GetDC(hwnd);
    //srand((unsigned)time(NULL));
    hpen = CreatePen(PS_SOLID, width, RGB(r, g, b));
    SelectObject(hdc, hpen);
    MoveToEx(hdc, x , y, NULL);
    LineTo(hdc, x, y);   
    DeleteObject(hpen);
    ReleaseDC(hwnd, hdc);
}

void DrawLine(
    int sx,             //起点x
    int sy,             //起点y
    int ex,             //终点x
    int ey,             //终点y
    int width,           //线宽
    int r, int g ,int b  //颜色RGB      
)
{

    HWND hwnd;
    HDC hdc;
    HPEN hpen;
    hwnd = GetDesktopWindow();  
    hdc = GetDC(hwnd);
    hpen = CreatePen(PS_SOLID, width, RGB(r, g, b));
    SelectObject(hdc, hpen);
    MoveToEx(hdc, sx , sy, NULL);
    LineTo(hdc, ex, ey);
    DeleteObject(hpen);
    ReleaseDC(hwnd, hdc);
}

void DrawBMP(       //自动获取位图的尺寸并在指定位置显示（不缩放）
    const char * path,
    int x,
    int y //BMP图像要显示的位置，左上顶点的xy坐标
    )
{
    HWND hwnd;
    HDC hdc;
    hwnd = GetDesktopWindow();
    hdc = GetDC(hwnd);          
    HBITMAP hBitmap;
    hBitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)path, IMAGE_BITMAP, 
        0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    HDC cmdmem = CreateCompatibleDC(hdc);       
    BITMAP bi = { 0 };
    GetObject(hBitmap, sizeof(BITMAP), &bi);        //获取位图信息
    int width = bi.bmWidth;                         //获取位图的宽度
    int height = bi.bmHeight;           
    SelectObject(cmdmem, hBitmap);
    BitBlt(hdc, x, y, width, height, cmdmem, 0, 0, SRCCOPY);
    DeleteObject(hBitmap);
    ReleaseDC(hwnd,hdc);
}

void RotateLine(
    int st_x,       
    int st_y,       //起点坐标
    int angle,      //线段所成角，→为0°，↓为90°，依次类推
    int l,          //线段长度
    int * ed_x,     //终点坐标
    int * ed_y
)
{
    const double pi = 3.14159;
    *ed_x = st_x + cos(pi * angle / 180) * l;
    *ed_y = st_y + sin(pi * angle / 180) * l;
}

void DrawLineA(
    int x,
    int y,
    int angle,
    int l,
    int w,
    int r,int g,int b
)
{
    int ed_x, ed_y;
    RotateLine(x,y,angle,l,&ed_x,&ed_y);
    DrawLine(x,y,ed_x,ed_y,w,r,g,b);
}

class cat
{

private:
    int x, y;   //全屏幕位置坐标
    int r, g, b;
    int angle;
    int w;
    int auto_shade; //自动渐变色
    const double pi = 3.14159;

public:
    cat(int _x, int _y) :x(_x), y(_y) { 
        r = 255; g = 255; b = 255; angle = 0; w = 1;
        auto_shade = 0;
    } //初始颜色为白色

    inline void setWidth(int width)
    {
        if (w > 0) return;
        w = width;
    }
    
    inline void autoShade(int state)
    {
        if(state==0||state==1) 
            auto_shade=state;
    }

    inline void setColor(int r,int g,int b) {           //设置颜色RGB
        if (r < 0 || r>255 || g < 0 || g>255 || b < 0 || b>255) return;
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    inline void changeColor()            //颜色变换
    {   
        RGBChange(&r,&g,&b);
    }
    inline void changeColor(void (*rgbchange)(int*,int*,int*))      //颜色变换重载：传入rgb变换函数
    {
        rgbchange(&r,&g,&b);
    }
    
    inline void randColor()             //随机颜色
    {
        srand((unsigned)time(NULL));
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
    }
    
    inline void forward(int dist)
    {
        int ed_x = x + dist * cos(pi*angle/180);
        int ed_y = y - dist * sin(pi*angle/180);
        DrawLine(x, y, ed_x, ed_y, w, r, g, b);
        if (auto_shade) this->changeColor();
        x = ed_x;
        y = ed_y;
    }
    inline void backward(int dist)
    {
        int ed_x = x - dist * cos(pi*angle/180);
        int ed_y = y + dist * sin(pi*angle/180);
        DrawLine(x, y, ed_x, ed_y, w, r, g, b);
        if (auto_shade) this->changeColor();
        x = ed_x;
        y = ed_y;
    }

    inline void move(int dist)
    {
         x = x + dist * cos(angle);
         y = y - dist * sin(angle);
    }
    inline int getAngle()
    {
        return this->angle;
    }

    inline void setAngle(int ang)
    {
        this->angle = ang % 360;
    }

    inline void right(int ang)
    {
        angle = (angle + ang) % 360;
    }

    inline void left(int ang)
    {
        angle = (angle - ang) % 360;
    }

};

#endif //_TW_GDI_HPP_