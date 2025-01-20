//--------------------------------------------------------
//程序描述：可以实现任意两个数的加减乘除运算，输入输出
//	均为int类型
//作者：王靳朝
//时间：2023年5月16日
//输入样例：UI界面显示之后，用户根据提示选择需要操作的类型
//	例如，选择4号为除法运算，根据提示输入x=7，y=3
//	运行结果之后显示商为2，余数为1.
//	用户按下C之后模拟计算器清0，开始重新运算
//调试工具：Xshell7 华为服务器
//说明：无
//--------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
void menu()
{
	printf("|--------计算器--------|\n");
	printf("|-------*1.Add*--------|\n");
	printf("|-------*2.Sub*--------|\n");
	printf("|-------*3.Mul*--------|\n");
	printf("|-------*4.Div*--------|\n");
	printf("|-------*0.Exit*-------|\n");
}

int  add(int w0,int w1);
int  sub(int w0,int w1);
int  mul(int w0,int w1);
extern div_t  div(int w0,int w1);

int main()
{
	int x,y,z,a;
	char c;
	menu();
	do
	{
		printf("Please select the operation type\n");
		scanf("%d",&a);
		if(a == 0)
		{
			printf("Exit\n");
			return 0;
		}
		printf("Please enter the number of operands\nx=");
		scanf("%d",&x);
		printf("y=");
		scanf("%d",&y);

		switch (a)
		{
			case 1:
				printf("x+y=%d\n",add(x,y));
				break;
			case 2:
				printf("x-y=%d\n",sub(x,y));
				break;
			case 3:
				printf("x*y=%d\n",mul(x,y));
				break;
			case 4:
				if (y != 0)
				{
					printf("The quotient of x/y is %d\n",div(x,y));
					printf("The remainder of x/y is %d\n",x-(x/y)*y);
					break;
				}
				else
				{	
					printf("Error!Please check the number of operands!\n");
				}
				default:
				printf("Invaild operation\n");
				break;
		}

		printf("Please Press 'C' to clear,press others to exit:\n");
		scanf(" %c",&c);
	}while(c == 'C');
	return 0;
}
