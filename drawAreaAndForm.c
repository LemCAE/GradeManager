#include "data.h"

// 输入框绘制
void drawField(inputField *f, int active){//绘制输入区
    int titleY=4, inputY=6;

    gotoxy(f->x, titleY);//画标题
    if(active){setcolor(7,0);}
    else{setcolor(0,7);}
    printf("%s", f->title);

    setcolor(0,7);
    gotoxy(f->x, inputY);//画输入框
    for(int i=0; i<f->width; i++){
        printf(" ");
    }

    gotoxy(f->x, inputY);
    printf("%s", f->buffer);//先清空输入框，然后打印缓冲区里面的内容
}

int inputForm(inputField fields[], int count, void (*drawFrame)(void)){
    int active=0;

    for (int i=0; i<count; i++){//初始化缓冲区和位置
        fields[i].buffer[0] = '\0';
        fields[i].pos = 0;
    }

    drawFrame();//调用函数，绘制外边框

    for (int i=0; i<count; i++){//画输入区
        drawField(&fields[i], i==active);
    }
    setcolor(0,7);

    while (1){//这里开始读取输入，也许可以加一个按Tab的功能
        inputField *cur = &fields[active];
        gotoxy(cur->x + utf8DisplayWidth(cur->buffer), 6);//输入位置
        int ch = _getch();

        if (ch == 0 || ch == 224){
            int key = _getch();
            if (key == 75){//左
                if (active > 0){
                    drawField(&fields[active], 0);
                    active--;
                    drawField(&fields[active], 1);
                }
            } else if (key == 77){//右
                if (active < count-1){
                    drawField(&fields[active], 0);
                    active++;
                    drawField(&fields[active], 1);
                }
            }
        } else if (ch == '\r'){
            return 1;
        } else if (ch == 27){
            return 0;
        } else if (ch == '\b'){
            if (cur->pos > 0){
            // 找到最后一个 UTF-8 字符的起始位置
            int p = cur->pos - 1;
            while (p > 0 && (cur->buffer[p] & 0xC0) == 0x80) p--;  // 跳过后续字节
            int delCharWidth = utf8DisplayWidth(cur->buffer + p); // 待删字符的宽度

            // 擦除屏幕上该字符占据的格数
            int currentTotalWidth = utf8DisplayWidth(cur->buffer);
            gotoxy(cur->x + currentTotalWidth - delCharWidth, 6);
            for (int i = 0; i < delCharWidth; i++) putchar(' ');

            // 更新 buffer
            cur->buffer[p] = '\0';
            cur->pos = p;
            }
        } else if ((ch >=32 && ch <= 126) || (ch &0x80)){
            char utf8_char[5] = {0};
            int len = utf8CharLen((unsigned char)ch);
            utf8_char[0] = ch;
            for (int i = 1; i < len; i++) {
                utf8_char[i] = _getch();
            }
            utf8_char[len] = '\0';

            // 计算新字符的显示宽度
            int char_width = utf8DisplayWidth(utf8_char);
            int current_width = utf8DisplayWidth(cur->buffer);
            int new_width = current_width + char_width;

            // 检查是否超出字段宽度
            if (new_width <= cur->width && cur->pos + len < (int)sizeof(cur->buffer)) {
                strcat(cur->buffer, utf8_char);
                cur->pos += len;
                printf("%s", utf8_char);
            }
        }
        setcolor(0,7);
    }
}