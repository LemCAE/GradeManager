#include "data.h"

int queryStuExistByID(Student slist[], int scount, char xh[]){
    for(int i = 0; i < scount; i++){
        if(strcmp(slist[i].xh, xh) == 0){
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


