#include "data.h"

static inline void printArrayInt(int array[], int size) {   // 使用 static inline 避免多重定义
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

void initDefault(Student slist[], int *scount, Course clist[], int *ccount, Select sclist[], int *sccount){
    FILE *studentFile, *courseFile, *selectFile;
    system("cls");
    if((studentFile = fopen("data/student_default.txt", "r")) == NULL){
        printf("默认学生文件打开失败！\n");
        system("pause");
        exit(1);
    }
    if((courseFile = fopen("data/course_default.txt", "r")) == NULL){
        printf("默认课程文件打开失败！\n");
        system("pause");
        exit(1);
    }
    if((selectFile = fopen("data/select_default.txt", "r")) == NULL){
        printf("默认选课文件打开失败！\n");
        system("pause");
        exit(1);
    }
    while(fscanf(studentFile,"%9s %19s %3s %d", 
            slist[*scount].xh,
            slist[*scount].xm,
            slist[*scount].xb,
            &slist[*scount].nl) == 4)
    {
        (*scount)++;
    }
    while(fscanf(courseFile,"%9s %24s %f", 
            clist[*ccount].kh,
            clist[*ccount].km,
            &clist[*ccount].xf
        ) == 3)
    {
        (*ccount)++;
    }
    while(fscanf(selectFile,"%9s %9s %f",
            sclist[*sccount].xh,
            sclist[*sccount].kh,
            &sclist[*sccount].cj) == 3)
    {
        (*sccount)++;
    }
    system("cls");
    fclose(studentFile);
    fclose(courseFile);
    fclose(selectFile);
    //printStudents(slist, *scount);
    //printCourses(clist, *ccount);
    //printSelects(sclist, *sccount);
    printf("===== 默认初始化完成 =====\n");
    system("pause");
}