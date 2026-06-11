# 成绩管理系统

## 一、系统功能

成绩管理系统要求实现学生成绩管理的基本功能，包括学生、课程、成绩信息的录入、删除、查找和导入/导出等。
学生信息的属性包括：学号、姓名、性别和年龄；
课程信息包括：课号、课名和学分；
选课信息包括：学号、课号和成绩。

1. 功能要求

**录入**：从指定的文件或默认的文件中导入学生信息、课程信息以及选课信息，并创建成绩单；

**显示**：分屏显示系统中所有学生信息、课程信息、成绩信息；

**输入**：通过键盘输入学生记录或课程记录或选课记录到成绩管理系统中；

**删除**：删除一条已经存在的学生记录或课程记录或选课记录；

**查找**：根据用户输入的属性值查找符合条件的学生信息或课程信息或成绩信息；

**输出**：把当前所有的学生信息、课程信息、选课信息以及学生的成绩单全部输出到指定的文件中。

### 程序执行过程

循环显示主菜单，用户在“请给出你的选择：”后面输入选项（数字 0~6），按回车后执行相应功能。参照“菜单设计练习”的要求建立主菜单结构。

---

## 二、菜单功能

### 1. 导入初始数据

从指定文件或默认文件导入学生、课程、选课信息，并根据选课记录及课程学分创建成绩单，计算加权平均分，再按平均分高低排序。

### 2. 显示信息（显示所有记录）

- 按学号升序显示所有学生记录，每屏 10 条，按任意键继续；
- 按课程号升序显示课程记录；
- 按平均成绩降序显示成绩单。

### 3. 输入记录（具有修改功能）

从键盘输入学生、课程或选课信息，增加新记录。
每输入一条记录都检测是否已存在，若存在则提示是否替换，否则直接增加。
每输入完一条记录提示是否继续，根据输入决定继续与否。

### 4. 删除记录（逐条记录确认）

根据输入的学生姓名或课程名称，删除相关学生或课程记录。若有多条满足条件的记录，则逐一确认是否删除。

### 5. 查询信息

- 输入学号或姓名查询学生相关信息；
- 输入课程号或课程名查询课程相关信息；
- 根据学号查询该学生的选课信息、成绩单及排名情况。

### 6. 批量导出数据

把当前所有学生信息、课程信息、选课信息以及成绩单全部输出到磁盘文件，文件名以时间字符串命名。

### 0. 退出

结束程序运行，退出成绩管理系统。

> 上述 7 个主菜单选项中的显示、输入、删除以及查询功能都包含 3 个子功能，运行时给出对应的下一级子菜单选项，根据输入调用相关函数。

---

## 三、本课设基本要求

### 1. 数据结构

用结构体数组实现成绩信息的记录和管理。

#### （1）学生信息结构体

```c
typedef struct
{
    char xh[10];   // 学号
    char xm[20];   // 姓名，10个汉字以内
    char xb[3];    // 性别，只能保存一个汉字
    int nl;        // 年龄
} Student;
```

#### （2）课程信息结构体

```c
typedef struct
{
    char kh[10];   // 课号，长度10字符以内
    char km[25];   // 课名，12个汉字以内
    float xf;      // 课程学分，浮点数
} Course;
```

#### （3）选课信息结构体

```c
typedef struct
{
    char xh[10];   // 学号
    char kh[10];   // 课程号
    float cj;      // 成绩，浮点数
} Select;
```

#### （4）成绩单信息结构体

```c
typedef struct
{
    char xh[10];     // 学号
    char xm[20];     // 姓名
    float cj[30];    // 各门课程成绩
    float zpj;       // 加权平均分
    float zxf;       // 总修习学分
} Score;
```

### 主函数中定义的数组

- `Student slist[]` — 学生信息数组
- `Course clist[]` — 课程信息数组
- `Select sclist[]` — 选课信息数组（每名学生的一门选课对应一条记录）
- `Score cjlist[]` — 成绩单数组（每名学生对应一条记录，包含平均分、总学分及排名）

---

### 2. 各函数功能

以下函数原型为本课程设计的基本要求，请尽量不要更改。

#### （1）初始化数据

```c
void init(Student slist[], int *scount, Course clist[], int *ccount, Select sclist[], int *sccount);
```

程序启动时通过指定文件（若未指定或失败则从默认文件）装入学生、课程、选课信息，并将记录条数分别保存到 `*scount`、`*ccount`、`*sccount` 中。

#### （2）建立成绩单

```c
int create_cjlist(Select sclist[], int sccount, Course clist[], int ccount, Score cjlist[]);
```

根据选课数组中的学号查询学生姓名，填入成绩单；再根据课程号按课程顺序将成绩填入对应位置；最后计算加权平均分和总学分。
加权平均分计算公式：

$$
\text{加权平均分} = \frac{\sum (\text{成绩} \times \text{学分})}{\sum \text{学分}}
$$

#### （3）显示数据

```c
void disp_student(Student slist[], int scount);   // 显示所有学生，每10条暂停，按学号升序
void disp_course(Course clist[], int ccount);     // 显示所有课程，每10条暂停，按课号升序
void disp_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount); // 显示成绩单，每10行暂停，按平均分降序
```

显示前需调用对应的排序函数：

```c
void sort_slist(Student slist[], int scount);     // 按学号升序
void sort_clist(Course clist[], int ccount);      // 按课程号升序
void sort_cjlist(Score cjlist[], int cjcount);    // 按平均成绩降序
```

#### （4）数据输入

```c
int input_std(Student slist[], int scount);       // 输入学生记录，返回新记录数
int input_course(Course clist[], int ccount);     // 输入课程记录，返回新记录数
int input_select(Select sclist[], int sccount);   // 输入选课记录，返回新记录数
```

- 每输入一条记录，检测是否已存在，若存在则提示是否替换（兼具增加和修改功能）。
- 每输入完一条，提示是否继续。
- `input_select` 还需校验学号、课程号是否存在，成绩范围 `-1 ≤ 成绩 ≤ 120`（-1 表示暂无成绩）。

#### （5）删除记录

```c
int delete_std(Student slist[], int scount);       // 根据姓名或学号删除学生记录
int delete_course(Course clist[], int ccount);     // 根据课程名或课号删除课程记录
int delete_select(Select sclist[], int sccount);   // 根据学号删除选课记录
```

返回剩余记录数。

#### （6）查询信息

```c
void query_std(Student slist[], int scount);                 // 按学号或姓名查询学生
void query_course(Course clist[], int ccount);               // 按课号或课程名查询课程
void query_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount); // 按学号查询成绩单（含排名）
```

#### （7）批量导出数据

```c
void write_to_file1(Student slist[], int scount, Course clist[], int ccount, Select sclist[], int sccount);
```

以时间字符串为文件名分别保存学生、课程、选课信息。例如：
`student20190918120423.txt`、`course20190918120430.txt`、`select201909181258.txt`

```c
void write_to_file2(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount);
```

以时间字符串为文件名保存成绩单，内容包括：名次、学号、姓名、性别、各门课成绩、平均分、总学分等。
