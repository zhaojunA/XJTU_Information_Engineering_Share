#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int num;
    struct Node *next;
}node;

void add(node**Head,int number);
void print(node *Head);
void fre(node *Head);
void reverse(node **Head);

int main()
{
    int number,n,i;
    node *head=NULL;
    scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&number);
		add(&head, number);
	}
    print(head);
    printf("\n");
    reverse(&head);
    print(head);
    fre(head);
	return 0;
}

//使用尾插法添加结点
void add(node**Head, int number)
{
    node *p=(node*)malloc(sizeof(node));//p指向头节点 
    node *last = *Head;//last时刻指向当前最后的节点 
    p->num = number;
    p->next = NULL;

    if(last)
	{
        while(last->next) 
		{
            last=last->next;
        }
        last->next=p;
    }
    else 
	{
        *Head=p;//要改变一个指针就要向函数中传入指针的指针，所以参数用了指向指针的指针 
    }
}

void print(node *Head)
{
    node *p=Head;
    while (p) 
	{
        printf("%d ",p->num);
        p=p->next;
    }
}

void fre(node *Head) 
{
    node *p=Head,*q;
    while(p) 
	{
        q=p;
        p=p->next;
        free(q);
    }
}

void reverse(node **Head)
{
    node *pre=*Head,*cur,*rear,*p=*Head;

    if (pre==NULL||pre->next==NULL)
        return ; 
    cur=pre->next;

    while(cur) 
	{
        rear=cur->next;
        cur->next=pre;
        pre=cur;
        cur=rear;
    }
    p->next=NULL;//实现逆置后让原来的头结点也就是现在的尾结点的next指针指向ＮＵＬＬ
    *Head=pre;
}
