#pragma once
#ifndef _TW_INPUT_H_
#define _TW_INPUT_H_

#include <stdio.h>
#include <Windows.h>
#include <math.h>

namespace twinput{

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

enum SHORTCUT {
    CTRL = VK_LCONTROL,
    SHIFT = VK_LSHIFT,
    ALT = VK_MENU,
    ESC = VK_ESCAPE,
    WIN = VK_LWIN,
    BACK = VK_BACK,
    TAB = VK_TAB,
    ENTER = VK_RETURN,
    HOME = VK_HOME,
    END = VK_END,
    DEL = VK_DELETE,
    INS = VK_INSERT,
    UP = VK_UP,
    DOWN = VK_DOWN,
    RIGHT = VK_RIGHT,
    LEFT = VK_LEFT,
    F1 = VK_F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    PRTSC = VK_PRINT,
    A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    MOUSE_LEFT = VK_LBUTTON,
    MOUSE_RIGHT = VK_RBUTTON
};

//鼠标按键映射
const int mousemap[3][2]  =  {
        {MOUSEEVENTF_LEFTDOWN  ,   MOUSEEVENTF_LEFTUP   },
        {MOUSEEVENTF_MIDDLEDOWN,   MOUSEEVENTF_MIDDLEUP },
        {MOUSEEVENTF_RIGHTDOWN ,   MOUSEEVENTF_RIGHTUP  }
    };

//键盘按下KEY，再弹起来
void Click(int KEY);  

//r=0 : 设置为小写  r=1 : 设置为大写
void Set_Capital(int r);    


//模拟键盘输入一段文本  delay单位是毫秒
void Enter_Text(char * text,int delay);  


//模拟键盘按下组合键
void Shortcuts(int keyargs, ...);  

//模拟鼠标按键, 0:左键  1:滚轮键  2:右键
void MouseClick(int c);   


//控制鼠标移动  dx,dy:横纵方向控制, 0:该方向不移动，1:正向  -1:反向  （原点左上角）
void MouseMove(int dx, int dy);  

//获取鼠标指针x,y坐标
 void GetMousePos(int* x, int* y); 

}

#endif //_TW_INPUT_H_