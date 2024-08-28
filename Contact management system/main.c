#define _CRT_SECURE_NO_WARNINGS 1

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define DEFAULT_SZ 5
#define INC_SZ 2

typedef struct PeoInfo
{
    char num[5];
    char name[50];
    char phone[20];//办公室电话
    char call[20];
}PeoInfo;

typedef struct Contact
{
    PeoInfo* data;//指向动态申请的空间，用来存放联系人的信息
    int sz;//记录的是当前通讯录中有效信息的个数
    int capacity;//记录当前通讯录的最大容量
}Contact;


//初始化通讯录
void InitContact(Contact* pc);

//增加联系人
void AddContact(Contact* pc);

//打印
void PrintContact(const Contact* pc);

//删除
void DelContact(Contact* pc);

//查找指定联系人
void SearchContact(Contact* pc);

void CheckCapacity(Contact* pc);


void Cxpos(Contact* pc,int pos);




//动态版本-初始化
void InitContact(Contact* pc)
{
    pc->data = (PeoInfo*)malloc(DEFAULT_SZ * sizeof(PeoInfo));
    if (pc->data == NULL)
    {
        perror("InitContact");
        return;
    }
    pc->sz = 0;//初始化后默认是0
    pc->capacity = DEFAULT_SZ;

    
}


void CheckCapacity(Contact* pc)
{
    if (pc->sz == pc->capacity)
    {
        PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (pc->capacity + INC_SZ) * sizeof(PeoInfo));
        if (ptr != NULL)
        {
            pc->data = ptr;
            pc->capacity += INC_SZ;
            printf("增容成功\n");
        }
        else
        {
            perror("AddContact");
            printf("增加联系人失败\n");
            return;
        }
    }
}

//动态版本- 增加联系人
void AddContact(Contact* pc)
{
    int x = 0;
    int y = 0;
    char nameORid[20] = { 0 };
    //考虑增容
    CheckCapacity(pc);
    //增加一个人的信息
    printf("选择要顺序添加新员工信息还是插入添加，选择1为顺序添加，选择2为插入添加，选择其他数字退出添加:>");
    scanf("%d", &x);
    if (x == 1)
    {
        printf("进入顺序添加\n请输入员工编号:>");
        scanf("%s", pc->data[pc->sz].num);

        printf("请输入名字:>");
        scanf("%s", pc->data[pc->sz].name);

        printf("请输入办公室电话:>");
        scanf("%s", pc->data[pc->sz].phone);

        printf("请输入手机号码:>");
        scanf("%s", pc->data[pc->sz].call);

        pc->sz++;
    }
    else if (x == 2)
    {
        printf("进入插入添加\n请查看现有的员工信息并输入你要插入的在哪位员工编号前:>\n");
        PrintContact(pc);
        
        scanf("%s", &nameORid);
        
        int pos = FindByNameORid(pc, nameORid);
        Cxpos(pc, pos);

        printf("请输入员工编号:>\n");
        scanf("%s", pc->data[pos].num);

        printf("请输入名字:>");
        scanf("%s", pc->data[pos].name);

        printf("请输入办公室电话:>");
        scanf("%s", pc->data[pos].phone);

        printf("请输入手机号码:>");
        scanf("%s", pc->data[pos].call);
        pc->sz++;
    }
    else
    {
        printf("退出添加\n");
        return;
    }
    
    printf("\n增加成功\n\n");
}
void Cxpos(Contact* pc,int pos)
{
    int i = 0;
    int j = 0;
    for (i = pos,j=pc->sz+1; (i < pc->sz  &&  i<=j); j--)
    {
        pc->data[j+1] = pc->data[j];
    }
    
}



void PrintContact(const Contact* pc)
{
    int i = 0;
    //打印标题
    printf("%-9s\t%-9s\t%-10s\t%-10s\n", "员工编号", "员工姓名", "办公室电话", "手机号码");
    //打印数据
    for (i = 0; i < pc->sz; i++)
    {
        if (*(pc->data[i].name) != 0)
        {
            printf("%-9s\t%-9s\t%-10s\t%-10s\n",
                pc->data[i].num,
                pc->data[i].name,
                pc->data[i].phone,
                pc->data[i].call);
        }
        
    }
    printf("\n");
}

void PrintContact2(const Contact* pc,int x)
{
        printf("%-9s\t%-9s\t%-10s\t%-10s\n", "员工编号", "员工姓名", "办公室电话", "手机号码");

        printf("%-9s\t%-9s\t%-10s\t%-10s\n",
            pc->data[x].num,
            pc->data[x].name,
            pc->data[x].phone,
            pc->data[x].call);

        printf("\n");
    
    
}


static int FindByNameORid(Contact* pc, char nameORid[])
{
    int i = 0;
    for (i = 0; i < pc->sz; i++)
    {
        if (strcmp(pc->data[i].name, nameORid) == 0 || strcmp(pc->data[i].num, nameORid) == 0)
        {
            return i;
        }
    }

    return -1;//找不到
}

static int FindByNameORid2(Contact* pc, char nameORid[],int T)
{
    int i = T;
    for (i = T; i < pc->sz; i++)
    {
        if (strcmp(pc->data[i].name, nameORid) == 0 || strcmp(pc->data[i].num, nameORid) == 0)
        {
            
                
            //PrintContact2(pc, i);
            //i = pc->sz;
            FindByNameORid2(pc, nameORid, T + 1);
            
            return 1;
                
        }
    }
    

    return -1;
}
static int FindByNameORid3(Contact* pc, char nameORid[], int T)
{
    int i = T;
    int x = pc->sz;
    for (i = T; i < pc->sz; i++)
    {
        if (strcmp(pc->data[i].name, nameORid) == 0 || strcmp(pc->data[i].num, nameORid) == 0)
        {
            
            
            *(pc->data[i].num) = 0; 
            *(pc->data[i].name) = 0;
            *(pc->data[i].phone) = 0;
            *(pc->data[i].call) = 0;
            FindByNameORid3(pc, nameORid, T + 1);
            return 1;

        }
    }


    return -1;
}
////void DL(Contact* pc)
//{
//	int i = 0,count=0;
//	
//	for (int i = 0; i < pc->sz - 1; i++)
//	{
//		if (*(pc->data[i].num) == 0  && *(pc->data[i].num)!=0)
//		{
//			pc->data[i] = pc->data[i + 1];
//			*(pc->data[i+1].num) = 0;
//			*(pc->data[i+1].name) = 0;
//			*(pc->data[i+1].phone) = 0;
//			*(pc->data[i+1].call) = 0;
//			count++;
//		}
//		pc->sz - count;
//	}
//	
//	
//}




void DelContact(Contact* pc)
{
    int pos = 0;
    int T = 0;
    int i = 0;
    char nameORid[20] = { 0 };
    PrintContact(pc);
    if (pc->sz == 0)
    {
        printf("通讯录为空，无需删除\n");
        return;
    }
    printf("请输入要删除人的名字:>");
    scanf("%s", &nameORid);

    int a = 9 ;
    
    
    pos=FindByNameORid2(pc, nameORid, T);
    if (pos == -1)
    {
        printf("要删除的人不存在\n");
        return;
    }
    if (pos == 1)
    {
        printf("输入1全部删除同名同性人，输入2只删除第一条:>");
        scanf("%d", &a);
    }
    
    if (a == 1)
    {
        FindByNameORid3(pc, nameORid, T);
    }
    if (a == 2)
    {
        int pos= FindByNameORid(pc, nameORid);
        for (i = pos; i < pc->sz - 1; i++)
        {
            pc->data[i] = pc->data[i + 1];
        }
        pc->sz--;
    }
    
    
    
    printf("删除成功\n");
}



void SearchContact(Contact* pc)
{
    char nameORid[20] = { 0 };
    int a = 0;
    int b = 0;
L:
    printf("请选择你要查询的方式进行查询，输入1为员工姓名查询，输入2为员工编号查询:>\n");
    scanf("%d", &a);
    if (a == 1)
    {
        printf("进入员工姓名查询\n");
        printf("请输入你要查询的员工姓名:>\n");
        scanf("%s", &nameORid);
    }
    else if (a == 2)
    {
        printf("进入员工编号查询\n");
        printf("请输入你要查询的员工编号:>\n");
        scanf("%s", &nameORid);
    }
    else
    {
        printf("输入错误，请重新输入你要的查询方式\n");
        goto L;
    }
    int pos = FindByNameORid(pc, nameORid);
    if (pos == -1)
    {
        printf("要查找的人不存在\n");
        return;
    }
    else
    {
        printf("%-9s\t%-9s\t%-10s\t%-10s\n", "员工编号", "员工姓名", "办公室电话", "手机号码");
        //打印数据
        printf("%-9s\t%-9s\t%-10s\t%-10s\n",
            pc->data[pos].num,
            pc->data[pos].name,
            pc->data[pos].phone,
            pc->data[pos].call);
        printf("\n查看上一条员工信息请按1，查看下一条员工信息请按2.按0或其他数字退出查找:>");
        scanf("%d", &b);
        while (b==1||b==2)
        {
            
            if (b == 1)
            {
                pos = pos - 1;
                printf("%-9s\t%-9s\t%-10s\t%-10s\n", "员工编号", "员工姓名", "办公室电话", "手机号码");
                printf("%-9s\t%-9s\t%-10s\t%-10s\n",
                    pc->data[pos].num,
                    pc->data[pos].name,
                    pc->data[pos].phone,
                    pc->data[pos].call);
            }
            else
            {
                pos = pos + 1;
                printf("%-9s\t%-9s\t%-10s\t%-10s\n", "员工编号", "员工姓名", "办公室电话", "手机号码");
                printf("%-9s\t%-9s\t%-10s\t%-10s\n",
                    pc->data[pos].num,
                    pc->data[pos].name,
                    pc->data[pos].phone,
                    pc->data[pos].call);
            }
            printf("\n查看上一条员工信息请按1，查看下一条员工信息请按2.按0或其他数字退出查找:>");
            scanf("%d", &b);
        }
        
    }
    printf("\n");
}







void menu()
{
    printf("**************************************************\n");
    printf("******  1. 添加员工信息    2. 删除员工信息  ******\n");
    printf("******  3. 查找员工信息    4. 输出员工信息  ******\n");
    printf("******                                      ******\n");
    printf("******  0. 退出                              *****\n");
    printf("**************************************************\n");
}

enum Option
{
    EXIT,
    ADD,
    DEL,
    SEARCH,
    PRINT
};

int main()
{
    int input = 0;
    //创建通讯录
    Contact con;//通讯录
    //初始化通讯录
    
    InitContact(&con);

    do
    {
        menu();
        printf("请选择:>");
        scanf("%d", &input);
        switch (input)
        {
        case ADD:
            //增加人的信息
            AddContact(&con);
            break;
        case DEL:
            //删除
            DelContact(&con);
            
            break;
        case SEARCH:
            SearchContact(&con);
            break;
        
        
        case PRINT:
            PrintContact(&con);
            break;
        case EXIT:
            printf("退出通讯录\n");
            break;
        default:
            printf("选择错误,重新选择\n");
            break;
        }
    } while (input);

    return 0;
}
