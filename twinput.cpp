#include "include/twinput.hpp"

void twinput::Click(int KEY)  //键盘按下KEY，再弹起来
{
    keybd_event(KEY, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);            //相当于 keybd_event(KEY,0,0,0);
    keybd_event(KEY, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); //相当于 keybd_event(KEY,0,2,0);
}  

void twinput::Set_Capital(int r)    //r=0 : 设置为小写  r=1 : 设置为大写
{
    if (GetKeyState(VK_CAPITAL) ^ r)   //大小写的目标状态与当前状态不同  如果CAPITAL键被按下即当前是大写，GetKeyState会返回1
        twinput::Click(VK_CAPITAL);
}

void Enter_Text(char * text,int delay)   //延时是毫秒
{
    static int map[256];
    memset(map,0,sizeof(map));
    map[' ']  = VK_SPACE;             //映射一波ASCII与键值不相等的字符
    map[',']  = VK_OEM_COMMA;
    map['/']  = VK_DIVIDE;
    map['.']  = VK_DECIMAL;
    map['-']  = VK_OEM_MINUS;
    map['*']  = VK_MULTIPLY;
    map['=']  = VK_OEM_PLUS;
    map['+']  = 0x6B;
    map['\n'] = VK_RETURN;
    map['\''] = 222;
    int capital_state=GetKeyState(VK_CAPITAL);  //记录大小写状态
    
    for( ; *text != '\0' ; text++,Sleep(delay))
    {
        if(map[*text]) twinput::Click(map[*text]);
        else
        {
            int offset = 0;          
            if(*text>='a' && *text<='z') {
                twinput::Set_Capital(0);
                offset=32;                      //如果是小写字母就减去32
            }
            else if(*text >= 'A' && *text <= 'Z') twinput::Set_Capital(1);
            twinput::Click((int)*text - offset);
        }
    }
    twinput::Set_Capital(capital_state);  //恢复原来的大小写状态
}


void twinput::Shortcuts(int keyargs, ...)
{
    va_list ap;
    int keylist[20];
    va_start(ap,keyargs);           //第一个参数是后续参数个数，即有几个键
                                    //注意va_start这里就已经读了第一个参数，之后调用va_arg就是第二个参数了
    for(int i=0; i<keyargs; i++)
    {
        keylist[i]=va_arg(ap,int);
        keybd_event(keylist[i], 0 ,KEYEVENTF_EXTENDEDKEY | 0, 0);           
    }    
    va_end(ap);
    for(int i=0; i<keyargs; i++,printf("%d\n",keylist[i]))
        keybd_event(keylist[i] ,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
}

void twinput::MouseClick(int c)   //0:左键  1:滚轮键  2:右键
{
    mouse_event(twinput::mousemap[c][0], 0, 0, 0, 0);
    mouse_event(twinput::mousemap[c][1], 0, 0, 0, 0);
}

void twinput::MouseMove(int dx, int dy)  //dx,dy:横纵方向控制, 0:该方向不移动，1:正向  -1:反向  （原点左上角）
{
    POINT p = { 0,0 };
    GetCursorPos(&p);
    SetCursorPos(p.x + dx, p.y + dy);
}

void twinput::GetMousePos(int* x, int* y) //获取鼠标指针x,y坐标
{
    POINT p = { 0,0 };
    GetCursorPos(&p);
    *x = p.x;
    *y = p.y;
} 
