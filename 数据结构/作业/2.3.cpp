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

//ʹ��β�巨��ӽ��
void add(node**Head, int number)
{
    node *p=(node*)malloc(sizeof(node));//pָ��ͷ�ڵ� 
    node *last = *Head;//lastʱ��ָ��ǰ���Ľڵ� 
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
        *Head=p;//Ҫ�ı�һ��ָ���Ҫ�����д���ָ���ָ�룬���Բ�������ָ��ָ���ָ�� 
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
    p->next=NULL;//ʵ�����ú���ԭ����ͷ���Ҳ�������ڵ�β����nextָ��ָ��Σգ̣�
    *Head=pre;
}
