#include "data.h"

int menu_select();
int displayMenuSelect();
int inputMenuSelect();
int queryMenuSelect();
int deleteMenuSelect();int generalMenu(char *items[], int count, int enableESC);

int main(){
    SetConsoleOutputCP(CP_UTF8);//切换UTF-8
    SetConsoleCP(CP_UTF8);

    Student slist[STUDENT_MAX];
    Course clist[COURSE_MAX];
    Select sclist[SELECT_MAX];
    Score cjlist[SCORE_MAX];

    int scount=0,ccount=0,sccount=0,cjcount=0;
    int stuPos, crsPos;
    
    initDefault(slist, &scount, clist, &ccount, sclist, &sccount);//默认加载文件
    cjcount = create_cjlist(slist, scount, sclist, sccount, clist, ccount, cjlist);//生成成绩单
    
    for(;;){
        switch (menu_select()){
        case 1:
            init(slist, &scount, clist, &ccount, sclist, &sccount);
            cjcount = create_cjlist(slist, scount, sclist, sccount, clist, ccount, cjlist);
            sort_cjlist(cjlist, cjcount);
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
                        sccount = input_select(sclist, sccount, slist, scount, clist, ccount);
                        break;
                    case 0:
                        quit = 1;
                        break;
                }
                if(quit){ 
                    break;
                }
            }
            cjcount = create_cjlist(slist, scount, sclist, sccount, clist, ccount, cjlist);
            break;
        case 4:
            for(;;){
                int quit = 0;
                switch (deleteMenuSelect()){
                    case 1:
                        scount = delete_std(slist, scount);
                        clearSCList(slist, scount, clist, ccount, sclist, &sccount);
                        cjcount = create_cjlist(slist, scount, sclist, sccount, clist, ccount, cjlist);
                        break;
                    case 2:
                        ccount = delete_course(clist, ccount);
                        clearSCList(slist, scount, clist, ccount, sclist, &sccount);
                        cjcount = create_cjlist(slist, scount, sclist, sccount, clist, ccount, cjlist);
                        break;
                    case 3:
                        clearSCList(slist, scount, clist, ccount, sclist, &sccount);
                        sccount = delete_select(sclist, sccount, slist, scount, clist, ccount, cjlist, cjcount);
                        cjcount = create_cjlist(slist, scount, sclist, sccount, clist, ccount, cjlist);
                        break;
                    case 0:
                        quit = 1;
                        break;
                }
                if(quit){ 
                    break;
                }
            }
            break;
        case 5:
            for(;;){
                int quit = 0;
                switch (queryMenuSelect()){
                    case 1:
                        query_std(slist, scount, &stuPos);
                        _getch();
                        break;
                    case 2:
                        query_course(clist, ccount, &crsPos);
                        _getch();
                        break;
                    case 3:
                        sort_cjlist(cjlist, cjcount);
                        query_cjlist(cjlist, cjcount, clist, ccount, slist, scount, sclist, sccount);
                        break;
                    case 0:
                        quit = 1;
                        break;
                }
                if(quit){ 
                    break;
                }
            }
            break;
        case 6:
            sort_cjlist(cjlist, cjcount);
            write_to_file1(slist, scount, clist, ccount, sclist, sccount);
            write_to_file2(cjlist, cjcount, clist, ccount, slist, scount);
            break;
        case 0:
            exit(0);
        }
    }

    return 0;
}

////////////////////////////

int menu_select() {
    char *items[] = {
        "1. 导入数据",
        "2. 显示信息",
        "3. 输入记录",
        "4. 删除记录",
        "5. 查询信息",
        "6. 批量导出数据",
        "0. 退出"
    };
    int count = 7;
    return generalMenu(items, count, 0);
}


int displayMenuSelect() {
    char *items[] = {
        "1. 按学号升序显示学生记录",
        "2. 按课程号升序显示课程记录",
        "3. 按平均成绩降序显示成绩单",
        "0. 返回上一级菜单"
    };
    int count = 4;
    return generalMenu(items, count, 1);
}

int inputMenuSelect() {
    char *items[] = {
        "1. 输入学生数据",
        "2. 输入课程数据",
        "3. 输入选课数据",
        "0. 返回上一级菜单"
    };
    int count = 4;
    return generalMenu(items, count, 1);
}

int queryMenuSelect() {
    char *items[] = {
        "1. 按学号或姓名查询学生记录",
        "2. 按课程号或课程名查询课程记录",
        "3. 按学号查询成绩单",
        "0. 返回上一级菜单"
    };
    int count = 4;
    return generalMenu(items, count, 1);
}

int deleteMenuSelect() {
    char *items[] = {
        "1. 删除学生记录",
        "2. 删除课程记录",
        "3. 删除选课记录",
        "0. 返回上一级菜单"
    };
    int count = 4;
    return generalMenu(items, count, 1);
}

int generalMenu(char *items[], int count, int enableESC){
    int selected = 0;
    int x = 5, y = 2;

    system("cls");
    for (int i = 0; i < count; i++) {
        gotoxy(x, y + i);
        if (i == selected) setcolor(7, 0);
        else setcolor(0, 7);
        printf("%s", items[i]);
    }
    setcolor(0, 7);

    while (1) {
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            int key = _getch();
            int prev = selected;
            if (key == 72) selected = (selected - 1 + count) % count;
            else if (key == 80) selected = (selected + 1) % count;

            if (prev != selected) {
                gotoxy(x, y + prev);
                setcolor(0, 7);
                printf("%s", items[prev]);
                gotoxy(x, y + selected);
                setcolor(7, 0);
                printf("%s", items[selected]);
                setcolor(0, 7);
            }
        } else if (ch == '\r') {
            if (selected == count - 1) return 0;
            else return selected + 1;
        } else if (enableESC && ch == 27) {
            return 0;
        }
    }
}