#include "data.h"

int menu_select();
int displayMenuSelect();
int inputMenuSelect();
int queryMenuSelect();
int deleteMenuSelect();

int main(){
    SetConsoleOutputCP(CP_UTF8);//切换UTF-8
    SetConsoleCP(CP_UTF8);

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
                switch (displayMenuSelect()){
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
            for(;;){
                int quit = 0;
                switch (inputMenuSelect()){
                    case 1:
                        scount = input_std(slist, scount);
                        break;
                    case 2:
                        ccount = input_course(clist, ccount);
                        break;
                    case 3:
                        sccount = input_select(sclist, scount);
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
        case 4:
            for(;;){
                int quit = 0;
                switch (deleteMenuSelect()){
                    case 1:
                        scount = delete_std(slist, scount);
                        break;
                    case 2:
                        ccount = delete_course(clist, ccount);
                        break;
                    case 3:
                        sccount = delete_select(sclist, scount);
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
        case 5:
            for(;;){
                int quit = 0;
                switch (queryMenuSelect()){
                    case 1:
                        query_std(slist, scount);
                        break;
                    case 2:
                        query_course(clist, ccount);
                        break;
                    case 3:
                        query_cjlist(cjlist, cjcount, clist, ccount, slist, scount);
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
        case 6:
            write_to_file1(slist, scount, clist, ccount, sclist, sccount);
            write_to_file2(cjlist, cjcount, clist, ccount, slist, scount);
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

int displayMenuSelect(){
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

int inputMenuSelect(){
    char c;
    do {
        system("cls");
        printf("1. 输入学生数据\n");
        printf("2. 输入课程数据\n");
        printf("3. 输入选课数据\n");
        printf("0. 返回上一级菜单\n");
        printf("Input 1-3,0: ");
        c=getchar();
    } while (c<'0' || c>'3');
    return(c-'0');
}

int queryMenuSelect(){
    char c;
    do {
        system("cls");
        printf("1. 按学号或姓名查询学生记录\n");
        printf("2. 按课程号或课程名查询课程记录\n");
        printf("3. 按学号查询成绩单\n");
        printf("0. 返回上一级菜单\n");
        printf("Input 1-3,0: ");
        c=getchar();
    } while (c<'0' || c>'3');
    return(c-'0');
}

int deleteMenuSelect(){
    char c;
    do {
        system("cls");
        printf("1. 删除学生记录\n");
        printf("2. 删除课程记录\n");
        printf("3.删除选课记录\n");
        printf("0. 返回上一级菜单\n");
        printf("Input 1-3,0: ");
        c=getchar();
    } while (c<'0' || c>'3');
    return(c-'0');
}