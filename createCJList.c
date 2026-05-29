#include "data.h"

/*
typedef struct
{
    char xh[10];     // 学号
    char xm[20];     // 姓名
    float cj[30];    // 各门课程成绩
    float zpj;       // 加权平均分
    float zxf;       // 总修习学分
} Score;
*/

int ifStudentExist(Select sclist[], int sccount, Score cjlist[], int cjcount, char xh[]);//输入学号，判断该生是否已经存在cjlist中

int create_cjlist(Student slist[], int scount, Select sclist[], int sccount, Course clist[], int ccount, Score cjlist[]){
    system("cls");
    int cjcount=0;
    
    for (int i=0; i<sccount; i++){
        if(!ifStudentExist(sclist, sccount, cjlist, cjcount, sclist[i].xh)){
            for(int j=0; j<ccount; j++){
                cjlist[cjcount].cj[j] = -1;//-1表示空
            }//初始化成绩数组
            strcpy(cjlist[cjcount].xh, sclist[i].xh);
            strcpy(cjlist[cjcount].xm, getNameByID(slist, scount, sclist[i].xh));
            cjlist[cjcount].cj[getClassPosByClassID(clist, ccount, sclist[i].kh)] = sclist[i].cj;
            cjlist[cjcount].zpj = sclist[i].cj;
            cjlist[cjcount].zxf = getPointByClass(clist, ccount, sclist[i].kh);
            cjcount++;
        }else{
            cjlist[locateByID(sclist[i].xh, cjlist, cjcount)].cj[getClassPosByClassID(clist, ccount, sclist[i].kh)] = sclist[i].cj;
            //v:原加权平均乘以学分加当前成绩乘以当前学分
            cjlist[locateByID(sclist[i].xh, cjlist, cjcount)].zpj = (cjlist[locateByID(sclist[i].xh, cjlist, cjcount)].zpj*cjlist[locateByID(sclist[i].xh, cjlist, cjcount)].zxf + sclist[i].cj*getPointByClass(clist, ccount, sclist[i].kh));
            //v:更新总学分
            cjlist[locateByID(sclist[i].xh, cjlist, cjcount)].zxf += getPointByClass(clist, ccount, sclist[i].kh);
            //v:除以总学分得到新的加权平均
            cjlist[locateByID(sclist[i].xh, cjlist, cjcount)].zpj /= cjlist[locateByID(sclist[i].xh, cjlist, cjcount)].zxf;
        }
    }
    printScore(cjlist, cjcount, clist, ccount);

    //system("pause");
    return cjcount;
}

int ifStudentExist(Select sclist[], int sccount, Score cjlist[], int cjcount, char xh[]){
    for(int i=0; i<cjcount;i++){
        if(strcmp(cjlist[i].xh,xh)==0){
            return 1;
        }
    }
    return 0;
}
