#include<stdio.h>
int main()
{
    int x,score;
    printf("请输入成绩：");
    scanf_s("%d", &score);
    x = score / 10;
    if (score < 0 && score>100)
    printf("非法输入");
    else
        switch(x)
        {
        case 10:case 9:printf("A"); break;
        case 8:printf("B"); break;
        case 7:printf("C"); break;
        case 6:printf("D"); break;
        case 5:case 4:case 3:case 2:case 1:case 0:printf("E"); break;
        default:printf("非法输入");
        }
}
