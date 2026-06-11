#include "data.h"

int delete_std(Student slist[], int scount){        // 根据姓名或学号删除学生记录
    int stuPos = -1;
    query_std(slist, scount, &stuPos);

    if(stuPos == -1){
        _getch();
    }

    if(stuPos != -1){
        gotoxy(5,8);
        printf("是否删除该学生记录？");
        int selected = sureToProcess(26, 8);
        if (!selected || selected == -1) return scount;
        for(int i = stuPos; i < scount - 1; i++){
            slist[i] = slist[i+1];
        }
        scount--;
    }

    return scount;
}

int delete_course(Course clist[], int ccount){      // 根据课程名或课号删除课程记录
    int crsPos = -1;
    query_course(clist, ccount, &crsPos);

    if(crsPos == -1){
        _getch();
    }

    if(crsPos != -1){
        gotoxy(5,8);
        printf("是否删除该课程记录？");
        int selected = sureToProcess(26, 8);
        if (!selected || selected == -1) return ccount;
        for(int i = crsPos; i < ccount - 1; i++){
            clist[i] = clist[i+1];
        }
        ccount--;
    }
    
    return ccount;
}

int delete_select(Select sclist[], int sccount, Student slist[], int scount, Course clist[], int ccount, Score cjlist[], int cjcount){    // 根据学号删除选课记录
    system("cls");

    gotoxy(5,8);
    printf("←→切换输入项，回车确认，ESC退出");

    inputField fields[] = {
        {"姓名", "", 0, 6, 20},
        {"学号", "", 0, 28, 10}
    };

    int status = inputForm(fields, 2, drawTableFrameStudentQuery);

    if(!status || (fields[0].buffer[0] == '\0' && fields[1].buffer[0] == '\0')){
        return sccount;
    }

    if(fields[1].buffer[0] != '\0'){
        int dataPos = queryExistInCJLByIDWithPos(sclist, sccount, cjlist, cjcount, fields[1].buffer);
        if (dataPos == -1){
            gotoxy(5, 10);
            printf("未找到该学生的选课记录");
            _getch();
            return sccount;
        }else{
            gotoxy(5, 10);
            displayDeleteSelect(cjlist, dataPos, clist, ccount, slist, scount, sclist, &sccount);
        }
    }else{
        int stuIdx = queryStuExistByName(slist, scount, fields[0].buffer);
        if (stuIdx == -1){
            gotoxy(5, 10);
            printf("未找到该学生");
            _getch();
            return sccount;
        }
        int dataPos = queryExistInCJLByIDWithPos(sclist, sccount, cjlist, cjcount, slist[stuIdx].xh);
        if (dataPos == -1){
            gotoxy(5, 10);
            printf("未找到该学生的选课记录");
            _getch();
            return sccount;
        }else{
            gotoxy(5, 10);
            displayDeleteSelect(cjlist, dataPos, clist, ccount, slist, scount, sclist, &sccount);
        }
    }
    return sccount;
}

void clearSCList(Student slist[], int scount, Course clist[], int ccount, Select sclist[], int *sccount){
    for(int i = 0; i < *sccount; ){
        if(queryStuExistByID(slist, scount, sclist[i].xh) == -1 || queryCrsExistByID(clist, ccount, sclist[i].kh) == -1){
            for (int j = i; j < *sccount - 1; j++){
                sclist[j] = sclist[j+1];
            }
            (*sccount)--;
        } else{
            i++;
        }
    }
}