#include "data.h"

// 显示所有学生，每10条暂停，按学号升序
void disp_student(Student slist[], int scount) {
    sort_slist(slist, scount);
    const int PAGE_SIZE = 10;
    int totalPages = (scount + PAGE_SIZE - 1) / PAGE_SIZE;
    int currentPage = 0;

    int x1 = 5,  x2 = 17, x3 = 35, x4 = 43;//x1:第一格，..
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
        gotoxy(x3, row); printf("%s", slist[i].xb);
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

    int x1 = 5,  x2 = 17, x3 = 40;//x1:第一格，..
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
        gotoxy(x1, row); printf("%s", clist[i].kh);
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

    int x1 = 5,  x2 = 17, x3 = 35, x4 = 45;//x1:第一格，..
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
        gotoxy(x1, row); printf("%s", cjlist[i].xh);
        gotoxy(x2, row); printf("%s", cjlist[i].xm);
        gotoxy(x3, row); printf("%.2f", cjlist[i].zpj);
        gotoxy(x4, row); printf("%6.1f", cjlist[i].zxf);
    }
    
    gotoxy(x1, bottomRow);
    printChar('=', (x4 + 6) - x1);
    // 页码
    gotoxy(x1, infoRow);
    printf("共 %d 条  第 %d / %d 页", cjcount, currentPage + 1, totalPages);
    gotoxy(x4-11, infoRow);
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
            printChar(' ', (x4 + 6) - x1);
        }
        start = currentPage * PAGE_SIZE;
        end = (start + PAGE_SIZE) < cjcount ? (start + PAGE_SIZE) : cjcount;
        
        for (int i = start; i < end; i++) {
            int row = dataStartRow + (i - start);
            gotoxy(x1, row); printf("%s", cjlist[i].xh);
            gotoxy(x2, row); printf("%s", cjlist[i].xm);
            gotoxy(x3, row); printf("%.2f", cjlist[i].zpj);
            gotoxy(x4, row); printf("%6.1f", cjlist[i].zxf);
        }

        gotoxy(x1, infoRow);
        printChar(' ', (x4 + 4) - x1);
        gotoxy(x1, infoRow);
        printf("共 %d 条  第 %d / %d 页", cjcount, currentPage + 1, totalPages);
        gotoxy(x4-11, infoRow);
        printf("←→:翻页  Esc:退出");
    }
}