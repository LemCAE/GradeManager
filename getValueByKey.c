#include "data.h"

int locateByID(char xh[], Score cjlist[], int cjcount){
    for(int i=0; i<cjcount;i++){
        if(strcmp(cjlist[i].xh,xh)==0){
            return i;
        }
    }
    printf("[createCJList] locateByID error\n");
    return -1;
    system("pause");
    exit(1);
}

float getPointByClass(Course clist[], int ccount, char kh[]){
    for(int i=0; i<ccount;i++){
        if(strcmp(clist[i].kh,kh)==0){
            return clist[i].xf;
        }
    }
    printf("[createCJList] getPointByClass error\n");
    return -1;
    system("pause");
    exit(1);
}

char* getNameByID(Student slist[], int scount, char xh[]){
    for(int i=0; i<scount;i++){
        if(strcmp(slist[i].xh,xh)==0){
            return slist[i].xm;
        }
    }
    printf("[createCJList] getNameByID error\n");
    return '\0';
    system("pause");
    exit(1);
}

int getClassPosByClassID(Course clist[], int ccount, char kh[]){
    for(int i=0; i<ccount;i++){
        if(strcmp(clist[i].kh,kh)==0){
            return i;
        }
    }
    printf("[createCJList] getClassPosByClassID error\n");
    return -1;
    system("pause");
    exit(1);
}

int getStuPosByID(Student array[], int length, int id){
    for(int i = 0; i < length; i++){
        if(atoi(array[i].xh) == id){
            return i;
        }
    }
    printf("[dispData] getStuPosByID Error\n");
    return -1;
    system("pause");
    exit(1);
}

int getCrsPosByID(Course array[], int length, int id){
    for(int i = 0; i < length; i++){
        if(atoi(array[i].kh) == id){
            return i;
        }
    }
    printf("[dispData] getCrsPosByID Error\n");
    return -1;
    system("pause");
    exit(1);
}

int getScoPosBySco(Score array[], int length, float score, int disped[]){
    for(int i = 0; i < length; i++){
        if(array[i].zpj == score && !disped[i]){
            disped[i] = 1;
            return i;
        }
    }
    printf("[dispData] getScoPosBySco Error\n");
    return -1;
    system("pause");
    exit(1);
}