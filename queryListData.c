#include "data.h"

// 按学号或姓名查询学生
void query_std(Student slist[], int scount, int *stuPos){ 
    system("cls");

    gotoxy(5,8);
    printf("←→切换输入项，回车确认，ESC退出");

    inputField fields[] = {
        {"姓名", "", 0, 6, 9},
        {"学号", "", 0, 21, 9}
    };

    int status = inputForm(fields, 2, drawTableFrameStudentQuery);

    if(!status || (fields[0].buffer[0] == '\0' && fields[1].buffer[0] == '\0')){
        return;
    }

    if(fields[1].buffer[0] != '\0'){
        int dataPos = queryStuExistByID(slist, scount, fields[1].buffer);
        if (dataPos == -1){
            gotoxy(5, 10);
            printf("未找到该学生");
            return;
        }else{
            gotoxy(5, 10);
            displayStudent(slist, dataPos);
            *stuPos = dataPos;
        }
    }else{
        int dataPos = queryStuExistByName(slist, scount, fields[0].buffer);
        if (dataPos == -1){
            gotoxy(5, 10);
            printf("未找到该学生");
            return;
        }else{
            gotoxy(5, 10);
            displayStudent(slist, dataPos);
            *stuPos = dataPos;
        }
    }
}

// 按课号或课程名查询课程
void query_course(Course clist[], int ccount, int *crsPos){
    system("cls");

    gotoxy(5,8);
    printf("←→切换输入项，回车确认，ESC退出");

    inputField fields[] = {
        {"课号", "", 0, 6, 10},
        {"课名", "", 0, 17, 20}
    };

    int status = inputForm(fields, 2, drawTableFrameCourseQuery);

    if(!status || (fields[0].buffer[0] == '\0' && fields[1].buffer[0] == '\0')){
        return;
    }

    if(fields[0].buffer[0] != '\0'){
        int dataPos = queryCrsExistByID(clist, ccount, fields[0].buffer);
        if (dataPos == -1){
            gotoxy(5, 10);
            printf("未找到该课程");
            return;
        }else{
            gotoxy(5, 10);
            displayCourse(clist, dataPos);
            *crsPos = dataPos;
        }
    } else{
        int dataPos = queryCrsExistByName(clist, ccount, fields[1].buffer);
        if (dataPos == -1){
            gotoxy(5, 10);
            printf("未找到该课程");
            return;
        } else{
            gotoxy(5, 10);
            displayCourse(clist, dataPos);
            *crsPos = dataPos;
        }
    }
}

// 按学号查询成绩单（含排名）
void query_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount, Select sclist[], int sccount){
    system("cls");

    gotoxy(5,8);
    printf("←→切换输入项，回车确认，ESC退出");

    inputField fields[] = {
        {"姓名", "", 0, 6, 9},
        {"学号", "", 0, 21, 9}
    };

    int status = inputForm(fields, 2, drawTableFrameStudentQuery);

    if(!status || (fields[0].buffer[0] == '\0' && fields[1].buffer[0] == '\0')){
        return;
    }

    if(fields[1].buffer[0] != '\0'){
        int dataPos = queryExistInCJLByIDWithPos(sclist, sccount, cjlist, cjcount, fields[1].buffer);
        if (dataPos == -1){
            gotoxy(5, 10);
            printf("未找到该学生");
            _getch();
            return;
        }else{
            gotoxy(5, 10);
            displayScore(cjlist, dataPos, clist, ccount, slist, scount, sclist, sccount);
            _getch();
        }
    }else{
        int stuIdx = queryStuExistByName(slist, scount, fields[0].buffer);
        if (stuIdx == -1){
            gotoxy(5, 10);
            printf("未找到该学生");
            _getch();
            return;
        }
        int dataPos = queryExistInCJLByIDWithPos(sclist, sccount, cjlist, cjcount, slist[stuIdx].xh);
        if (dataPos == -1){
            gotoxy(5, 10);
            printf("未找到该学生");
            _getch();
            return;
        }else{
            gotoxy(5, 10);
            displayScore(cjlist, dataPos, clist, ccount, slist, scount, sclist, sccount);
            _getch();
        }
    }
}
