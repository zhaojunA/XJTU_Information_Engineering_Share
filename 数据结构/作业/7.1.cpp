#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50
typedef char ElemType;
typedef struct node
{
    ElemType data;
    struct node *lchild;
    struct node *rchild;
}BTNode;//����ṹ�� 

typedef struct
{
	BTNode *data[MaxSize];
	int front,rear;
}SqQueue;//������� 

void InitQueue(SqQueue *&q)//���г�ʼ�� 
{
	q=(SqQueue *)malloc(sizeof(SqQueue));
	q->front=q->rear=0;
}

bool QueueEmpty(SqQueue *q)//�����п� 
{
	return(q->front==q->rear);
}

bool enQueue(SqQueue *&q,BTNode *b)//��� 
{
	if(q->front==(q->rear+1)%MaxSize)//�ж���
	  return false;
    q->rear=(q->rear+1)%MaxSize;
	q->data[q->rear]=b;
    return true;

}

bool deQueue(SqQueue *&q,BTNode *&b)//���� 
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
 	if(ch=='^') b=NULL; //�ݹ��������
   	else 
	{//�Ƚ�������㣬�ڵݹ齨����������
		b=(BTNode *)malloc(sizeof(BTNode)); 			
		if(!b) return false; //mallocʧ�ܣ�����NULL,��ֹҰָ�� 
		b->data=ch;
		CreateBTree(b->lchild);
		CreateBTree(b->rchild);
	}
      return true;
}

bool PreOrder(BTNode *b)//������� 
{
	if(b!=NULL)//�ݹ���ֹ 
	{
		printf("%c",b->data);
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

void IsCompleteTree(BTNode *b)//������ 
{   BTNode *p;
    SqQueue *qu;
    int flag=0; 
    InitQueue(qu);	//���塢��ʼ������
    enQueue(qu,b);			//��������
    while(!QueueEmpty(qu))		//�Ӳ�Ϊ��ѭ��
    {
    	if(p->lchild==NULL&&p->rchild!=NULL)  //�����Ϊ�յ��Ҷ��Ӳ���ֱ�ӽ��� 
    	{	printf(" N");
    		return;
		}
		else if((p->lchild!=NULL&&p->rchild==NULL)||(p->lchild==NULL&&p->rchild==NULL)) //��¼���һ���ڲ��ڵ�,���˺��ٳ��ַ�Ҷ�ӽڵ������ѭ�� 
		{	flag=1;
	  	}
	  	deQueue(qu,p);		//���ӡ����ʽ��p
	  	if(flag==1) 
	  	{
	  		if(p->lchild!=NULL||p->rchild!=NULL)
	  		{printf(" N");  return;
			}
		}
		printf("%c",p->data);
      	if(p->lchild!=NULL)    //������ʱ�������
	  		enQueue(qu,p->lchild);
      	if(p->rchild!=NULL)    //���Һ���ʱ�������
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
