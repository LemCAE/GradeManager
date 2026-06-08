#include "data.h"

int delete_std(Student slist[], int scount){        // 根据姓名或学号删除学生记录
    int stuPos = -1;
    char choice;
    query_std(slist, scount, &stuPos);

    if(stuPos != -1){
        gotoxy(5,8);
        printf("是否删除该学生记录？(y/n): ");
        scanf(" %c", &choice);
        if(choice == 'y' || choice == 'Y'){
            for(int i = stuPos; i < scount - 1; i++){
                slist[i] = slist[i+1];
            }
            scount--;
        }
    }

    return scount;
}

int delete_course(Course clist[], int ccount){      // 根据课程名或课号删除课程记录
    int crsPos = -1;
    char choice;
    query_course(clist, ccount, &crsPos);

    if(crsPos != -1){
        gotoxy(5,8);
        printf("是否删除该课程记录？(y/n): ");
        scanf(" %c", &choice);
        if(choice == 'y' || choice == 'Y'){
            for(int i = crsPos; i < ccount - 1; i++){
                clist[i] = clist[i+1];
            }
            ccount--;
        }
    }
    
    return ccount;
}

int delete_select(Select sclist[], int sccount){    // 根据学号删除选课记录
    
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