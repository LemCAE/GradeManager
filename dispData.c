#include "data.h"

void dispDetail(Score cjlist[], int cjcount, Course clist[], int ccount, int currentPage, int currentLine);

// 显示所有学生，每10条暂停，按学号升序
void disp_student(Student slist[], int scount) {
    sort_slist(slist, scount);
    const int PAGE_SIZE = 10;
    int totalPages = (scount + PAGE_SIZE - 1) / PAGE_SIZE;
    int currentPage = 0;

    int x1 = 5,  x2 = 17, x3 = 39, x4 = 47;//x1:第一格，..
    int tableStartRow = 2;                  // 表头
    int dataStartRow = tableStartRow + 2;   // 数据第一行
    int dataHeight = PAGE_SIZE;             // 数据区高度
    int bottomRow = dataStartRow + dataHeight; // 底线
    int infoRow = bottomRow + 1;            // 页码

    system("cls");

    gotoxy(x1, tableStartRow -2);
    printf("学生信息表");
    gotoxy(x1, tableStartRow -1);
    printChar('=', (x4 + 4) - x1);

    gotoxy(x1, tableStartRow); printf("学号");
    gotoxy(x2, tableStartRow); printf("姓名");
    gotoxy(x3, tableStartRow); printf("性别");
    gotoxy(x4, tableStartRow); printf("年龄");
    
    gotoxy(x1, tableStartRow + 1);
    printChar('-', (x4 + 4) - x1);

    // 数据
    int start = currentPage * PAGE_SIZE;
    int end = (start + PAGE_SIZE) < scount ? (start + PAGE_SIZE) : scount;
    for (int i = start; i < end; i++) {
        int row = dataStartRow + (i - start);
        gotoxy(x1, row); printf("%s", slist[i].xh);
        gotoxy(x2, row); printf("%s", slist[i].xm);
        gotoxy(x3 + 1, row); printf("%s", slist[i].xb);//这种只有一个字的（或者长度确定的）就居中吧
        gotoxy(x4, row); printf("%3d", slist[i].nl);
    }
    
    gotoxy(x1, bottomRow);
    printChar('=', (x4 + 4) - x1);
    // 页码
    gotoxy(x1, infoRow);
    printf("共 %d 条  第 %d / %d 页", scount, currentPage + 1, totalPages);
    gotoxy(x4-13, infoRow);
    printf("←→:翻页  Esc:退出");

    while (1) {
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            int key = _getch();
            if (key == 75) currentPage = (currentPage - 1 + totalPages) % totalPages;
            if (key == 77) currentPage = (currentPage + 1) % totalPages;
        } else if (ch == 27) break;
        else continue;

        for (int r = 0; r < dataHeight; r++) {
            gotoxy(x1, dataStartRow + r);
            printChar(' ', (x4 + 4) - x1);
        }
        start = currentPage * PAGE_SIZE;
        end = (start + PAGE_SIZE) < scount ? (start + PAGE_SIZE) : scount;//如果start + PAGE_SIZE小于scount，即当前已经是最后一页了，就把end设置为scount
        
        for (int i = start; i < end; i++) {
            int row = dataStartRow + (i - start);
            gotoxy(x1, row); printf("%s", slist[i].xh);
            gotoxy(x2, row); printf("%s", slist[i].xm);
            gotoxy(x3, row); printf("%s", slist[i].xb);
            gotoxy(x4, row); printf("%3d", slist[i].nl);
        }

        gotoxy(x1, infoRow);
        printChar(' ', (x4 + 4) - x1);
        gotoxy(x1, infoRow);
        printf("共 %d 条  第 %d / %d 页", scount, currentPage + 1, totalPages);
        gotoxy(x4-13, infoRow);
        printf("←→:翻页  Esc:退出");
    }
}

// 显示所有课程，每10条暂停，按课号升序
void disp_course(Course clist[], int ccount){
    sort_clist(clist, ccount);
    const int PAGE_SIZE = 10;
    int totalPages = (ccount + PAGE_SIZE - 1) / PAGE_SIZE;
    int currentPage = 0;

    int x1 = 5,  x2 = 17, x3 = 43;//x1:第一格，..
    int tableStartRow = 2;                  // 表头
    int dataStartRow = tableStartRow + 2;   // 数据第一行
    int dataHeight = PAGE_SIZE;             // 数据区高度
    int bottomRow = dataStartRow + dataHeight; // 底线
    int infoRow = bottomRow + 1;            // 页码

    system("cls");

    gotoxy(x1, tableStartRow -2);
    printf("课程信息表");
    gotoxy(x1, tableStartRow -1);
    printChar('=', (x3 + 4) - x1);

    gotoxy(x1, tableStartRow); printf("课号");
    gotoxy(x2, tableStartRow); printf("课程名");
    gotoxy(x3, tableStartRow); printf("学分");
    
    gotoxy(x1, tableStartRow + 1);
    printChar('-', (x3 + 4) - x1);

    // 数据
    int start = currentPage * PAGE_SIZE;
    int end = (start + PAGE_SIZE) < ccount ? (start + PAGE_SIZE) : ccount;
    for (int i = start; i < end; i++) {
        int row = dataStartRow + (i - start);
        gotoxy(x1 + 1, row); printf("%s", clist[i].kh);
        gotoxy(x2, row); printf("%s", clist[i].km);
        gotoxy(x3, row); printf("%4.1f", clist[i].xf);
    }
    
    gotoxy(x1, bottomRow);
    printChar('=', (x3 + 4) - x1);
    // 页码
    gotoxy(x1, infoRow);
    printf("共 %d 条  第 %d / %d 页", ccount, currentPage + 1, totalPages);
    gotoxy(x3-13, infoRow);
    printf("←→:翻页  Esc:退出");

    
    while (1) {
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            int key = _getch();
            if (key == 75) currentPage = (currentPage - 1 + totalPages) % totalPages;
            if (key == 77) currentPage = (currentPage + 1) % totalPages;
        } else if (ch == 27) break;
        else continue;

        for (int r = 0; r < dataHeight; r++) {
            gotoxy(x1, dataStartRow + r);
            printChar(' ', (x3 + 4) - x1);
        }
        start = currentPage * PAGE_SIZE;
        end = (start + PAGE_SIZE) < ccount ? (start + PAGE_SIZE) : ccount;
        
        for (int i = start; i < end; i++) {
            int row = dataStartRow + (i - start);
            gotoxy(x1, row); printf("%s", clist[i].kh);
            gotoxy(x2, row); printf("%s", clist[i].km);
            gotoxy(x3, row); printf("%4.1f", clist[i].xf);
        }

        gotoxy(x1, infoRow);
        printChar(' ', (x3 + 4) - x1);
        gotoxy(x1, infoRow);
        printf("共 %d 条  第 %d / %d 页", ccount, currentPage + 1, totalPages);
        gotoxy(x3-13, infoRow);
        printf("←→:翻页  Esc:退出");
    }

}

// 显示成绩单，每10行暂停，按平均分降序
void disp_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount) {
    sort_cjlist(cjlist, cjcount);
    const int PAGE_SIZE = 10;
    int totalPages = (cjcount + PAGE_SIZE - 1) / PAGE_SIZE;
    int currentPage = 0;
    int currentLine = 0;

    int x1 = 5,  x2 = 17, x3 = 40, x4 = 48;//x1:第一格，..
    int tableStartRow = 2;                  // 表头
    int dataStartRow = tableStartRow + 2;   // 数据第一行
    int dataHeight = PAGE_SIZE;             // 数据区高度
    int bottomRow = dataStartRow + dataHeight; // 底线
    int infoRow = bottomRow + 1;            // 页码

    system("cls");

    gotoxy(x1, tableStartRow -2);
    printf("学生成绩单");
    gotoxy(x1, tableStartRow -1);
    printChar('=', (x4 + 6) - x1);

    gotoxy(x1, tableStartRow); printf("学号");
    gotoxy(x2, tableStartRow); printf("姓名");
    gotoxy(x3, tableStartRow); printf("平均分");
    gotoxy(x4, tableStartRow); printf("总学分");
    
    gotoxy(x1, tableStartRow + 1);
    printChar('-', (x4 + 6) - x1);

    // 数据
    int start = currentPage * PAGE_SIZE;
    int end = (start + PAGE_SIZE) < cjcount ? (start + PAGE_SIZE) : cjcount;
    for (int i = start; i < end; i++) {
        int row = dataStartRow + (i - start);
        if (i == start + currentLine){
            setcolor(7, 0);
            gotoxy(x1, row); printChar(' ', (x4 + 6) - x1);
        }
        gotoxy(x1, row); printf("%s", cjlist[i].xh);
        gotoxy(x2, row); printf("%s", cjlist[i].xm);
        gotoxy(x3, row); printf("%6.2f", cjlist[i].zpj);
        gotoxy(x4, row); printf("%6.1f", cjlist[i].zxf);
        setcolor(0, 7);
    }

    gotoxy(x1, bottomRow);
    printChar('=', (x4 + 6) - x1);
    // 页码
    gotoxy(x1, infoRow);
    printf("共 %d 条 第 %d/%d 页", cjcount, currentPage + 1, totalPages);
    gotoxy(x4-22, infoRow);
    printf("←→:翻页 ↑↓:选择 Esc:退出");

    dispDetail(cjlist, cjcount, clist, ccount, currentPage, currentLine);

    while (1) {
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            int key = _getch();
            if (key == 75) {
                currentPage = (currentPage - 1 + totalPages) % totalPages;
                currentLine = 0;
            }
            if (key == 77) {
                currentPage = (currentPage + 1) % totalPages;
                currentLine = 0;
            }
            if (key == 80 || key == 72){
                int itemsOnPage = PAGE_SIZE < (cjcount - PAGE_SIZE * currentPage) ? PAGE_SIZE : (cjcount - PAGE_SIZE * currentPage);
                if (itemsOnPage <= 0) continue;
                if (key == 80){
                    currentLine = (currentLine + 1) % itemsOnPage;
                }
                else{
                    currentLine = (currentLine - 1 + itemsOnPage) % itemsOnPage;
                }
            }
        } else if (ch == 27) break;
        else continue;

        for (int r = 0; r < dataHeight; r++) {
            gotoxy(x1, dataStartRow + r);
            if (r == currentLine) setcolor(7, 0);
            printChar(' ', (x4 + 6) - x1);
            setcolor(0, 7);
        }
        start = currentPage * PAGE_SIZE;
        end = (start + PAGE_SIZE) < cjcount ? (start + PAGE_SIZE) : cjcount;
        
        for (int i = start; i < end; i++) {
            if (i == start + currentLine) setcolor(7, 0);
            int row = dataStartRow + (i - start);
            gotoxy(x1, row); printf("%s", cjlist[i].xh);
            gotoxy(x2, row); printf("%s", cjlist[i].xm);
            gotoxy(x3, row); printf("%6.2f", cjlist[i].zpj);
            gotoxy(x4, row); printf("%6.1f", cjlist[i].zxf);
            setcolor(0, 7);
        }

        gotoxy(x1, infoRow);
        printChar(' ', (x4 + 4) - x1);
        gotoxy(x1, infoRow);
        printf("共 %d 条 第 %d/%d 页", cjcount, currentPage + 1, totalPages);
        gotoxy(x4-22, infoRow);
        printf("←→:翻页 ↑↓:选择 Esc:退出");

        dispDetail(cjlist, cjcount, clist, ccount, currentPage, currentLine);
    }
}

void dispDetail(Score cjlist[], int cjcount, Course clist[], int ccount, int currentPage, int currentLine) {

    int dx1 = 57, dx2 = 69, dx3 = 94, dx4 = 100;
    int detailRow = 0;
    const int PAGE_SIZE = 10;
    int index = currentPage * PAGE_SIZE + currentLine;
    int count = 0;

    gotoxy(dx1, detailRow); printf("各科成绩细则");
    gotoxy(dx1, detailRow + 1); printChar('=', (dx4 + 4) - dx1);
    gotoxy(dx1, detailRow + 2); printf("课号");
    gotoxy(dx2, detailRow + 2); printf("课程名");
    gotoxy(dx3, detailRow + 2); printf(" 成绩");
    gotoxy(dx4, detailRow + 2); printf("学分");
    gotoxy(dx1, detailRow + 3); printChar('-', (dx4 + 4) - dx1);

    for (int i = 0 ; i<ccount; i++){
        gotoxy(dx1, detailRow + 4 + count); printChar(' ', (dx4 + 4) - dx1);
        if (cjlist[index].cj[i] != -1 && cjlist[index].cj[i] != -2) {
            gotoxy(dx1, detailRow + 4 + count); printf("%s", clist[i].kh);
            gotoxy(dx2, detailRow + 4 + count); printf("%s", clist[i].km);
            gotoxy(dx3, detailRow + 4 + count); printf("%5.1f", cjlist[index].cj[i]);
            gotoxy(dx4, detailRow + 4 + count); printf("%4.1f", clist[i].xf);
            count++;
        } else if (cjlist[index].cj[i] == -1) {
            gotoxy(dx1, detailRow + 4 + count); printf("%s", clist[i].kh);
            gotoxy(dx2, detailRow + 4 + count); printf("%s", clist[i].km);
            gotoxy(dx3, detailRow + 4 + count); printf(" 暂无");
            gotoxy(dx4, detailRow + 4 + count); printf("%4.1f", clist[i].xf);
            count++;
        }
    }

    for (int r = count; r < ccount; r++) {
        gotoxy(dx1, detailRow + 4 + r);
        printChar(' ', (dx4 + 4) - dx1);
    }

    setcolor(0, 7);
    gotoxy(dx1, detailRow + 4 + count);
    printChar('=', (dx4 + 4) - dx1);

}