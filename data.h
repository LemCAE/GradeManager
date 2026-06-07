#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define STUDENT_MAX 100
#define COURSE_MAX 100
#define SELECT_MAX 500
#define SCORE_MAX 100

typedef struct
{
    char xh[10];   // 学号
    char xm[20];   // 姓名，10个汉字以内
    char xb[4];    // 性别，只能保存一个汉字（UTF-8需要4字节！目前暂时这样子改）
    int nl;        // 年龄
} Student;

typedef struct
{
    char kh[10];   // 课号，长度10字符以内
    char km[25];   // 课名，12个汉字以内
    float xf;      // 课程学分，浮点数
} Course;

typedef struct
{
    char xh[10];   // 学号
    char kh[10];   // 课程号
    float cj;      // 成绩，浮点数
} Select;

typedef struct
{
    char xh[10];     // 学号
    char xm[20];     // 姓名
    float cj[30];    // 各门课程成绩
    float zpj;       // 加权平均分
    float zxf;       // 总修习学分
} Score;

typedef struct{
    char *title;
    char buffer[20];
    int pos;
    int x;
    int width;
}inputField;//定义输入区

//初始化数据    initData.c
void init(Student slist[], int *scount, Course clist[], int *ccount, Select sclist[], int *sccount);

//建立成绩单        ！是不是要改函数原型？不然读不到姓名
int create_cjlist(Student slist[], int scount, Select sclist[], int sccount, Course clist[], int ccount, Score cjlist[]);

//显示数据
void disp_student(Student slist[], int scount);   // 显示所有学生，每10条暂停，按学号升序
void disp_course(Course clist[], int ccount);     // 显示所有课程，每10条暂停，按课号升序
void disp_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount); 
        // 显示成绩单，每10行暂停，按平均分降序

//数据排序  sort.c
void sort_slist(Student slist[], int scount);     // 按学号升序
void sort_clist(Course clist[], int ccount);      // 按课程号升序
void sort_cjlist(Score cjlist[], int cjcount);    // 按平均成绩降序

//数据输入
int input_std(Student slist[], int scount);       // 输入学生记录，返回新记录数
int input_course(Course clist[], int ccount);     // 输入课程记录，返回新记录数
int input_select(Select sclist[], int sccount, Student slist[], int scount, Course clist[], int ccount);   // 输入选课记录，返回新记录数

//数据删除，返回剩余的记录数
int delete_std(Student slist[], int scount);       // 根据姓名或学号删除学生记录
int delete_course(Course clist[], int ccount);     // 根据课程名或课号删除课程记录
int delete_select(Select sclist[], int sccount);   // 根据学号删除选课记录

//数据查询
void query_std(Student slist[], int scount);                 // 按学号或姓名查询学生
void query_course(Course clist[], int ccount);               // 按课号或课程名查询课程
void query_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount); // 按学号查询成绩单（含排名）

//数据导出  output.c
void write_to_file1(Student slist[], int scount, Course clist[], int ccount, Select sclist[], int sccount);
        //以时间字符串为文件名分别保存学生、课程、选课信息
void write_to_file2(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount);
        //以时间字符串为文件名保存成绩单，内容包括：名次、学号、姓名、性别、各门课成绩、平均分、总学分等。

//通过键获取值
int locateByID(char xh[], Score cjlist[], int cjcount);//输入学号，查找在成绩数组中的位置
char* getNameByID(Student slist[], int scount, char xh[]);//输入学号，获得姓名
float getPointByClass(Course clist[], int ccount, char kh[]);//输入课号，获得学分
int getClassPosByClassID(Course clist[], int ccount, char kh[]);//输入课号，获得课程在课程数组中的位置
int getStuPosByID(Student array[], int length, int id);
int getCrsPosByID(Course array[], int length, int id);
int getScoPosBySco(Score array[], int length, float score, int disped[]);

//调试用函数
int printfile(FILE *infile);
void printStudents(Student slist[], int count);
void printCourses(Course clist[], int count);
void printSelects(Select sclist[], int count);
void printScore(Score cjlist[], int count, Course clist[], int ccount);
void initDefault(Student slist[], int *scount, Course clist[], int *ccount, Select sclist[], int *sccount);

//输出控制
void gotoxy(int x, int y);
void setcolor(int bg, int fg);
void printChar(char c, int number);
void cleaInputBuffer();//清空缓冲区，不过现在暂时用不着了

//防重复查询
int queryStuExistByID(Student slist[], int scount, char xh[]);
int queryCrsExistByID(Course clist[], int ccount, char kh[]);
int querySelExistByID(Select sclist[], int sccount, char xh[], char kh[]);
int queryExistInCJLByID(Select sclist[], int sccount, Score cjlist[], int cjcount, char xh[]);//输入学号，判断该生是否已经存在cjlist中
int emptyExist(inputField fields[], int count);


//utf-8编码控制
int utf8CharLen(unsigned char c);//判断utf-8编码的字符长度
int utf8DisplayWidth(const char *str);//计算utf-8编码的字符串显示宽度

//通用排序
void sortFromLow(int array[], int length);
void sortFromHigh(float array[], int length);

//绘制TUI
void drawField(inputField *f, int active);
int inputForm(inputField fields[], int count, void (*drawFrame)(void));

#endif