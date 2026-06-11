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
    char title[] = "请输入学生数据（优先查询学号）";
    int xPos[] = {5, 20, 30};
    drawTable(xPos, 3, title);
}

void drawTableFrameCourseQuery(){
    char title[] = "请输入课程数据（优先查询课号）";
    int xPos[] = {5, 16, 37};
    drawTable(xPos, 3, title);
    
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
    printChar('=', (dx3 + 5) - dx1);
    gotoxy(dx1, detailRow + 2); printf("课号");
    gotoxy(dx2, detailRow + 2); printf("课程名");
    gotoxy(dx3, detailRow + 2); printf("成绩");

    gotoxy(dx1, detailRow + 3);
    printChar('-', (dx3 + 5) - dx1);


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
    printChar('=', (dx3 + 5) - dx1);

}

// 基本信息和细则表格
void drawSelectDetail(Score cjlist[], int index, Course clist[], int ccount, Select sclist[], int sccount, int detailItems[], int detailCount, int selected, int marked[]) {
    int x1 = 5,  x2 = 17, x3 = 35, x4 = 45;
    int dx1 = 5, dx2 = 17, dx3 = 40;
    int tableStartRow = 2;
    int dataStartRow = tableStartRow + 2;
    int bottomRow = dataStartRow + 1;
    int detailRow = bottomRow + 2;

    system("cls");

    gotoxy(x1, tableStartRow - 2); printf("查询到成绩如下：");
    gotoxy(x1, tableStartRow - 1); printChar('=', (x4 + 6) - x1);
    gotoxy(x1, tableStartRow); printf("学号");
    gotoxy(x2, tableStartRow); printf("姓名");
    gotoxy(x3, tableStartRow); printf("平均分");
    gotoxy(x4, tableStartRow); printf("总学分");
    gotoxy(x1, tableStartRow + 1); printChar('-', (x4 + 6) - x1);
    gotoxy(x1, dataStartRow); printf("%s", cjlist[index].xh);
    gotoxy(x2, dataStartRow); printf("%s", cjlist[index].xm);
    gotoxy(x3, dataStartRow); printf("%.2f", cjlist[index].zpj);
    gotoxy(x4, dataStartRow); printf("%6.1f", cjlist[index].zxf);
    gotoxy(x1, bottomRow);    printChar('=', (x4 + 6) - x1);

    gotoxy(dx1, detailRow); printf("各科成绩细则");
    gotoxy(dx1, detailRow + 1); printChar('=', (dx3 + 5) - dx1);
    gotoxy(dx1, detailRow + 2); printf("课号");
    gotoxy(dx2, detailRow + 2); printf("课程名");
    gotoxy(dx3, detailRow + 2); printf("成绩");
    gotoxy(dx1, detailRow + 3); printChar('-', (dx3 + 5) - dx1);

    for (int k = 0; k < detailCount; k++) {
        int sclistIdx = detailItems[k];
        int row = detailRow + 4 + k;

        int isHigh = (k == selected);
        int isMark = marked[k];
        if (isHigh && isMark) setcolor(6, 0);      // 红底黄字
        else if (isHigh)      setcolor(7, 0);       // 白底黑字
        else if (isMark)      setcolor(4, 14);       // 黄底黑字
        else                  setcolor(0, 7);
        gotoxy(dx1, row); printChar(' ', (dx3 + 5) - dx1);
        gotoxy(dx1, row); printf("%s", sclist[sclistIdx].kh);
        gotoxy(dx2, row); printf("%s", clist[queryCrsExistByID(clist, ccount, sclist[sclistIdx].kh)].km);
        gotoxy(dx3, row); 
        if (sclist[sclistIdx].cj == -1) printf("暂无");
        else printf("%.1f", sclist[sclistIdx].cj);
    }

    setcolor(0, 7);
    gotoxy(dx1, detailRow + 4 + detailCount);
    printChar('=', (dx3 + 5) - dx1);

    gotoxy(dx1, detailRow + 5 + detailCount);
    printf("↑↓:选择  Space/Del:标记  Enter:删除  Esc:退出");
}

void drawDetailRow(Score cjlist[], int index, Course clist[], int ccount, Select sclist[], int sclistIdx, int dx1, int dx2, int dx3, int row, int isHigh, int isMark) {
    gotoxy(dx1, row);
    if (isHigh && isMark) setcolor(6, 0);      // 红底黄字
    else if (isHigh)      setcolor(7, 0);       // 白底黑字
    else if (isMark)      setcolor(4, 14);       // 黄底黑字
    else                  setcolor(0, 7);
    gotoxy(dx1, row); printChar(' ', (dx3 + 5) - dx1);
    gotoxy(dx1, row);
    printf("%s", sclist[sclistIdx].kh);
    gotoxy(dx2, row);
    printf("%s",clist[queryCrsExistByID(clist, ccount, sclist[sclistIdx].kh)].km);
    gotoxy(dx3, row);
    if (sclist[sclistIdx].cj == -1) printf("暂无");
    else printf("%.1f", sclist[sclistIdx].cj);
    setcolor(0, 7);
    gotoxy(0, 0);
}

void clearRow(int x, int y, int width) {
    gotoxy(x, y);
    for (int i = 0; i < width + 6; i++) putchar(' ');
}

void displayDeleteSelect(Score cjlist[], int index, Course clist[], int ccount, Student slist[], int scount, Select sclist[], int *sccount) {
    int dx1 = 5, dx2 = 17, dx3 = 40;
    int dataBeginRow = 11;

    // 选课记录索引
    int detailItems[SELECT_MAX];
    int detailCount = 0;
    char* studentXh = cjlist[index].xh;
    for (int i = 0; i < *sccount; i++) {
        if (strcmp(sclist[i].xh, studentXh) == 0) {
            detailItems[detailCount++] = i;
        }
    }

    if (detailCount == 0) {
        system("cls");
        gotoxy(5, 5); printf("该学生没有选课记录！");
        _getch();
        return;
    }

    int selected = 0;
    int marked[SELECT_MAX] = {0};

    drawSelectDetail(cjlist, index, clist, ccount, sclist, *sccount, detailItems, detailCount, selected, marked);
    drawDetailRow(cjlist, index, clist, ccount, sclist, detailItems[selected], dx1, dx2, dx3, dataBeginRow + selected, 1, marked[selected]);

    while (1) {
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            int key = _getch();
            if (key == 72 && detailCount > 0) {  // 上
                int prev = selected;
                selected = (selected - 1 + detailCount) % detailCount;
                // 重绘旧行和新行
                drawDetailRow(cjlist, index, clist, ccount, sclist, detailItems[prev], dx1, dx2, dx3, dataBeginRow + prev, 0, marked[prev]);
                drawDetailRow(cjlist, index, clist, ccount, sclist, detailItems[selected], dx1, dx2, dx3, dataBeginRow + selected, 1, marked[selected]);
            } else if (key == 80 && detailCount > 0) { // 下
                int prev = selected;
                selected = (selected + 1) % detailCount;
                drawDetailRow(cjlist, index, clist, ccount, sclist, detailItems[prev], dx1, dx2, dx3, dataBeginRow + prev, 0, marked[prev]);
                drawDetailRow(cjlist, index, clist, ccount, sclist, detailItems[selected], dx1, dx2, dx3, dataBeginRow + selected, 1, marked[selected]);
            } else if (key == 83 && detailCount > 0) { // Del
                marked[selected] = !marked[selected];
                drawDetailRow(cjlist, index, clist, ccount, sclist, detailItems[selected], dx1, dx2, dx3, dataBeginRow + selected, 1, marked[selected]);
            }
        } else if (ch == 32 && detailCount > 0) { // 空格
            marked[selected] = !marked[selected];
            drawDetailRow(cjlist, index, clist, ccount, sclist, detailItems[selected], dx1, dx2, dx3, dataBeginRow + selected, 1, marked[selected]);
        } else if (ch == 13) { // 回车
            // 收集待删索引
            int toDelete[SELECT_MAX], delCount = 0;
            for (int k = 0; k < detailCount; k++) {
                if (marked[k]) toDelete[delCount++] = detailItems[k];
            }
            if (delCount == 0) continue;

            // 降序排序
            for (int i = 0; i < delCount - 1; i++)
                for (int j = i + 1; j < delCount; j++)
                    if (toDelete[i] < toDelete[j]) {
                        int tmp = toDelete[i];
                        toDelete[i] = toDelete[j];
                        toDelete[j] = tmp;
                    }

            // 执行删除
            for (int i = 0; i < delCount; i++) {
                int pos = toDelete[i];
                for (int j = pos; j < *sccount - 1; j++)
                    sclist[j] = sclist[j + 1];
                (*sccount)--;
            }
            return;
        } else if (ch == 27) {
            break;
        }
    }
}