#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50
typedef char ElemType;
typedef struct node
{
    ElemType data;
    struct node *lchild;
    struct node *rchild;
}BTNode;//定义结构体 

typedef struct
{
	BTNode *data[MaxSize];
	int front,rear;
}SqQueue;//定义队列 

void InitQueue(SqQueue *&q)//队列初始化 
{
	q=(SqQueue *)malloc(sizeof(SqQueue));
	q->front=q->rear=0;
}

bool QueueEmpty(SqQueue *q)//队列判空 
{
	return(q->front==q->rear);
}

bool enQueue(SqQueue *&q,BTNode *b)//入队 
{
	if(q->front==(q->rear+1)%MaxSize)//判队满
	  return false;
    q->rear=(q->rear+1)%MaxSize;
	q->data[q->rear]=b;
    return true;

}

bool deQueue(SqQueue *&q,BTNode *&b)//出队 
{
	if(q->front==q->rear)
	  return false;
    q->front=(q->front+1)%MaxSize;
	b=q->data[q->front];
    return true;
}

bool CreateBTree(BTNode *&b)
{	char ch;
	scanf("%c",&ch);
 	if(ch=='^') b=NULL; //递归结束条件
   	else 
	{//先建立根结点，在递归建立左右子树
		b=(BTNode *)malloc(sizeof(BTNode)); 			
		if(!b) return false; //malloc失败，返回NULL,防止野指针 
		b->data=ch;
		CreateBTree(b->lchild);
		CreateBTree(b->rchild);
	}
      return true;
}

bool PreOrder(BTNode *b)//先序遍历 
{
	if(b!=NULL)//递归终止 
	{
		printf("%c",b->data);
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

void IsCompleteTree(BTNode *b)//逐层遍历 
{   BTNode *p;
    SqQueue *qu;
    int flag=0; 
    InitQueue(qu);	//定义、初始化队列
    enQueue(qu,b);			//根结点入队
    while(!QueueEmpty(qu))		//队不为空循环
    {
    	if(p->lchild==NULL&&p->rchild!=NULL)  //左儿子为空但右儿子不空直接结束 
    	{	printf(" N");
    		return;
		}
		else if((p->lchild!=NULL&&p->rchild==NULL)||(p->lchild==NULL&&p->rchild==NULL)) //记录最后一个内部节点,若此后再出现非叶子节点则结束循环 
		{	flag=1;
	  	}
	  	deQueue(qu,p);		//出队、访问结点p
	  	if(flag==1) 
	  	{
	  		if(p->lchild!=NULL||p->rchild!=NULL)
	  		{printf(" N");  return;
			}
		}
		printf("%c",p->data);
      	if(p->lchild!=NULL)    //有左孩子时将其进队
	  		enQueue(qu,p->lchild);
      	if(p->rchild!=NULL)    //有右孩子时将其进队
	  		enQueue(qu,p->rchild);
    }
	printf(" Y");
}

int main()
{
	node *BTNode;
	CreateBTree(BTNode);
	PreOrder(BTNode);
	printf("\n");
	IsCompleteTree(BTNode);
	return 0;
}
