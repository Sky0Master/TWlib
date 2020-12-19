#include "include/twprocess.hpp"

void dispose_AllProcess(void (*func)(PROCESSENTRY32&))
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);   //创建当前系统的进程快照
    if (snapshot == INVALID_HANDLE_VALUE)       //快照拍摄失败,返回空句柄
        return;
    PROCESSENTRY32 process;                     //初始化一个进程对象
    SecureZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);
    int POK = Process32First(snapshot, &process);
    for (; POK; POK = Process32Next(snapshot, &process))
        func(process);
    //process.th32ProcessID, process.szExeFile
    CloseHandle(snapshot);

}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    WNDINFO* pInfo = (WNDINFO*)lParam;
    DWORD dwProcessId = 0;
    GetWindowThreadProcessId(hWnd, &dwProcessId);

    if (dwProcessId == pInfo->dwPid)
    {
        pInfo->hWnd = hWnd;
        return FALSE;
    }
    return TRUE;
}

HWND GetHwndByProcessId(DWORD dwProcessId)
{
    WNDINFO info = { 0 };
    info.hWnd = NULL;
    info.dwPid = dwProcessId;
    EnumWindows(EnumWindowsProc, (LPARAM)&info);
    return info.hWnd;
    
}

void hide_Self()            {   ShowWindow(GetForegroundWindow(),SW_HIDE);      }

void show_Self()            {   ShowWindow(GetForegroundWindow(), SW_SHOW);     }

void maximize_Self()        {	ShowWindow(GetForegroundWindow(), SW_MAXIMIZE); }

void minimize_Self()        {   ShowWindow(GetForegroundWindow(), SW_MINIMIZE); }

void hide_Window(HWND hW)   {   ShowWindow(hW, SW_HIDE);                        }

void show_Window(HWND hW)   {   ShowWindow(hW, SW_SHOW);                        }

void print_AllProcess()
{
    DWORD pid = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);   //创建当前系统的进程快照
    if (snapshot == INVALID_HANDLE_VALUE)       //快照拍摄失败,返回空句柄
        return;
    PROCESSENTRY32 process;                     //初始化一个进程对象
    SecureZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);          
    int POK = Process32First(snapshot, &process);
    for (   ; POK; POK = Process32Next(snapshot, &process))
        printf("%d  %ls\n", process.th32ProcessID, process.szExeFile);
    CloseHandle(snapshot);
}

DWORD GetProcessIDbyName(const char * name)
{
    int num = MultiByteToWideChar(0, 0, name, -1, NULL, 0);
    wchar_t* w_name = new wchar_t[num];
    MultiByteToWideChar(0, 0, name, -1, w_name, num);
    //LPCWSTR w_name = (LPCWSTR)name;      //这是错误的写法,不能强制类型转换
    //printf("%ls", w_name);
    DWORD pid = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);   //创建当前系统的进程快照
    if (snapshot == INVALID_HANDLE_VALUE)//快照拍摄失败
        return -1;
    PROCESSENTRY32 process;
    SecureZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);           //初始化一个进程对象
    int POK = Process32First(snapshot, &process);         //获取第一个进程
    for (; POK; POK = Process32Next(snapshot, &process))  //遍历所有进程
        if ( !lstrcmpi(process.szExeFile,(LPCSTR)w_name))
            {
                pid = process.th32ProcessID;       
                //printf("%d\n", pid);
                break;
            }
    CloseHandle(snapshot);
    return pid;
}

void KillProcess(PROCESSENTRY32 & process)  //结束进程
{
    HANDLE hd=OpenProcess(PROCESS_TERMINATE, FALSE, process.th32ProcessID);
    TerminateProcess(hd,0);
}

void KillAll()                      //结束所有进程
{
    dispose_AllProcess(KillProcess);
}
