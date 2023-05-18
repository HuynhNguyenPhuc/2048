#include "graphic.h"

void gotoXY(int x, int y){
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { short(x), short(y) };  
    SetConsoleCursorPosition(h,c);
}

void setCursor(bool visible, DWORD size){
    if (size == 0) size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
}