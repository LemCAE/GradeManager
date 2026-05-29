#include "data.h"
#include <windows.h>

int menu_select();
int subMenu_select();

int main(){
    SetConsoleOutputCP(CP_UTF8);//切换UTF-8

    Student slist[STUDENT_MAX];
    Course clist[COURSE_MAX];
    Select sclist[SELECT_MAX];
    Score cjlist[SCORE_MAX];

    int scount=0,ccount=0,sccount=0,cjcount=0;
    
    initDefault(slist, &scount, clist, &ccount, sclist, &sccount);//默认加载文件
    cjcount = create_cjlist(slist, scount, sclist, sccount, clist, ccount, cjlist);//生成成绩单
    
    for(;;){
        switch (menu_select()){
        case 1:
            init(slist, &scount, clist, &ccount, sclist, &sccount);
            cjcount = create_cjlist(slist, scount, sclist, sccount, clist, ccount, cjlist);
            printf("导入成功\n");
            system("pause");
            break;
        case 2:
            for(;;){
                int quit = 0;
                switch (subMenu_select()){
                case 1:
                    disp_student(slist, scount);
                    break;
                case 2:
                    disp_course(clist, ccount);
                    break;
                case 3:
                    disp_cjlist(cjlist, cjcount, clist, ccount, slist, scount);
                    break;
                case 0:
                    quit = 1;
                    break;
                }
                if(quit){ 
                    break;
                    system("pause");
                }
            }
            break;
        case 3:
            printf("Function3\n");
            system("pause");
            break;
        case 4:
            printf("Function4\n");

            system("pause");
            break;
        case 5:
            printf("Function5\n");

            system("pause");
            break;
        case 6:
            printf("Function6\n");

            system("pause");
            break;
        case 0:
            system("pause");
            exit(0);
        }
    }

    return 0;
}

int menu_select(){
    char c;
    do {
        system("cls");
        printf("1. 导入初始数据\n");
        printf("2. 显示信息\n");
        printf("3. 输入记录\n");
        printf("4. 删除记录\n");
        printf("5. 查询信息\n");
        printf("6. 批量导出数据\n");
        printf("0. 退出\n");
        printf("Input 1-6,0: ");
        c=getchar();
    } while (c<'0' || c>'6');
    return(c-'0');
}

int subMenu_select(){
    char c;
    do {
        system("cls");
        printf("1. 按学号升序显示学生记录\n");
        printf("2. 按课程号升序显示课程记录\n");
        printf("3. 按平均成绩降序显示成绩单\n");
        printf("0. 返回上一级菜单\n");
        printf("Input 1-3,0: ");
        c=getchar();
    } while (c<'0' || c>'3');
    return(c-'0');
}