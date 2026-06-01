#include "data.h"


void init(Student slist[], int *scount, Course clist[], int *ccount, Select sclist[], int *sccount){
    *scount = 0;
    *ccount = 0;
    *sccount = 0;//重置计数

    system("cls");
    FILE *studentFile, *courseFile, *selectFile;
    char studentFileName[100],courseFileName[100],selectFileName[100];

    printf("请输入学生文件的文件名：");
    scanf("%s", studentFileName);
    printf("请输入课程文件的文件名：");
    scanf("%s", courseFileName);
    printf("请输入选课文件的文件名：");
    scanf("%s", selectFileName);//这里还要处理当输入为空时的情况，此时直接应用默认文件名

    system("cls");

    if((studentFile = fopen(studentFileName, "r")) == NULL){
        printf("选定的学生文件打开失败，尝试打开默认文件\n");
        system("pause");
        system("cls");
        if((studentFile = fopen("data/student_default.txt", "r")) == NULL){
            printf("默认学生文件打开失败！\n");
            system("pause");
            exit(1);
        }
    }
    //printfile(studentFile);
    if((courseFile = fopen(courseFileName, "r")) == NULL){
        printf("选定的课程文件打开失败，尝试打开默认文件\n");
        system("pause");
        system("cls");
        if((courseFile = fopen("data/course_default.txt", "r")) == NULL){
            printf("默认课程文件打开失败！\n");
            system("pause");
            exit(1);
        }
    }
    //printfile(courseFile);
    if((selectFile = fopen(selectFileName, "r")) == NULL){
        printf("选定的选课文件打开失败，尝试打开默认文件\n");
        system("pause");
        system("cls");
        if((selectFile = fopen("data/select_default.txt", "r")) == NULL){
            printf("默认选课文件打开失败！\n");
            system("pause");
            exit(1);
        }
    }
    //printfile(selectFile);


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

    printStudents(slist, *scount);
    printCourses(clist, *ccount);
    printSelects(sclist, *sccount);
    system("pause");
}