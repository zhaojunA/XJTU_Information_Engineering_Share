#include<stdio.h>
#include<stdlib.h> 
#define MAXSIZE 100

typedef struct List {
	int data[MAXSIZE];
	int length;
} *sqlist;            //sqlist类型的指针 

sqlist LA,LB,LC;
int i;
int main()
{
	int * pa,* pb,* pc,* LA_LAST,* LB_LAST;
	LA = (sqlist)malloc(sizeof(struct List));
	scanf("%d",&LA->length);
	for (i=0;i<LA->length;i++)
	{
		scanf("%d",&LA->data[i]);
	} 
	pa=LA->data;
	LA_LAST=pa+LA->length-1;
	
	LB = (sqlist)malloc(sizeof(struct List));
	scanf("%d",&LB->length);
	for (i = 0;i<LB->length;i++)
	{ 
		scanf("%d",&LB->data[i]);
	} 
	pb=LB->data;
	LB_LAST=pb+LB->length-1;
	
	LC=(sqlist)malloc(sizeof(struct List)); 
	LC->length=LA->length+LB->length;
	pc=LC->data;

	while(pa<=LA_LAST&&pb<=LB_LAST)
	{
		if (*pa<=*pb)
		{
			*pc=*pa;
			pc++;pa++;
		}
		                                     
		else
		{
			*pc=*pb;
			pc++;pb++;                       /*核心算法区域*/ 
		}
	}
		
	while (pa<=LA_LAST)
	{
		*pc=*pa;
		pc++;pa++;
	}
		
	while (pb<=LB_LAST)
	{
		*pc=*pb;
		pc++;pb++;
	}
	
	for (i = 0;i<LC->length;i++)
	{printf("%d ",LC->data[i]);
	}
	return 0;
} 
