//------------------------------------------------------
//程序描述：实现(x+y)*8/2运算式，定义输入输出均为int类型
//作者：王靳朝
//时间：2023年5月16日
//输入格式样例：
//	运行程序后，从键盘输入x=12，y=34，回车之后程序运行
//	将结果显示在屏幕上
//调试工具：Xshell7 华为云服务器
//说明：无
//------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x,y,z;
	printf("Please enter x=");
	scanf("%d",&x);
	printf("Please enter y=");
	scanf("%d",&y);
	printf("(x+y)*8/2=%d\n",calculate(x,y));
	return 0;
}
