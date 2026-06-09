#include "data.h"

void drawTableFrameStudent();
void drawTableFrameCourse();
void drawTableFrameSelect();
void drawTable(int xPos[], int count, char title[]);

//主输入函数

int input_std(Student slist[], int scount){
    int ifContinue = 1;
    int status = 0;
    while(ifContinue){
        system("cls");

        gotoxy(5,8);
        printf("←→切换输入项，回车确认，ESC退出");

        inputField fields[] = {
            {"姓名", "", 0, 6, 9},
            {"学号", "", 0, 21, 9},
            {"性别", "", 0, 31, 9},
            {"年龄", "", 0, 41, 4}
        };

        status = inputForm(fields, 4, drawTableFrameStudent);

        if (!status) return scount;
        if(!emptyExist(fields, 4)){
            gotoxy(5,10);
            printf("信息输入不完整，请重新输入");
            _getch();
            continue;
        }
        
        gotoxy(5,10);

        if ((strcmp(fields[2].buffer, "男") != 0) && (strcmp(fields[2].buffer, "女") != 0)){
            gotoxy(5,10);
            printf("性别输入错误，请重新输入");
            _getch();
            continue;
        }

        char *endptr;
        float score = strtof(fields[3].buffer, &endptr);
        if (*endptr != '\0' || score < 0) {
            gotoxy(5,10);
            printf("年龄输入异常，请重新输入");
            _getch();
            continue;
        }

        int dataPos = queryStuExistByID(slist, scount, fields[1].buffer);
        if (dataPos == -1){
            strcpy(slist[scount].xm, fields[0].buffer);
            strcpy(slist[scount].xh, fields[1].buffer);
            strcpy(slist[scount].xb, fields[2].buffer);
            slist[scount].nl = atoi(fields[3].buffer);
            scount++;
        } else{
            printf("学号已存在,是否覆盖？(y/n):");
            char coverChoice;
            scanf(" %c", &coverChoice);
            if (coverChoice == 'y'){
                strcpy(slist[dataPos].xm, fields[0].buffer);
                strcpy(slist[dataPos].xh, fields[1].buffer);
                strcpy(slist[dataPos].xb, fields[2].buffer);
                slist[dataPos].nl = atoi(fields[3].buffer);
            }
        }
        gotoxy(5,10);
        for (int i = 0; i < 75; i++) putchar(' ');
        gotoxy(5,10);
        char contChoice;
        printf("是否继续输入？(y/n):");
        scanf(" %c", &contChoice);
        ifContinue = (contChoice == 'y');
    }
    return scount;
}

int input_course(Course clist[], int ccount){
    int ifContinue = 1;
    int status = 0;
    while(ifContinue){
        system("cls");

        gotoxy(5,8);
        printf("←→切换输入项，回车确认，ESC退出");

        inputField courseFields[] = {
            {"课号", "", 0, 6, 10},
            {"课名", "", 0, 17, 20},
            {"学分", "", 0, 38, 6}
        };

        status = inputForm(courseFields, 3, drawTableFrameCourse);

        if (!status) return ccount;
        if(!emptyExist(courseFields, 3)){
            gotoxy(5,10);
            printf("信息输入不完整，请重新输入");
            _getch();
            continue;
        }

        char *endptr;
        float score = strtof(courseFields[2].buffer, &endptr);
        if (*endptr != '\0' || score < 0) {
            gotoxy(5,10);
            printf("学分输入异常，请重新输入");
            _getch();
            continue;
        }

        gotoxy(5,10);

        int dataPos = queryCrsExistByID(clist, ccount, courseFields[0].buffer);

        if (dataPos == -1){
            strcpy(clist[ccount].kh, courseFields[0].buffer);
            strcpy(clist[ccount].km, courseFields[1].buffer);
            clist[ccount].xf = atof(courseFields[2].buffer);
            ccount++;
        } else{
            printf("课号已存在,是否覆盖？(y/n):");
            char coverChoice;
            scanf(" %c", &coverChoice);
            if (coverChoice == 'y'){
                strcpy(clist[dataPos].kh, courseFields[0].buffer);
                strcpy(clist[dataPos].km, courseFields[1].buffer);
                clist[dataPos].xf = atof(courseFields[2].buffer);
            }
        }
        
        gotoxy(5,10);
        for (int i = 0; i < 75; i++) putchar(' ');
        gotoxy(5,10);
        char contChoice;
        printf("是否继续输入？(y/n):");
        scanf(" %c", &contChoice);
        ifContinue = (contChoice == 'y');
    }
    return ccount;
}



int input_select(Select sclist[], int sccount, Student slist[], int scount, Course clist[], int ccount){
    int ifContinue = 1;
    int status = 0;
    while(ifContinue){
        system("cls");

        gotoxy(5,8);
        printf("←→切换输入项，回车确认，ESC退出");

        inputField selectFields[] = {
            {"学号", "", 0, 6, 10},
            {"课号", "", 0, 17, 10},
            {"成绩", "", 0, 28, 5}
        };

        status = inputForm(selectFields, 3, drawTableFrameSelect);

        if(!status) return sccount;
        if(!emptyExist(selectFields, 3)){
            gotoxy(5,10);
            printf("信息输入不完整，请重新输入");
            _getch();
            continue;
        }

        gotoxy(5,10);

        int dataPos = querySelExistByID(sclist, sccount, selectFields[0].buffer, selectFields[1].buffer);

        char *endptr;
        float score = strtof(selectFields[2].buffer, &endptr);
        if (*endptr != '\0' || score < -1 || score > 120) {
            gotoxy(5,10);
            printf("成绩输入异常，请重新输入");
            _getch();
            continue;
        }
        
        if (queryStuExistByID(slist, scount, selectFields[0].buffer) != -1 && queryCrsExistByID(clist, ccount, selectFields[1].buffer) != -1){
            if (dataPos == -1){
                strcpy(sclist[sccount].xh, selectFields[0].buffer);
                strcpy(sclist[sccount].kh, selectFields[1].buffer);
                sclist[sccount].cj = atof(selectFields[2].buffer);
                sccount++;
            } else{
                printf("该选课记录已经存在，是否覆盖？(y/n):");
                char coverChoice;
                scanf(" %c", &coverChoice);
                if (coverChoice == 'y'){
                    strcpy(sclist[dataPos].xh, selectFields[0].buffer);
                    strcpy(sclist[dataPos].kh, selectFields[1].buffer);
                    sclist[dataPos].cj = atof(selectFields[2].buffer);
                }
            }
        }else{
            printf("学号或课号不存在，请检查输入");
            _getch();
            continue;
        }

        gotoxy(5,10);
        for (int i = 0; i < 75; i++) putchar(' ');
        gotoxy(5,10);
        char contChoice;
        printf("是否继续输入？(y/n):");
        scanf(" %c", &contChoice);
        ifContinue = (contChoice == 'y');
    }
    return sccount;
}


///////////////////////////////////输入区

//画边框的函数
void drawTableFrameStudent(){
    char title[] = "请输入学生数据：";
    int xPos[] = {5, 20, 30, 40, 50};
    drawTable(xPos, 5, title);
}

void drawTableFrameCourse() {
    char title[] = "请输入课程数据：";
    int xPos[] = {5, 16, 37, 44};
    drawTable(xPos, 4, title);
}

void drawTableFrameSelect() {
    char title[] = "请输入选课数据：";
    int xPos[] = {5, 16, 27, 33};
    drawTable(xPos, 4, title);
}

//xPos:x0,x1,x2,x3,..
void drawTable(int xPos[], int count, char title[]){
    gotoxy(5, 2);
    printf("%s", title);
    gotoxy(5, 3);
    printChar('=', xPos[count - 1] - 4);//上边框
    for (int i = 0; i < count; i++) {
        gotoxy(xPos[i], 4); putchar('|');
    }
    gotoxy(5, 5);
    printChar('-', xPos[count - 1] - 4);//分隔线
    for (int i = 0; i < count; i++) {
        gotoxy(xPos[i], 6); putchar('|');
    }
    gotoxy(5, 7);
    printChar('=', xPos[count - 1] - 4);//下边框
}

int emptyExist(inputField fields[], int count){
    for (int i=0; i<count; i++){
        if (fields[i].buffer[0] == '\0'){
            return 0;
        }
    }
    return 1;
}