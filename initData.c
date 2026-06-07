#include "data.h"

void drawTableFrameFile();

void init(Student slist[], int *scount, Course clist[], int *ccount, Select sclist[], int *sccount){
    *scount = 0;
    *ccount = 0;
    *sccount = 0;

    char studentFileName[30], courseFileName[30], selectFileName[30];

    system("cls");

    gotoxy(5,8);
    printf("←→切换输入项，回车确认，ESC退出");

    inputField selectFields[] = {
        {"学生文件", "", 0, 6, 30},
        {"课程文件", "", 0, 37, 30},
        {"选课文件", "", 0, 68, 30}
    };

    int result = inputForm(selectFields, 3, drawTableFrameFile);

    if(!result){
        initDefault(slist, scount, clist, ccount, sclist, sccount);
        return;
    }

    if(!emptyExist(selectFields, 3)){
        gotoxy(5,10);
        printf("信息输入不完整，使用默认数据");
        _getch();
        initDefault(slist, scount, clist, ccount, sclist, sccount);
        return;
    }

    gotoxy(5,10);

    strcpy(studentFileName, selectFields[0].buffer);
    strcpy(courseFileName, selectFields[1].buffer);
    strcpy(selectFileName, selectFields[2].buffer);

    //尝试打开全部三个文件（全有或全无）
    FILE *studentFile = fopen(studentFileName, "r");
    FILE *courseFile = fopen(courseFileName, "r");
    FILE *selectFile = fopen(selectFileName, "r");

    if (!studentFile || !courseFile || !selectFile){
        gotoxy(5,10);
        printf("文件打开失败：\n");
        gotoxy(5,11);
        if (!studentFile) printf("  - %s\n", studentFileName);
        gotoxy(5,12);
        if (!courseFile) printf("  - %s\n", courseFileName);
        gotoxy(5,13);
        if (!selectFile) printf("  - %s\n", selectFileName);
        gotoxy(5,14);
        printf("使用默认数据\n");
        _getch();
        system("cls");

        if (studentFile) fclose(studentFile);
        if (courseFile) fclose(courseFile);
        if (selectFile) fclose(selectFile);

        initDefault(slist, scount, clist, ccount, sclist, sccount);
        return;
    }

    //三个文件都成功打开，读取数据
    while(fscanf(studentFile,"%9s %19s %3s %d",
            slist[*scount].xh,
            slist[*scount].xm,
            slist[*scount].xb,
            &slist[*scount].nl) == 4)
    {
        (*scount)++;
    }

    while(fscanf(courseFile,"%9s %24s %f",
            clist[*ccount].kh,
            clist[*ccount].km,
            &clist[*ccount].xf
        ) == 3)
    {
        (*ccount)++;
    }

    while(fscanf(selectFile,"%9s %9s %f",
            sclist[*sccount].xh,
            sclist[*sccount].kh,
            &sclist[*sccount].cj) == 3)
    {
        (*sccount)++;
    }

    system("cls");

    fclose(studentFile);
    fclose(courseFile);
    fclose(selectFile);

    // printStudents(slist, *scount);
    // printCourses(clist, *ccount);
    // printSelects(sclist, *sccount);
    gotoxy(5,2);
    printf("数据读取完成\n");
    gotoxy(5,3);
    _getch();
}

void drawTableFrameFile() {
    gotoxy(5, 2);
    printf("请输入文件名：");

    int left = 5, col1 = 36, col2 = 67, right = 98;
    int totalWidth = right - left;   // 91

    // 顶线
    gotoxy(left, 3);
    for (int i = 0; i < totalWidth+1; i++) putchar('=');

    // 标题行竖线
    gotoxy(left, 4);  putchar('|');
    gotoxy(col1, 4);  putchar('|');
    gotoxy(col2, 4);  putchar('|');
    gotoxy(right, 4); putchar('|');

    // 分隔线
    gotoxy(left, 5);
    for (int i = 0; i < totalWidth+1; i++) putchar('-');

    // 输入行竖线
    gotoxy(left, 6);  putchar('|');
    gotoxy(col1, 6);  putchar('|');
    gotoxy(col2, 6);  putchar('|');
    gotoxy(right, 6); putchar('|');

    // 底线
    gotoxy(left, 7);
    for (int i = 0; i < totalWidth+1; i++) putchar('=');
}