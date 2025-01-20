#include <stdio.h>
#include <stdlib.h>
#define MaxSize 11
typedef int ElemType;
typedef struct 
{
    ElemType data[MaxSize];
    int front,rear;
}SqQueue;//定义结构体 

bool InitQueue(SqQueue *&q)
{
	q=(SqQueue *)malloc(sizeof(SqQueue));
	if(!q) return false;
	q->front=q->rear=0;
	return true;
}//初始化 

void DestroyQueue(SqQueue *&q)
{
	free(q);
}//销毁 

bool QueueEmpty(SqQueue *q)
{
	return(q->front==q->rear);
}//判空 

bool enQueue(SqQueue *&q,ElemType e)
{
	if((q->rear+1)%MaxSize==q->front)
	return false;
	q->rear=(q->rear+1)%MaxSize;
	q->data[q->rear]=e;
	return true;
}//入队 

bool deQueue(SqQueue *&q,ElemType &e)
{
	if(q->front==q->rear)
		return false;
	q->front=(q->front+1)%MaxSize;
	e=q->data[q->front];
	return true;
}//出队 

void ReverseQueue(SqQueue *&q)
{
	int i,j,a[MaxSize];
	int len=((q->rear-q->front+MaxSize)%MaxSize);
	ElemType e;
	for(i=0;i<len;i++)
	{
		deQueue(q,e);
		a[i]=e;
	}
	q->front=q->rear=0;
  	for(j=len-1;j>=0;j--)
    {
		q->rear=(q->rear+1)%MaxSize;
		q->data[q->rear]=a[j];
	}
}//逆置 

int main()
{
	int n,a[10],i,flag=0;	
	SqQueue *sq;	ElemType e,f,g;
	if(!InitQueue(sq)) printf("初始化失败。");
	else 
	{
		InitQueue(sq);
		scanf("%d",&n);
		for(i=0;i<n;i++)
		{
			scanf("%d",&e);
			if(e>=0) enQueue(sq,e);
			else {deQueue(sq,f);flag++;}
		}
		for(i=0;i<n-2*flag;i++)
		{
			deQueue(sq,e);
			printf("%d ",e);
			enQueue(sq,e);
		}
		ReverseQueue(sq);
		printf("\n");
		for(i=0;i<n-2*flag;i++)
		{
			deQueue(sq,g);
			printf("%d ",g);
		}
		DestroyQueue(sq);
	}
	return 0;
}
