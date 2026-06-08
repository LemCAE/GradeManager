#include "data.h"

int queryStuExistByID(Student slist[], int scount, char xh[]){
    for(int i = 0; i < scount; i++){
        if(strcmp(slist[i].xh, xh) == 0){
            return i;
        }
    }
    return -1;
}

int queryStuExistByName(Student slist[], int scount, char xm[]){
    for(int i = 0; i < scount; i++){
        if(strcmp(slist[i].xm, xm) == 0){
            return i;
        }
    }
    return -1;
}

int queryCrsExistByID(Course clist[], int ccount, char kh[]){
    for(int i = 0; i < ccount; i++){
        if(strcmp(clist[i].kh, kh) == 0){
            return i;
        }
    }
    return -1;
}

int queryCrsExistByName(Course clist[], int ccount, char km[]){
    for(int i = 0; i < ccount; i++){
        if(strcmp(clist[i].km, km) == 0){
            return i;
        }
    }
    return -1;
}

int querySelExistByID(Select sclist[], int sccount, char xh[], char kh[]){
    for(int i = 0; i < sccount; i++){
        if(strcmp(sclist[i].xh, xh) == 0 && strcmp(sclist[i].kh, kh) == 0){
            return i;
        }
    }
    return -1;
}


int queryExistInCJLByID(Select sclist[], int sccount, Score cjlist[], int cjcount, char xh[]){
    for(int i=0; i<cjcount;i++){
        if(strcmp(cjlist[i].xh,xh)==0){
            return 1;
        }
    }
    return 0;
}

int queryExistInCJLByIDWithPos(Select sclist[], int sccount, Score cjlist[], int cjcount, char xh[]){
    for(int i=0; i<cjcount;i++){
        if(strcmp(cjlist[i].xh,xh)==0){
            return i;
        }
    }
    return -1;
}

