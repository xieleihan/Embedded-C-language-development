#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#define INF 99999
#define M 20

int dist[M][M];
int path[M][M];
int Stack[M];
int top;
int counts;
int visited[M];
using namespace std;

struct vertex//景点信息结构体
{
    int num;
    char name[20];
    char info[300];
};

struct maps
{
    int n;
    int m;
    vertex v[M];
    int edgs[M][M];
}g;//景点信息图结构体

void Creat_vertex()//创建景点信息
{
    g.v[0].num=1;
    strcpy_s(g.v[0].name,"一号学生公寓");
    strcpy_s(g.v[0].info,"这是学生休息的地方");
    g.v[1].num=2;
    strcpy_s(g.v[1].name,"2号学生公寓");
    strcpy_s(g.v[1].name,"这是学生休息的地方");
    g.v[2].num=3;
    strcpy_s(g.v[2].name,"东餐厅");
    strcpy_s(g.v[2].name,"一个来了就不想走的地方");
    g.v[3].num=4;
    strcpy_s(g.v[3].name,"校门");
    strcpy_s(g.v[3].info,"学校入口");
    g.v[4].num=5;
    strcpy_s(g.v[4].name,"一号教学楼");
    strcpy_s(g.v[4].name,"这是同学们学习的地方");
    g.v[5].num=6;
    strcpy_s(g.v[5].name,"五号学生公寓");
    strcpy_s(g.v[5].name,"这是学校第五座教学楼");
    g.v[6].num=7;
    strcpy_s(g.v[6].name,"图书馆");
    strcpy_s(g.v[6].name,"藏书丰富，是同学们阅读学习的好去处");
    g.v[7].num=8;
    strcpy_s(g.v[7].name,"十栋信息工程学院楼");
    strcpy_s(g.v[7].info,"计算机教学楼");
    g.v[8].num=9;
    strcpy_s(g.v[8].name,"男生宿舍");
    strcpy_s(g.v[8].name,"休息生活区域");
    g.v[9].num=10;
    strcpy_s(g.v[9].name,"四号学生公寓");
    strcpy_s(g.v[9].name,"学习的地方");
    g.v[10].num=11;
    strcpy_s(g.v[10].name,"广科湖");
    strcpy_s(g.v[10].name,"人工湖");
}

void Creat_maps()//创建图
{
    int i,j;
    g.n=13;
    g.m=18;
    for(i=0;i<g.n;i++)
    {
        for(j=0;j<g.n;j++)
        {
            g,edgs[i][j]=INF;
        }
    }
    g.edgs[0][1]=g.edgs[1][0]=500;//写入边的权值信息
    g.edgs[0][2]=g.edgs[2][0]=500;//写入边的权值信息
    g.edgs[0][7]=g.edgs[7][0]=500;//写入边的权值信息
    g.edgs[1][3]=g.edgs[3][1]=500;//写入边的权值信息
    g.edgs[1][4]=g.edgs[4][1]=500;//写入边的权值信息
    g.edgs[2][7]=g.edgs[7][2]=500;//写入边的权值信息
    g.edgs[2][10]=g.edgs[10][2]=500;//写入边的权值信息
    g.edgs[3][4]=g.edgs[4][3]=500;//写入边的权值信息
    g.edgs[4][5]=g.edgs[5][4]=500;//写入边的权值信息
    g.edgs[4][6]=g.edgs[6][4]=500;//写入边的权值信息
    g.edgs[5][6]=g.edgs[6][5]=500;//写入边的权值信息
    g.edgs[5][8]=g.edgs[8][5]=500;//写入边的权值信息
    g.edgs[6][8]=g.edgs[8][6]=500;//写入边的权值信息
    g.edgs[6][12]=g.edgs[12][6]=500;//写入边的权值信息
    g.edgs[6][7]=g.edgs[7][6]=500;//写入边的权值信息
    g.edgs[8][9]=g.edgs[9][8]=500;//写入边的权值信息
    g.edgs[9][11]=g.edgs[11][9]=500;//写入边的权值信息
    g.edgs[10][11]=g.edgs[11][10]=500;//写入边的权值信息
}

void Search_info()//搜索景点信息
{
    int i,n;
    printf("广州科技职业技术大学的景点有：\n");
    for(i=0;i<13;i++)
    {
        printf("%d:%s\n",g.v[i].num,g.v[i].name);
    }
    while(1)
    {
        printf("请输入你要查询的景点编号\n");
        printf("按0退出\n");
        scanf("%d",&n);
        getchar();
        if(n==0)
        {
            break;
        }
        else
            if(n<0||n>13)
            {
                printf("输入有误，请重新输入\n");
                continue;
            }
            else
            {
                //这里为什么用n-1，n-1代表了什么
                printf("%d:%s\n",g.v[n-1].num,g.v[n-1].name);
                printf("%s\n",g.v[n-1].info);
            }
    }
}

void Floyd()//弗洛伊德算法
{
    //初始化两个矩阵
    int i,j,k;
    for(i=0;i<g.n;i++)
    {
        for(j=0;j<g.n;j++)
        {
            dist[i][j]=g.edgs[i][j];
            if(i!j&&dist[i][j]<INF)
            {
                path[i][j]=i;
            }
            else
            {
                path[i][j]=-1;
            }
        }
    }
    //核心算法
    for(k=0;k<g.n;k++)
    {
        for(i=0;i<g.n;i++)
        {
            for(j=0;j<g.n;j++)
            {
                if(dist[i][j]>(dist[i][j]+dist[k][j]))
                {
                    dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
        }
    }
    return;
}

//打印从s节点开始，到e节点结束之间的路径
void Floy_print(int s,int e)//打印算法结果
{
    if(path[s][e]==-1||path[s][e]==e||path[s][e]==s)
    {
        return;
    }
    else
    {
        Floy_print(s,path[s][e]);
        printf("%s->",g.v[path[s][e]].name);//打印中间景点名
        Floy_print(path[s][e],e);//将中间点作为起点继续打印路径
}

void Dfs_allpath(int s,int e)//深度优先，全路径
{
    int dis=0;
    int i,j;
    Stack[top]=s;//定义了栈
    top++;//起点
    visited[s]=1;//标记入栈
    for(i=0;i<g.n;i++)
    {
        if(g.edgs[s][i]>0&&g.edgs[s][i]!=INF&&!visited[i]))
        {
            //未被访问的点
            if(i==e)//到达终点，需要打印路径
            {
                printf("第%d条路：",counts++);
                for(j=0;j<top;j++)
                {
                    printf("%s->",g.v[Stack[j]][Stack[j+1]];
                    if(j<top-1)
                    {
                            dis=dis+g.edgs[Stack[j]][Stack[j+1]];
                    }
                    dis=dis+g.edgs[Stack[top-1]][e];//加到终点
                    printf("%s\n",g.v[e].name);//打印
                    printf("总长度是：%dm\n\n",dis);//长度
                }
            }
            else
            {
                Dfs_allpath(i,e);
                top--;
                visited[i]=0;
            }
        }
    }
}

void Beatpath_Multispot()//最佳路径
{
}

void Dis_menu()//打印菜单
{
    printf("\n");
    printf("     ***********欢迎使用广州科技职业技术大学导游查询系统***********\n\n");
    printf("     *****    1.广科大景点信息查询          **********\n");
    printf("     *****    2.两景点之间最短路径查询      **********\n");
    printf("     *****    3.两景点之间所有路径查询      **********\n");
    printf("     *****    4.多景点访问路线查询          *********\n");
    printf("     *****    5.退出系统                    ***********\n");
    printf("     *************************************************\n");
    return;
}

void Dis_map()//打印地图
{
    printf("                                  *广科大校区景点地图一览*\n\n");
    printf("                                                       (10)七教                \n");
    printf("                   (6)五教           (9)三教                ◎----------|                  \n");
    printf("                      ◎                 ◎-----------------|           |        \n");
    printf("                      |------------------|------------------|           |                        \n");
    printf("                 (5)一教         (7)二教 |                  |-----------◎     \n");
    printf("                    ◎                     ◎     (13)广科湖|         (12)四教            \n");
    printf("      (4)校门◎------|---------------------|--------◎      |            |      \n");
    printf("              |      |                     |         |     ◎------------| \n");
    printf("              |      |                     |        (11)操场     \n");
    printf("              |      |                     ◎           |       \n");
    printf("              ◎1号学生公寓            (8)图书馆        |                      \n");
    printf("              |-------------------------------|         |       \n");
    printf("              |                               |---------(3)东餐厅 \n");
    printf("              |                                            ");
    printf("              |                                           \n");
    printf("              ◎2号学生公寓                                            \n\n");
}

int main()//主函数
{
    int i,n;
    int start,ens;
    Creat_vertex();
    Creat_maps();
    Dis_maps();
    while(1)
    {
        Dis_menu();
        printf("请输入需要操作的指令：\n");
        scanf("%d",&n);
        getchar();
        if(n<1||n>5)
        {
            printf("输入有误，请重新输入\n");
            continue;
        }
        else
        {
            if(n==1)
            {
                Search_info();
            }
            else
            {
                if(n==2)
                {
                    Dis_maps();
                    printf("请输入起点的景点：\n");
                    scanf("%d",&start);
                    printf("请输入终点的景点：\n");
                    scanf("%d",&ends);
                    Floyd();
                    printf("从%s到%s最短距离是：%d\n",g.v[start-1].name,g.v[ends-1].name);
                    printf("%s->",g.v[start-1].name);
                    Floyd_print(start,ends-1);
                    printf("%s\n",g.v[[ends-1].name);
                }
                else
                    if(n==3)
                    {
                        Dis_maps();
                        counts=1;
                        printf("请输入起点的景点：\n");
                        scanf("%d",&start);
                        printf("请输入终点的景点：\n");
                        scanf("%d",&ends);

    
    
    
    return 0;
}
