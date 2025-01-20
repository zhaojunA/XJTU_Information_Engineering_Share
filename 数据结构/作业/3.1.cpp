#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct linknode
{
    ElemType data;
    struct linknode *next,*prior;
}LinkStNode;

void initStack(LinkStNode *&s)
{
	s=(LinkStNode*)malloc(sizeof(LinkStNode));
	s->next=NULL;
	s->prior=NULL;
}//初始化 

void DestroyStack(LinkStNode *&s)
{
	LinkStNode *pre=s,*p=s->prior;
	while(p!=NULL)
	{
		free(pre);
		pre=p;
		p=pre->prior;
	}
	free(pre);
}//销毁 

bool Push(LinkStNode *&s,ElemType e)
{
	LinkStNode *p,*head;
	p=(LinkStNode*)malloc(sizeof(LinkStNode));
	p->data=e;
	s->next=p;
	p->prior=s;
	s=p;//链尾为栈顶用尾插 
	return true;
}//进栈 

bool Pop(LinkStNode *&s,ElemType &e)
{
	LinkStNode *p;
	if(s->next==NULL)
		return false;
	p=s;
	e=s->data;
	s=s->prior;
	free(p);
	return true;
}//出栈 

int main()
{
	LinkStNode *st,*head;
	ElemType str[50],e; int i,j,n; char c;
	if(!initStack(st)) return 0;
	else
	{
		head=st;
    	gets(str);
		for(i=0;str[i]!='#';i++)
		{
			if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
			{
				Push(st,str[i]);
			}
		}
		for(j=0;str[j]!='#';j++)
		{
			if(str[j]>='0'&&str[j]<='9')
			{
				Push(st,str[j]);
			}
		}
		st->next=head;
		while(st!=head)
		{	Pop(st,e);
			printf("%c",e);
		}
		DestroyStack(st);
		}
		return 0;
}
