#include<malloc.h>
#include<stdio.h>
typedef struct node                   
{
    int data;
    struct node *next;
}NODE;

NODE *create()                        
{
    NODE *head,*q,*p;                
    char ch;
    int a;
    head=(NODE*)malloc(sizeof(NODE)); 
    q=head;
    ch='*';
    printf("\nInput the list :");
    while(ch!='?')                    
    {
    scanf("%d",&a);                  
    p=(NODE*)malloc(sizeof(NODE));
        p->data=a;
        q->next=p;
        q=p;
        ch=getchar();                    
    }
    q->next=NULL;
    return(head);                        
}

NODE *locate(NODE *head,int x)     
{
    NODE *p;
    p=head->next;
    while((p!=NULL)&&(p->data!=x)) 
        p=p->next;                 
    return(p);
}

void main()                             
{
int y,i=1;
NODE *a,*b;
a=create();
printf("Input x: ");
scanf("%d",&y);
b=locate(a,y);
if(b!=NULL)
{   printf("find:");
    printf("%5d\n",b->data);  
    
}
else
    printf("error");             
} 
