#include "data.h"

void sortFromLow(int array[], int length);
void sortFromHigh(float array[], int length);

// 显示所有学生，每10条暂停，按学号升序
void disp_student(Student slist[], int scount){
    system("cls");
    sort_slist(slist, scount);
    printf("%-4s  %-12s  %-2s  %2s\n", "学号", "姓名", "性别", "年龄");
    printf("===========================\n");
    int count = 0;
    for(int i = 0; i < scount; i++){
        printf("%-4s  %-12s  %-2s  %2d\n",
               slist[i].xh,
               slist[i].xm,
               slist[i].xb,
               slist[i].nl);
        if(((i + 1) % 10 == 0)||(i + 1 == scount)){
            printf("===========================\n共有%d条记录，当前显示第%d条到第%d条\n", scount, count*10 + 1, i + 1);
            count++;
            if((i + 1 != scount)){
                system("pause");
                system("cls");
                printf("%-4s  %-12s  %-2s  %2s\n", "学号", "姓名", "性别", "年龄");
                printf("===========================\n");
            }else {
                system("pause");
                system("cls");
            }
        }
    }
}

// 显示所有课程，每10条暂停，按课号升序
void disp_course(Course clist[], int ccount){
    system("cls");
    sort_clist(clist, ccount);
    printf("%-4s  %-12s  %-2s\n", "课号", "课程名", "学分");
    printf("===========================\n");
    int count = 0;
    for(int i = 0; i < ccount; i++){
        printf("%-4s  %-12s  %-2.2f\n", 
            clist[i].kh, 
            clist[i].km, 
            clist[i].xf);
        if(((i + 1) % 10 == 0)||(i + 1 == ccount)){
            printf("===========================\n共有%d条记录，当前显示第%d条到第%d条\n", ccount, count*10 + 1, i + 1);
            count++;
            if((i + 1 != ccount)){
                system("pause");
                system("cls");
                printf("%-4s  %-12s  %-2s\n", "课号", "课程名", "学分");
                printf("===========================\n");
            }else {
                system("pause");
                system("cls");
            }
        }
    }

};

// 显示成绩单，每10行暂停，按平均分降序
void disp_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount){
    system("cls");
    sort_cjlist(cjlist, cjcount);
    printf("%-10s %-20s %-8s %-8s %s\n", "学号", "姓名", "加权平均分", "总学分", "成绩明细");
    printf("====================================\n");
    int count = 0;
    for(int i = 0; i < cjcount; i++){
        printf("%-10s %-20s %-8.2f %-8.1f",
               cjlist[i].xh,
               cjlist[i].xm,
               cjlist[i].zpj,
               cjlist[i].zxf);
        printf("[");
        for (int j = 0; j < ccount; j++) {
            if (cjlist[i].cj[j] != -1) {
                printf("%-4s:%-4.2f\t", clist[j].km, cjlist[i].cj[j]);
            }
        }
        printf("]\n");
        if(((i + 1) % 10 == 0)||(i + 1 == cjcount)){
            printf("===========================\n共有%d条记录，当前显示第%d条到第%d条\n", cjcount, count*10 + 1, i + 1);
            count++;
            if((i + 1 != cjcount)){
                system("pause");
                system("cls");
            }else {
                system("pause");
                system("cls");
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

