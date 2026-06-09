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
    {"01", "高等数学", 4.0},
    {"02", "大学英语", 3.0},
    {"03", "程序设计", 3.5},
    {"04", "体育", 1.0},
    {"05", "数据结构", 3.5}
};
static int defaultCcount = sizeof(defaultCourses) / sizeof(Course);

static Select defaultSelects[] = {
    {"1001", "01", 111.4},
    {"1001", "02", 78.0},
    {"1001", "03", 92.0},
    {"1001", "04", -1.0},
    {"1002", "01", 76.0},
    {"1002", "02", 88.0},
    {"1002", "03", 84.0},
    {"1003", "01", 95.0},
    {"1003", "03", 89.0},
    {"1004", "02", 82.0},
    {"1004", "04", 90.0},
    {"1005", "01", 81.0},
    {"1005", "02", 85.0},
    {"1005", "05", 91.0}
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
}
