#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 1000
#define MAXBIT 30

typedef struct{
    char ch[2];
    int quan;
    char code[MAXBIT];
} Link;

int ls, fs;
Link link[MAXSIZE];   //顺序表 

//文件处理模块
void initLink();
int file_size(char* filename);
int GetcTable();

//生成解码文件模块 
void show();
void ctob(char a, char str[]);
void btoc(char str[], FILE* fw);
int Discode();

//检测正确性（由于源文件被删除，暂不使用） 
int test(); 

int main(){
	//生成解码文件"discode.txt" 
	initLink();
	GetcTable();
	//show();
	file_size("Encode.txt");
	Discode();
	
	//检测正确性
	//test(); 
	
	return 0;
}

//文件处理模块
void initLink()
{
	int i, j;
	ls = 0;
	for (i = 0; i < MAXSIZE; i++)
	{
		link[i].ch[0] = '\0';
		link[i].ch[1] = '\0';
		link[i].quan = 0;
		for (j = 0; j < MAXBIT; j++)
			link[i].code[j] = '\0';
	}
}

int file_size(char* filename)  
{
	fs = 0;
	FILE *fp = fopen(filename, "r");  
    if(!fp) return -1;  
    fseek(fp, 0L, SEEK_END);  
    fs = ftell(fp);  
    fclose(fp);
    return 0;  
}

//生成解码文件模块 
int GetcTable()
{
	int i, k;
	char a, str[MAXSIZE];
	FILE* fp = fopen("cTable.txt", "rb");
	if (!fp) return -1;
	fread(&k, sizeof(int), 1, fp);
	ls = k;
	for (i = 0; i < ls; i++){
		fread(link[i].ch, 1, 2, fp);
		fread(&k, sizeof(int), 1, fp);
		fread(link[i].code, 1, k, fp);
	}
	close(fp);
	return 0;
}

void show()
{
	int i;
	for (i = 0; i < ls; i++)
		printf("%s : %s\n", link[i].ch, link[i].code);
}

void ctob(char a, char str[])
{
	int i;
	char asc[] = "00000000";
	if (a < 0)
	{
		asc[0] = '1';
		a = -a;
	}
	for (i = 7; i > 0; i--)
	{
		if (a % 2 == 1)
		{
			asc[i] = '1';
			a--;
		}
		a = a / 2;
	}
	strcat(str, asc);
}

void btoc(char str[], FILE* fw){
	int i, j, k = 1, l;
	while (k == 1 && strlen(str) > 0)
	{
		for (i = 0; i < ls; i++)
		{
			k = 1;
			if (strlen(str) >= strlen(link[i].code))
			{
				for (j = 0; j < strlen(link[i].code); j++)
				{
					if (link[i].code[j] != str[j])
					{
						k = 0;
						break;
					}
				}
			}
			else k = 0;
			if (k == 1){
				//printf("%s\n",link[i].ch);
				fputs(link[i].ch, fw);
				l = strlen(str);
				for (j = 0; j < l - strlen(link[i].code); j++)
					str[j] = str[j + strlen(link[i].code)];
				for (j = l - strlen(link[i].code); j < l; j++)
					str[j] = '\0';
				break;
			}
		}
	}
	//printf("reststr : %s\n", str);
}

int Discode()
{
	int i, l;
	char a, str[MAXBIT * 2], rest;
	for (i = 0; i < MAXBIT * 2; i++) str[i] = '\0';
	FILE* fr = fopen("Encode.txt", "rb");
	if (!fr) return -1;
	FILE* fw = fopen("Discode.txt", "wb");
	for (i = 0; i < fs - 2; i++)
	{
		fread(&a, 1, 1, fr);
		ctob(a, str);
		btoc(str, fw);
		//printf("进度：%.2f%%\n", (float)(i + 1) / (float)(fs - 1) * 100);
	}
	fread(&a, 1, 1, fr);
	ctob(a, str);
	fread(&rest, 1, 1, fr);
	l = strlen(str);
	for (i = 0; i < rest; i++) str[l - 1 - i] = '\0';
	btoc(str, fw);
	//printf("进度：100.00%%\n");
	fclose(fw);
	fclose(fr);
	return 0;
}

//检测正确性（由于源文件被删除，暂不使用） 
int test()
{
	int i;
	char a1[2], a2[2];
	FILE* fp1 = fopen("Source.txt", "rb");
	FILE* fp2 = fopen("Discode.txt", "rb");
	for (i = 0; i < fs; i++)
	{
		a1[0] = fgetc(fp1);
		a2[0] = fgetc(fp2);
		if (a1[0] != a2[0])
		{
			if (a1[0] < 0)
			{
				a1[1] = fgetc(fp1);
				a2[1] = fgetc(fp2);
				i++;
			}
			printf("第 %d 个字节处出错，原为‘%s’，现为‘%s’\n", i, a1, a2);
			char str[255];
			fgets(str, 255, fp1);
			puts(str);
			break;
		}
	}
	if (i >= fs) printf("解码文件与源文件相符\n");
	fclose(fp1);
	fclose(fp2);
	return 0;
} 
