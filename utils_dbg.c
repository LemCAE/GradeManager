#include "data.h"

static inline void printArrayInt(int array[], int size) {
    printf("\n===============================\n");
    int printN = 1;
    for (int i = 0; i < size; i++) {
        printf("group[%d] = %d\t", i, array[i]);
        if (!(printN%8)){printf("\n");}
        printN++;
    }
    printf("\n===============================\n");
}

int printfile(FILE *infile)
{
    printf("===printfile===\n");
    if (infile == NULL){
        printf("Error: File not found\n");
        return 1;
    }
    int ch;
    while ((ch = fgetc(infile)) != EOF){
        putchar(ch);
    }
    printf("\n===============\n");
    rewind(infile);
    return 0;
}

void printStudents(Student slist[], int count) {
    printf("===== 学生信息 (%d 条) =====\n", count);
    printf("%-10s %-20s %-4s %-4s\n", "学号", "姓名", "性别", "年龄");
    printf("%-10s %-20s %-4s %-4s\n", "xh[10]", "xm[20]", "xb[4]", "nl");
    for (int i = 0; i < count; i++) {
        printf("%-10s %-20s %-4s %-4d\n",
               slist[i].xh,
               slist[i].xm,
               slist[i].xb,
               slist[i].nl);
    }
}

void printCourses(Course clist[], int count) {
    printf("===== 课程信息 (%d 条) =====\n", count);
    printf("%-10s %-25s %-6s\n", "课号", "课名", "学分");
    printf("%-10s %-25s %-6s\n", "kh[10]", "km[25]", "xf");
    for (int i = 0; i < count; i++) {
        printf("%-10s %-25s %-6.1f\n",
               clist[i].kh,
               clist[i].km,
               clist[i].xf);
    }
}

void printSelects(Select sclist[], int count) {
    printf("===== 选课信息 (%d 条) =====\n", count);
    printf("%-10s %-10s %-6s\n", "学号", "课号", "成绩");
    printf("%-10s %-10s %-6s\n", "xh[10]", "kh[10]", "cj");
    for (int i = 0; i < count; i++) {
        printf("%-10s %-10s %-6.2f\n",
               sclist[i].xh,
               sclist[i].kh,
               sclist[i].cj);
    }
}

void printScore(Score cjlist[], int count, Course clist[], int ccount) {
    printf("===== 成绩汇总 (%d 条) =====\n", count);
    printf("%-10s %-20s %-8s %-8s %s\n", "学号", "姓名", "加权平均分", "总学分", "成绩明细");
    printf("%-10s %-20s %-8s %-8s %s\n", "xh[10]", "xm[20]", "zpj", "zxf", "ClassName:cj[i]");
    for (int i = 0; i < count; i++) {
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
    }
}

