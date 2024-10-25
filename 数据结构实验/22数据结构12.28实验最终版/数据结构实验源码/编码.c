#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 1000
#define MAXBIT 30 

typedef struct
{
    char ch[2];
    int quan; 
    char code[MAXBIT];
} Link;

typedef struct
{
	int weight;
	int parent;
	int Lchild, Rchild;
} Tree;

int ls, ts, fs;                       
Link link[MAXSIZE];  //顺序表 

//文件处理模块 
void initLink();
int file_size(char* filename);
int countfile(char* filename);

//生成码本文件模块（哈夫曼树编码） 
void initTree(Tree tree[]);
void selectmin(int k, int *p1, int  *p2, Tree tree[]);
void HuffmanTree(Tree tree[]);
void HuffmanCode(Tree tree[]);
void show();
void createcTable();

//生成码流文件模块 
void ctob(char a[], char str[]);
void btoc(char str[], FILE* fw);
int Encode();

int main()
{
	//生成码本文件"cTable.txt" 
	initLink();
	countfile("SourceDoc.txt");
	ts = 2 * ls - 1;
	Tree tree[ts];
	initTree(tree);
	HuffmanTree(tree);
	HuffmanCode(tree);
	show();
	createcTable();
	
	//生成码流文件"encode.txt"
	Encode();
	
	return 0;
}

//文件处理模块 
void initLink()  //顺序表初始化 
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

int countfile(char* filename)
{
	int i, j, k, n = 0;
	char a[2];
	FILE *fp=fopen(filename, "rb");  
    if(!fp) return -1;
    file_size(filename);
	for (i = 0; i < fs; i++)
	{
		//printf("%d/%d\n", i, fs); 
		fread(a, 1, 1, fp);
		if (a[0] < 0 && i < fs - 1)
		{
			fread(a + 1, 1, 1, fp);
			i++;
		}
		else a[1] = '\0';
		//printf("%s", a);
		k = 0;
		for (j = 0; j < n; j++)
		{
			if (link[j].ch[0] == a[0] && link[j].ch[1] == a[1])
			{
				k = 1;
				link[j].quan++;
				break;
			}
		}
		if (k == 0)
		{
			link[n].ch[0] = a[0];
			link[n].ch[1] = a[1];
			link[n++].quan++;
			//printf("n = %d\n", n);
		}
	}
	fclose(fp);
	ls = n;
	return 0;
}

//生成码本文件模块（哈夫曼树编码）
void initTree(Tree tree[])   //顺序表实现哈夫曼树 
{
	int i, j;
	for (i = 0; i < ts; i++)      
	{	
		tree[i].weight = 0;
		tree[i].Lchild = -1;
		tree[i].parent = -1;
		tree[i].Rchild = -1;
	}
}

void selectmin(int k, int *p1, int  *p2, Tree tree[])    //起到了优先队列的作用 
{
	*p1 = *p2 = 0;
	int small1, small2;
	small1 = small2 = fs;
	int i;
	for (i = 0; i < k; i++)
	{
		if (tree[i].parent == -1 )
		{
			if (tree[i].weight < small1)
			{
				small2 = small1;
				small1 = tree[i].weight;
				*p2 = *p1;
				*p1 = i;
			}
			else if ( tree[i].weight < small2 )
			{
				small2 = tree[i].weight;
				*p2 = i;
			}
		}
	}
}

void HuffmanTree(Tree tree[])    //建树 
{
	int i, j, p1, p2;
	char a;
	for (i = 0; i < ls; i++)
		tree[i].weight = link[i].quan;
	for  (i = ls; i < ts; i++)  
	{
		selectmin(i, &p1, &p2, tree);
		tree[p1].parent = i;
		tree[p2].parent = i;
		tree[i].Lchild = p1;
		tree[i].Rchild = p2;
		tree[i].weight = tree[p1].weight + tree[p2].weight;
	}
}

void HuffmanCode(Tree tree[])  //得到编码 
{
	int i, j, c, k, p;
	for (i = 0; i < ls; i++)
	{
		k = MAXBIT;
		c = i;                    
		p = tree[c].parent;            
		while (p != -1)
		{
			k--;
			if (tree[p].Lchild == c)
				link[i].code[k] = '0';      
			else link[i].code[k] = '1';        
			c = p;                                    
			p = tree[c].parent;
		}
		for (j = 0; j < MAXBIT - k; j++)
			link[i].code[j] = link[i].code[j + k];
		for (j = MAXBIT - k; j < MAXBIT; j++)
			link[i].code[j] = '\0';
	}
}

void show()
{
	int i;
	for (i = 0; i < ls; i++){
		if(link[i].ch[0]==32){
			printf("Space : 个数 %d\t|频率 %f\t|编码 %s\n", link[i].quan, (float)link[i].quan / (float)fs, link[i].code);
		}else if(link[i].ch[0]==10){
			printf("Enter : 个数 %d\t|频率 %f\t|编码 %s\n", link[i].quan, (float)link[i].quan / (float)fs, link[i].code);
		}else if(link[i].ch[0]==9){
			printf("Tab : 个数 %d\t|频率 %f\t|编码 %s\n", link[i].quan, (float)link[i].quan / (float)fs, link[i].code);
		}else{
			printf("%s : 个数 %d\t|频率 %f\t|编码 %s\n", link[i].ch, link[i].quan, (float)link[i].quan / (float)fs, link[i].code);
		}	
	}
}

void createcTable()//生成码本文件 
{
	FILE* fp = fopen("cTable.txt", "wb");
	int i, k;
	fwrite(&ls, sizeof(int), 1, fp);
	for (i = 0; i < ls; i++)
	{
		fwrite(link[i].ch, 1, 2, fp);
		k = strlen(link[i].code);
		fwrite(&k, sizeof(int), 1, fp);
		fwrite(link[i].code, 1, k, fp);
	}
	fclose(fp);
}

//生成码流文件模块 
void ctob(char a[], char str[])    //编码改比特 
{
	int i, k = 0;
	for (i = 0; i < ls; i++)
	{
		if (a[0] == link[i].ch[0] && a[1] == link[i].ch[1])
		{
			strcat(str, link[i].code);
			k = 1;
			break;
    	}
    }
    if (k == 0) printf("Cannot find %d %d\n", a[0], a[1]);
}

void btoc(char str[], FILE* fw)   //八比特合成一个字节 
{
	char c = 127;
	int minus = 1, i, j, l;
	if (str[0] == '0') minus = 0;
	for (i = 1; i < 8; i++)
	{
		if (str[i] == '0')
		{
			l = 1;
			for (j = 0; j < 7 - i; j++) l = l * 2;
			c -= l;
		}
	}
	if (minus == 1 && c != 0 ) c = -c;
	if (minus == 1 && c == 0 ) c = -128;
   	fwrite(&c, 1, 1, fw);
   	l = strlen(str);
    for (i = 0; i < l - 8; i++) str[i] = str[i + 8];
    for (i = l - 8; i < l; i++) str[i] = '\0';
}

int Encode()
{
	char a[2], str[2 * MAXBIT], rest;
	int i;
	for (i = 0; i < 2 * MAXBIT; i++) str[i] = '\0';
	
	FILE* fr = fopen("SourceDoc.txt", "rb");
	if (!fr) return -1;
	FILE* fw = fopen("Encode.txt", "wb");
	for (i = 0; i < fs; i++){
		fread(a, 1, 1, fr);
		if (a[0] < 0 && i < fs - 1)
		{
			fread(a + 1, 1, 1, fr);
			i++;
		}
		else a[1] = '\0';
		ctob(a, str);
		while (strlen(str) >= 8) btoc(str, fw);
		//printf("进度：%.2f%%\n", (float)(i + 1) / (float)fs * 100);
	}
	if (strlen(str) > 0)
	{
		rest = 8 - strlen(str);
		for (i = 8 - rest; i < 8; i++) str[i] = '0';
		btoc(str, fw);
	}
	else rest = 0;
	printf("rest : %d\n", rest);
    fwrite(&rest, 1, 1, fw);
	fclose(fw);
	fclose(fr);
    return 0;
}
