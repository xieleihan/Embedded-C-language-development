# include <stdio.h>
# include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 4

typedef int Status;

typedef struct
{
	char carName[20];
}Car;


typedef struct
{
	Car * base;
	int front;
	int rear;
} SqQueue;


Status InitQueue(SqQueue *Q)
{
	Q->base = (Car *)malloc(MAXSIZE*sizeof(Car));
	if(!Q->base)
    {
		printf("�ڴ�������޷����ٿռ䣡");
		return ERROR;
	}

	Q->front=Q->rear=0;
	printf("����վ������ʼ���ɹ���\n");
	return 0;
}

Status EnQueue(SqQueue *Q, Car car)
{

	if((Q->rear+1)%MAXSIZE==Q->front)
    {
		printf("��ǰ���г�����������\n");
		return ERROR;
	}

	Q->base[Q->rear] = car;
	Q->rear = (Q->rear+1)%MAXSIZE;
	return OK;
}

Status DeQueue(SqQueue *Q, Car * car)
{

	if(Q->front==Q->rear)
    {
		printf("��ǰ�����޳�����\n");
		return ERROR;
	}
	*car = Q->base[Q->front];

	Q->front = (Q->front+1)%MAXSIZE;
	return OK;
}

void TraverseQueue(SqQueue Q)
{
	int front=Q.front;
	while(front != Q.rear)
    {
		printf("%s\n",Q.base[front].carName);
		front=(front+1)%MAXSIZE;
	}
}
int main(void)
{
	SqQueue Come,Work,Out;
	int option;
	int loop=1;
	Car car;
	do
    {

        printf("1.初始化加油站场景\n");
        printf("2.指挥车辆进入加油站入口队列\n");
        printf("3.指挥车辆进入加油队列\n");
        printf("4.指挥车辆驶向加油站出口队列\n");
        printf("5.指挥车辆驶离加油站出口队列\n");
        printf("6.查看当前入口排队车辆\n");
        printf("7.查看当前加油排队车辆\n");
        printf("8.查看当前出口排队车辆\n");
        printf("9.退出模拟加油站系统\n");
        printf("请输入你的操作：");

        switch(option)
        {
			case 1:
				InitQueue(&Come);
				InitQueue(&Work);
				InitQueue(&Out);
				break;
			case 2:
				printf("�����������ڶ��еĳ����ĳ��ƺţ�\n");
				scanf("%s",car.carName);
				EnQueue(&Come,car);
				break;
			case 3:
				if((Work.rear+1)%MAXSIZE !=Work.front){
					if(Come.rear != Come.front){
						DeQueue(&Come,&car);
						EnQueue(&Work,car);
						printf("�����ѽ�����Ͷ���\n");
					}
					else{
						printf("��ʱû�еȴ�������Ͷ��еĳ���\n");
					}
				}
				else{
					printf("������ʱ�޷�������Ͷ���,��Ҫ�����ȴ�\n");
				}
				break;
			case 4:
				if((Out.rear+1)%MAXSIZE !=Out.front){
					if(Work.rear != Work.front){
						DeQueue(&Work,&car);
						EnQueue(&Out,car);
						printf("�����ѽ�����ڶ���\n");
					}
					else{
						printf("��ʱû�еȴ�������ڶ��еĳ���\n");
					}
				}
				else{
					printf("������ʱ�޷�������ڶ���,��Ҫ�����ȴ�\n");
				}
				break;
			case 5:
				if(DeQueue(&Out,&car))
					printf("ʻ�����վ���ڶ��еĳ������ƺţ�%s\n",car.carName);
				break;
			case 6:
				printf("��ǰ����Ŷӳ����У�\n");
				TraverseQueue(Come);
				break;
			case 7:
				printf("��ǰ���ͳ����У�\n");
				TraverseQueue(Work);
				break;
			case 8:
				printf("��ǰ�����Ŷӳ����У�\n");
				TraverseQueue(Out);
				break;
			case 9:
				loop = 0;
				printf("���˳���ģ�����վϵͳ......");
		}
		printf("\n\n");
	} while(loop);
	return 0;
}

