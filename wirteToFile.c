#include "data.h"

char time_str[15];

void write_to_file1(Student slist[], int scount, Course clist[], int ccount, Select sclist[], int sccount){
    system("cls");
    FILE *studentFile, *courseFile, *selectFile;
    
    char studentFileName[64];
    char courseFileName[64];
    char selectFileName[64];

    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    strftime(time_str, sizeof(time_str), "%Y%m%d%H%M%S", localTime);

    sprintf(studentFileName, "output/%sstudent.txt", time_str);
    sprintf(courseFileName, "output/%scourse.txt", time_str);
    sprintf(selectFileName, "output/%sselect.txt", time_str);

    sort_slist(slist, scount);    
    sort_clist(clist, ccount);
    
    if((studentFile = fopen(studentFileName, "w")) == NULL){
        printf("[writeToFile]Error opening file\n");
        return;
    }
    if((courseFile = fopen(courseFileName, "w")) == NULL){
        printf("[writeToFile]Error opening file\n");
        return;
    }
    if((selectFile = fopen(selectFileName, "w")) == NULL){
        printf("[writeToFile]Error opening file\n");
        return;
    }

    for(int i = 0; i < scount; i++){
        fprintf(studentFile, "%s  %-s  %s  %d\n",
               slist[i].xh,
               slist[i].xm,
               slist[i].xb,
               slist[i].nl);
    }

    
    for(int i = 0; i < ccount; i++){
        fprintf(courseFile,"%s  %s  %.2f\n", 
            clist[i].kh, 
            clist[i].km, 
            clist[i].xf);
    }

    for(int i = 0; i < sccount; i++){
        fprintf(selectFile, "%s  %s  %.2f\n",
               sclist[i].xh,
               sclist[i].kh,
               sclist[i].cj);
    }

    fclose(studentFile);
    fclose(courseFile);
    fclose(selectFile);
    printf("已成功导出数据文件!\n");
}

void write_to_file2(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount){
    FILE *scoreFile;
    char scoreFileName[64];

    sprintf(scoreFileName, "output/%sscore.txt", time_str);

    if((scoreFile = fopen(scoreFileName, "w")) == NULL){
        printf("[writeToFile]Error opening file\n");
        return;
    }

    fprintf(scoreFile,"===== 成绩汇总 (%d 条) =====\n", cjcount);
    fprintf(scoreFile,"%-10s %-20s %-8s %-8s %s\n", "学号", "姓名", "加权平均分", "总学分", "成绩明细");
    for (int i = 0; i < cjcount; i++) {
        fprintf(scoreFile,"%-10s %-20s %-8.2f %-8.1f",
               cjlist[i].xh,
               cjlist[i].xm,
               cjlist[i].zpj,
               cjlist[i].zxf);
        fprintf(scoreFile,"[");
        for (int j = 0; j < ccount; j++) {
            if (cjlist[i].cj[j] != -1) {
                fprintf(scoreFile,"%-4s:%-4.2f\t", clist[j].km, cjlist[i].cj[j]);
            }
        }
        fprintf(scoreFile,"]\n");
    }
    fclose(scoreFile);
}