#include "data.h"

void sort_slist(Student slist[], int scount){
    for(int i=0; i<scount; i++){
        for(int j=0; j<scount-i-1; j++){
            if(atoi(slist[j].xh)>atoi(slist[j+1].xh)){
                Student temp = slist[j];
                slist[j] = slist[j+1];
                slist[j+1] = temp;
            }
        }
    }
}

void sort_clist(Course clist[], int ccount){
    for(int i=0; i<ccount; i++){
        for(int j=0; j<ccount-i-1; j++){
            if(atoi(clist[j].kh)>atoi(clist[j+1].kh)){
                Course temp = clist[j];
                clist[j] = clist[j+1];
                clist[j+1] = temp;
            }
        }
    }
}

void sort_cjlist(Score cjlist[], int cjcount){
    for(int i=0; i<cjcount; i++){
        for(int j=0; j<cjcount-i-1; j++){
            if(cjlist[j].zpj<cjlist[j+1].zpj){
                Score temp = cjlist[j];
                cjlist[j] = cjlist[j+1];
                cjlist[j+1] = temp;
            }
        }
    }
}

void sortFromLow(int array[], int length){
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length - i - 1; j++){
            if(array[j] > array[j + 1]){
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void sortFromHigh(float array[], int length){
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length - i - 1; j++){
            if(array[j] < array[j + 1]){
                float temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}