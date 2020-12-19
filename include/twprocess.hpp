#pragma once

#ifndef _TW_PROCESS_H_
#define _TW_PROCESS_H_

#include <Windows.h>
#include <Tlhelp32.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    HWND hWnd;
    DWORD dwPid;
}   WNDINFO;

//对每个进程调用func函数
void dispose_AllProcess(void (*func)(PROCESSENTRY32&));

//枚举进程窗口
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

//通过进程ID获取窗口句柄
HWND GetHwndByProcessId(DWORD dwProcessId);

//隐藏自身
void hide_Self();

//显示自身
void show_Self();

//最大化自身
void maximize_Self();

//最小化自身
void minimize_Self();

//隐藏窗口
void hide_Window(HWND hW);

//显示窗口
void show_Window(HWND hW);

//打印所有进程的ID和进程名，仅控制台可用
void print_AllProcess();  

//通过进程名获取进程ID
DWORD GetProcessIDbyName(const char* name);

//结束指定进程
void KillProcess(PROCESSENTRY32& process);

//结束所有进程（慎用）
void KillAll();

#endif  //_TW_PROCESS_H_