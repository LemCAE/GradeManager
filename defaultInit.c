#include "data.h"

static Student defaultStudents[] = {
    {"1001", "张三", "男", 20},
    {"1002", "李四", "女", 21},
    {"1003", "王五", "男", 19},
    {"1004", "赵六", "男", 20},
    {"1005", "周梅", "女", 22}
};
static int defaultScount = sizeof(defaultStudents) / sizeof(Student);

static Course defaultCourses[] = {
    {"C01", "高等数学", 4.0},
    {"C02", "大学英语", 3.0},
    {"C03", "程序设计", 3.5},
    {"C04", "体育", 1.0},
    {"C05", "数据结构", 3.5}
};
static int defaultCcount = sizeof(defaultCourses) / sizeof(Course);

static Select defaultSelects[] = {
    {"1001", "C01", 85.4},
    {"1001", "C02", 78.0},
    {"1001", "C03", 92.0},
    {"1001", "C04", 88.0},
    {"1002", "C01", 76.0},
    {"1002", "C02", 88.0},
    {"1002", "C03", 84.0},
    {"1003", "C01", 95.0},
    {"1003", "C03", 89.0},
    {"1004", "C02", 82.0},
    {"1004", "C04", 90.0},
    {"1005", "C01", 81.0},
    {"1005", "C02", 85.0},
    {"1005", "C05", 91.0}
};
static int defaultSccount = sizeof(defaultSelects) / sizeof(Select);

void initDefault(Student slist[], int *scount, Course clist[], int *ccount, Select sclist[], int *sccount){
    system("cls");
    memcpy(slist, defaultStudents, sizeof(defaultStudents));
    *scount = defaultScount;
    memcpy(clist, defaultCourses, sizeof(defaultCourses));
    *ccount = defaultCcount;
    memcpy(sclist, defaultSelects, sizeof(defaultSelects));
    *sccount = defaultSccount;
    //printStudents(slist, *scount);
    //printCourses(clist, *ccount);
    //printSelects(sclist, *sccount);
    //printf("===== 默认初始化完成 =====\n");
    //system("pause");
}
