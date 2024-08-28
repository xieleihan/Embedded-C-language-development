#include<stdio.h>

int a[101],n;

void quicksort(int left,int right)
{
    //算法描述
    //1、需要两个游标
    //2、需要把数组中的第一个值作为参考值
    //3、发生交换（两个游标碰面）
    //4、递归调用

    int i,j,temp,t;
    if(left>right)
    {
    return;
    }
    temp=a[left];
    i=left;
    j=right;
    while(i!=j)
    {
    //从右到左
    while(a[j]>=temp&&i<j)
    j--;
    while(a[j]<=temp&&i<j)
    i++;
    if(i<j)
    {
    t=a[i];
    a[i]=a[j];
    a[j]=t;
    }
    }
    //碰面后
    a[left]=a[i];
    a[i]=temp;
    //left是什么位置，i-1是什么位置？
    quicksort(left,i-1);
    quicksort(i+1,right);
}

int main()
{
    int i,j,t;
    printf("请输入数组长度");
    scanf("%d",&n);
    printf("请输入数组内容");
    for(i=1;i<=n;i++)
    {
    scanf("%d",&a[i]);
    }
    quicksort(1,n);
    printf("排序后");
    for(i=1;i<=n;i++)
    {
    printf("%d",a[i]);
    }
    getchar();
    return 0;
}
