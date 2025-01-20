#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50
#include <iostream>
#include <algorithm>
using namespace std;
typedef char ElemType;
typedef struct BTNode
{
    ElemType data;
    struct BTNode *lchild;
    struct BTNode *rchild;
}BNode;//定义结构体 

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

void InOrder(BTNode *b)//中序遍历 
{  if (b!=NULL)  
   {  
      InOrder(b->lchild);
      printf("%c",b->data);//访问根结点
      InOrder(b->rchild);
   }
}

void ReverseLeftRightChild(BTNode *&b)
{
    // 如果是叶子节点，则递归结束
    if (b== NULL)
    {
        return;
    }
    swap(b->lchild, b->rchild); // 直接使用swap交换函数交换指针；
    ReverseLeftRightChild(b->lchild);
    ReverseLeftRightChild(b->rchild);
}

int main()
{
	BTNode *BNode;
	CreateBTree(BNode);
	InOrder(BNode);
	printf("\n");
	ReverseLeftRightChild(BNode);
	InOrder(BNode);
}
