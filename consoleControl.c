#include "data.h"

void gotoxy(int x, int y){
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcolor(int bg, int fg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bg << 4) | fg);
}

void printChar(char c, int number){
    for(int i = 0; i < number; i++){
        printf("%c", c);
    }
}

void clearInputBuffer() {//清空缓冲区
    while (getchar() != '\n');
}