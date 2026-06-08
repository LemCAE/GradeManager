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

//////输入框

void drawTableFrameStudentQuery(){
    gotoxy(5,2);
    printf("请输入学生数据（优先查询学号）");

    gotoxy(5,3);
    printChar('=', 26);

    // 标题行竖线
    gotoxy(5,4);printf("|");
    gotoxy(20,4);printf("|");
    gotoxy(30,4);printf("|");

    // 分隔线
    gotoxy(5,5);
    printChar('-', 26);

    // 输入行竖线
    gotoxy(5,6);printf("|");
    gotoxy(20,6);printf("|");
    gotoxy(30,6);printf("|");

    // 底线
    gotoxy(5,7);
    printChar('=', 26);
}

void drawTableFrameCourseQuery(){
    
    gotoxy(5, 2);
    printf("请输入课程数据（优先查询课号）");

    gotoxy(5, 3);
    printChar('=', 33);

    gotoxy(5, 4);  putchar('|');
    gotoxy(16, 4); putchar('|');
    gotoxy(37, 4); putchar('|');

    gotoxy(5, 5);
    printChar('-', 33);

    gotoxy(5, 6);  putchar('|');
    gotoxy(16, 6); putchar('|');
    gotoxy(37, 6); putchar('|');

    gotoxy(5, 7);
    printChar('=', 33);
    
}

void displayStudent(Student slist[], int index){
    system("cls");

    int x1 = 5,  x2 = 17, x3 = 35, x4 = 43;
    int tableStartRow = 2;
    int dataStartRow = tableStartRow + 2;
    int bottomRow = dataStartRow + 1;

    gotoxy(5,0);
    printf("查询到学生如下：");
    gotoxy(x1, tableStartRow -1);
    printChar('=', (x4 + 4) - x1);

    gotoxy(x1, tableStartRow); printf("学号");
    gotoxy(x2, tableStartRow); printf("姓名");
    gotoxy(x3, tableStartRow); printf("性别");
    gotoxy(x4, tableStartRow); printf("年龄");
    
    gotoxy(x1, tableStartRow + 1);
    printChar('-', (x4 + 4) - x1);

    gotoxy(x1, dataStartRow); printf("%s", slist[index].xh);
    gotoxy(x2, dataStartRow); printf("%s", slist[index].xm);
    gotoxy(x3, dataStartRow); printf("%s", slist[index].xb);
    gotoxy(x4, dataStartRow); printf("%3d", slist[index].nl);

    gotoxy(x1, bottomRow);
    printChar('=', (x4 + 4) - x1);

}

void displayCourse(Course clist[], int index){
    int x1 = 5,  x2 = 17, x3 = 40;
    int tableStartRow = 2;
    int dataStartRow = tableStartRow + 2;
    int bottomRow = dataStartRow + 1;

    system("cls");

    gotoxy(x1, tableStartRow -2);
    printf("查询到课程如下：");
    gotoxy(x1, tableStartRow -1);
    printChar('=', (x3 + 4) - x1);

    gotoxy(x1, tableStartRow); printf("课号");
    gotoxy(x2, tableStartRow); printf("课程名");
    gotoxy(x3, tableStartRow); printf("学分");
    
    gotoxy(x1, tableStartRow + 1);
    printChar('-', (x3 + 4) - x1);

    gotoxy(x1, dataStartRow); printf("%s", clist[index].kh);
    gotoxy(x2, dataStartRow); printf("%s", clist[index].km);
    gotoxy(x3, dataStartRow); printf("%4.1f", clist[index].xf);
    
    gotoxy(x1, bottomRow);
    printChar('=', (x3 + 4) - x1);
}

void displayScore(Score cjlist[], int index, Course clist[], int ccount, Student slist[], int scount, Select sclist[], int sccount){
    int x1 = 5,  x2 = 17, x3 = 35, x4 = 45;
    int tableStartRow = 2;
    int dataStartRow = tableStartRow + 2;
    int bottomRow = dataStartRow + 1;
    int detailRow = bottomRow + 2;

    system("cls");

    gotoxy(x1, tableStartRow -2);
    printf("查询到成绩如下：");
    gotoxy(x1, tableStartRow -1);
    printChar('=', (x4 + 6) - x1);

    gotoxy(x1, tableStartRow); printf("学号");
    gotoxy(x2, tableStartRow); printf("姓名");
    gotoxy(x3, tableStartRow); printf("平均分");
    gotoxy(x4, tableStartRow); printf("总学分");

    gotoxy(x1, tableStartRow + 1);
    printChar('-', (x4 + 6) - x1);

    gotoxy(x1, dataStartRow); printf("%s", cjlist[index].xh);
    gotoxy(x2, dataStartRow); printf("%s", cjlist[index].xm);
    gotoxy(x3, dataStartRow); printf("%.2f", cjlist[index].zpj);
    gotoxy(x4, dataStartRow); printf("%6.1f", cjlist[index].zxf);   
    
    gotoxy(x1, bottomRow);
    printChar('=', (x4 + 6) - x1);

    int dx1 = 5,  dx2 = 17, dx3 = 40;
    int detailCount = 0;

    gotoxy(dx1, detailRow);
    printf("各科成绩细则");
    gotoxy(dx1, detailRow + 1);
    printChar('=', (dx3 + 4) - dx1);
    gotoxy(dx1, detailRow + 2); printf("课号");
    gotoxy(dx2, detailRow + 2); printf("课程名");
    gotoxy(dx3, detailRow + 2); printf("成绩");

    gotoxy(dx1, detailRow + 3);
    printChar('-', (dx3 + 4) - dx1);


    for(int i = 0; i < ccount; i++){
        gotoxy(dx1, detailRow + 4 + detailCount);
        if ((cjlist[index].cj[i] != -1) && (cjlist[index].cj[i] != -2)){
            gotoxy(dx1, detailRow + 4 + detailCount); printf("%s", clist[i].kh);
            gotoxy(dx2, detailRow + 4 + detailCount); printf("%s", clist[i].km);
            gotoxy(dx3, detailRow + 4 + detailCount); printf("%.1f", cjlist[index].cj[i]);
            detailCount++;
        } else if (cjlist[index].cj[i] == -1){
            gotoxy(dx1, detailRow + 4 + detailCount); printf("%s", clist[i].kh);
            gotoxy(dx2, detailRow + 4 + detailCount); printf("%s", clist[i].km);
            gotoxy(dx3, detailRow + 4 + detailCount); printf("暂无");
            detailCount++;
        }
        
    }

    gotoxy(dx1, detailRow + 4 + detailCount);
    printChar('=', (dx3 + 4) - dx1);

}