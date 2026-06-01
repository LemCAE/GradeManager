#include "data.h"

typedef struct{
    char *title;
    char buffer[20];
    int pos;
    int x;
    int width;
}inputField;//定义输入区

void drawField(inputField *f, int active);
void drawTableFrameStudent();
void drawTableFrameCourse();
void drawTableFrameSelect();
int inputForm(inputField fields[], int count, void (*drawFrame)(void));
int emptyExist(inputField fields[], int count);

//主输入函数

int input_std(Student slist[], int scount){
    int ifContinue = 1;
    int status = 0;
    while(ifContinue){
        system("cls");

        gotoxy(5,8);
        printf("←→切换输入项，回车确认，ESC退出");

        inputField fields[] = {
            {"姓名", "", 0, 6, 9},
            {"学号", "", 0, 21, 9},
            {"性别", "", 0, 31, 9},
            {"年龄", "", 0, 41, 4}
        };

        status = inputForm(fields, 4, drawTableFrameStudent);

        if (!status) return scount;
        if(!emptyExist(fields, 4)){
            gotoxy(5,10);
            printf("信息输入不完整，请重新输入");
            _getch();
            continue;
        }
        
        gotoxy(5,10);

        int dataPos = queryStuExistByID(slist, scount, fields[1].buffer);
        if (dataPos == -1){
            strcpy(slist[scount].xm, fields[0].buffer);
            strcpy(slist[scount].xh, fields[1].buffer);
            strcpy(slist[scount].xb, fields[2].buffer);
            slist[scount].nl = atoi(fields[3].buffer);
            scount++;
        } else{
            printf("学号已存在,是否覆盖？(y/n):");
            char coverChoice;
            scanf(" %c", &coverChoice);
            if (coverChoice == 'y'){
                strcpy(slist[dataPos].xm, fields[0].buffer);
                strcpy(slist[dataPos].xh, fields[1].buffer);
                strcpy(slist[dataPos].xb, fields[2].buffer);
                slist[dataPos].nl = atoi(fields[3].buffer);
            }
        }
        gotoxy(5,10);
        for (int i = 0; i < 75; i++) putchar(' ');
        gotoxy(5,10);
        char contChoice;
        printf("是否继续输入？(y/n):");
        scanf(" %c", &contChoice);
        ifContinue = (contChoice == 'y');
    }
    return scount;
}

int input_course(Course clist[], int ccount){
    int ifContinue = 1;
    int status = 0;
    while(ifContinue){
        system("cls");

        gotoxy(5,8);
        printf("←→切换输入项，回车确认，ESC退出");

        inputField courseFields[] = {
            {"课号", "", 0, 6, 10},
            {"课名", "", 0, 17, 20},
            {"学分", "", 0, 38, 6}
        };

        status = inputForm(courseFields, 3, drawTableFrameCourse);

        if (!status) return ccount;
        if(!emptyExist(courseFields, 4)){
            gotoxy(5,10);
            printf("信息输入不完整，请重新输入");
            _getch();
            continue;
        }

        gotoxy(5,10);

        int dataPos = queryCrsExistByID(clist, ccount, courseFields[0].buffer);

        if (dataPos == -1){
            strcpy(clist[ccount].kh, courseFields[0].buffer);
            strcpy(clist[ccount].km, courseFields[1].buffer);
            clist[ccount].xf = atof(courseFields[2].buffer);
            ccount++;
        } else{
            printf("课号已存在,是否覆盖？(y/n):");
            char coverChoice;
            scanf(" %c", &coverChoice);
            if (coverChoice == 'y'){
                strcpy(clist[dataPos].kh, courseFields[0].buffer);
                strcpy(clist[dataPos].km, courseFields[1].buffer);
                clist[dataPos].xf = atof(courseFields[2].buffer);
            }
        }
        
        gotoxy(5,10);
        for (int i = 0; i < 75; i++) putchar(' ');
        gotoxy(5,10);
        char contChoice;
        printf("是否继续输入？(y/n):");
        scanf(" %c", &contChoice);
        ifContinue = (contChoice == 'y');
    }
    return ccount;
}

/*
这里怎么判断？
首先要保证学号和课号都存在，即使用上面的query函数（大判断）
不行，这里没有传入sclist和clist，所以不能直接用...hyw
那我只能修改已有的数据啊...
然后确认这个学生有没有现在这门课的成绩记录？
比如固定学号，循环课号
如果找到了就返回i，不然返回-1
那这里的逻辑还是一样的
留着吧，这个不确定
*/

int input_select(Select sclist[], int sccount){
    int ifContinue = 1;
    while(ifContinue){
        system("cls");
        inputField selectFields[] = {
            {"学号", "", 0, 6, 10},
            {"课号", "", 0, 17, 10},
            {"成绩", "", 0, 28, 5}
        };

        inputForm(selectFields, 3, drawTableFrameSelect);

        gotoxy(5,10);



        
        gotoxy(5,10);
        for (int i = 0; i < 75; i++) putchar(' ');
        gotoxy(5,10);
        char contChoice;
        printf("是否继续输入？(y/n):");
        scanf(" %c", &contChoice);
        ifContinue = (contChoice == 'y');
    }
    return sccount;
}


///////////////////////////////////输入区


// 输入框绘制
void drawField(inputField *f, int active){//绘制输入区
    int titleY=4, inputY=6;

    gotoxy(f->x, titleY);//画标题
    if(active){setcolor(7,0);}
    else{setcolor(0,7);}
    printf("%s", f->title);

    setcolor(0,7);
    gotoxy(f->x, inputY);//画输入框
    for(int i=0; i<f->width; i++){
        printf(" ");
    }

    gotoxy(f->x, inputY);
    printf("%s", f->buffer);//先清空输入框，然后打印缓冲区里面的内容
}

int inputForm(inputField fields[], int count, void (*drawFrame)(void)){
    int active=0;

    for (int i=0; i<count; i++){//初始化缓冲区和位置
        fields[i].buffer[0] = '\0';
        fields[i].pos = 0;
    }

    drawFrame();//调用函数，绘制外边框

    for (int i=0; i<count; i++){//画输入区
        drawField(&fields[i], i==active);
    }
    setcolor(0,7);

    while (1){//这里开始读取输入，也许可以加一个按Tab的功能
        inputField *cur = &fields[active];
        gotoxy(cur->x + utf8DisplayWidth(cur->buffer), 6);//输入位置
        int ch = _getch();

        if (ch == 0 || ch == 224){
            int key = _getch();
            if (key == 75){//左
                if (active > 0){
                    drawField(&fields[active], 0);
                    active--;
                    drawField(&fields[active], 1);
                }
            } else if (key == 77){//右
                if (active < count-1){
                    drawField(&fields[active], 0);
                    active++;
                    drawField(&fields[active], 1);
                }
            }
        } else if (ch == '\r'){
            return 1;
        } else if (ch == 27){
            return 0;
        } else if (ch == '\b'){
            if (cur->pos > 0){
            // 找到最后一个 UTF-8 字符的起始位置
            int p = cur->pos - 1;
            while (p > 0 && (cur->buffer[p] & 0xC0) == 0x80) p--;  // 跳过后续字节
            int delCharWidth = utf8DisplayWidth(cur->buffer + p); // 待删字符的宽度

            // 擦除屏幕上该字符占据的格数
            int currentTotalWidth = utf8DisplayWidth(cur->buffer);
            gotoxy(cur->x + currentTotalWidth - delCharWidth, 6);
            for (int i = 0; i < delCharWidth; i++) putchar(' ');

            // 更新 buffer
            cur->buffer[p] = '\0';
            cur->pos = p;
            }
        } else if ((ch >=32 && ch <= 126) || (ch &0x80)){
            char utf8_char[5] = {0};
            int len = utf8CharLen((unsigned char)ch);
            utf8_char[0] = ch;
            for (int i = 1; i < len; i++) {
                utf8_char[i] = _getch();
            }
            utf8_char[len] = '\0';

            // 计算新字符的显示宽度
            int char_width = utf8DisplayWidth(utf8_char);
            int current_width = utf8DisplayWidth(cur->buffer);
            int new_width = current_width + char_width;

            // 检查是否超出字段宽度
            if (new_width <= cur->width && cur->pos + len < (int)sizeof(cur->buffer)) {
                strcat(cur->buffer, utf8_char);
                cur->pos += len;
                printf("%s", utf8_char);
            }
        }
        setcolor(0,7);
    }
}


//画边框的函数..不想写通用了xwx
void drawTableFrameStudent(){
    gotoxy(5,2);
    printf("请输入学生数据：");

    gotoxy(5,3);
    printChar('=', 46);

    // 标题行竖线
    gotoxy(5,4);printf("|");
    gotoxy(20,4);printf("|");
    gotoxy(30,4);printf("|");
    gotoxy(40,4);printf("|");
    gotoxy(50,4);printf("|");

    // 分隔线
    gotoxy(5,5);
    printChar('-', 46);

    // 输入行竖线
    gotoxy(5,6);printf("|");
    gotoxy(20,6);printf("|");
    gotoxy(30,6);printf("|");
    gotoxy(40,6);printf("|");
    gotoxy(50,6);printf("|");

    // 底线
    gotoxy(5,7);
    printChar('=', 46);
}

void drawTableFrameCourse() {
    gotoxy(5, 2);
    printf("请输入课程数据：");

    gotoxy(5, 3);
    printChar('=', 40);

    gotoxy(5, 4);  putchar('|');
    gotoxy(16, 4); putchar('|');
    gotoxy(37, 4); putchar('|');
    gotoxy(44, 4); putchar('|');

    gotoxy(5, 5);
    printChar('-', 40);

    gotoxy(5, 6);  putchar('|');
    gotoxy(16, 6); putchar('|');
    gotoxy(37, 6); putchar('|');
    gotoxy(44, 6); putchar('|');

    gotoxy(5, 7);
    printChar('=', 40);
}

void drawTableFrameSelect() {
    gotoxy(5, 2);
    printf("请输入选课记录：");

    gotoxy(5, 3);
    printChar('=', 29);

    gotoxy(5, 4);  putchar('|');
    gotoxy(16, 4); putchar('|');
    gotoxy(27, 4); putchar('|');
    gotoxy(33, 4); putchar('|');

    gotoxy(5, 5);
    printChar('-', 29);

    gotoxy(5, 6);  putchar('|');
    gotoxy(16, 6); putchar('|');
    gotoxy(27, 6); putchar('|');
    gotoxy(33, 6); putchar('|');

    gotoxy(5, 7);
    printChar('=', 29);
}

int emptyExist(inputField fields[], int count){
    for (int i=0; i<count; i++){
        if (fields[i].buffer[0] == '\0'){
            return 0;
        }
    }
    return 1;
}