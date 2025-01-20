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
}BNode;//����ṹ�� 

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

void InOrder(BTNode *b)//������� 
{  if (b!=NULL)  
   {  
      InOrder(b->lchild);
      printf("%c",b->data);//���ʸ����
      InOrder(b->rchild);
   }
}

void ReverseLeftRightChild(BTNode *&b)
{
    // �����Ҷ�ӽڵ㣬��ݹ����
    if (b== NULL)
    {
        return;
    }
    swap(b->lchild, b->rchild); // ֱ��ʹ��swap������������ָ�룻
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
