#include "include/twconsole.hpp"

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
