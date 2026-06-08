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

int create_cjlist(Student slist[], int scount, Select sclist[], int sccount, Course clist[], int ccount, Score cjlist[]){
    system("cls");
    int cjcount=0;

    for (int i=0; i<sccount; i++){
        if(!queryExistInCJLByID(sclist, sccount, cjlist, cjcount, sclist[i].xh)){
            for(int j=0; j<ccount; j++){
                cjlist[cjcount].cj[j] = -2;//-2表示未选
            }//初始化成绩数组
            strcpy(cjlist[cjcount].xh, sclist[i].xh);
            strcpy(cjlist[cjcount].xm, getNameByID(slist, scount, sclist[i].xh));

            int pos = getClassPosByClassID(clist, ccount, sclist[i].kh);
            cjlist[cjcount].cj[pos] = sclist[i].cj;

            if (sclist[i].cj != -1){
                float credit = getPointByClass(clist, ccount, sclist[i].kh);
                cjlist[cjcount].zpj = sclist[i].cj * credit;
                cjlist[cjcount].zxf = credit;
            } else {
                cjlist[cjcount].zpj = 0;
                cjlist[cjcount].zxf = 0;
            }
            cjcount++;
        }else{
            int idx = locateByID(sclist[i].xh, cjlist, cjcount);
            int pos = getClassPosByClassID(clist, ccount, sclist[i].kh);
            cjlist[idx].cj[pos] = sclist[i].cj;

            if (sclist[i].cj != -1){
                float credit = getPointByClass(clist, ccount, sclist[i].kh);
                cjlist[idx].zpj += sclist[i].cj * credit;
                cjlist[idx].zxf += credit;
            }
        }
    }

    for (int i=0; i<cjcount; i++){
        if (cjlist[i].zxf > 0)
            cjlist[i].zpj /= cjlist[i].zxf;
        else
            cjlist[i].zpj = 0;
    }

    return cjcount;
}
