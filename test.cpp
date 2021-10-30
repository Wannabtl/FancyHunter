#include<bits/stdc++.h>
#include<windows.h>
#define pc putchar
#define gc getchar
using namespace std;
int main(){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = true ; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
    
    COORD coord={0,0};
    for(int i=1;i<=10;i++)
    for(int j=1;j<=10;j++){
        pc('*');
        if(j==10) pc('\n');
    }
    coord={0,0};
    SetConsoleCursorPosition(handle, coord);
    pc('P');
    for(int i=1;i<=10;i++){
        coord.X=coord.Y=i;
        SetConsoleCursorPosition(handle, coord);
        pc('X');
    }
    
    coord.X=coord.Y=0;
    //short sx=5+P1.x*2-1,sy=P1.y*4-1-1;
    //coord={sx,sy};
    SetConsoleCursorPosition(handle, coord);
    puts("sdfasfasdf");
    char c=gc();
    return 0;
}

/*
P
 X
  X
   X
    X
     X
      X
       X
        X
         X
          X
*/