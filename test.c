/*
功能：Huffman对文件进行编码和解码
时间：2014-11-24
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
//结点结构体
typedef struct Node
{
	unsigned char value;  //结点值
	int frequency;   //结点频数
	struct Node *Lchild;  //左儿子
	struct Node *Rchild;  //右儿子
};
 
//编码字符结构体
typedef struct
{
	unsigned char value;  //字符值
	char code[100];   //字符编码
	int frequency;   // 字符频数
	int codelen;   //字符编码长度
}HuffmanCode;
 
struct Node *root;  //哈弗曼树根节点
 
//读取文件统计各个字母出现频率，返回字符种数
//filename为文件名，*node为用于保存数据的数组
int count(char filename[],HuffmanCode *node)
{
	FILE *fp=fopen(filename,"rb");  //打开文件
	unsigned char now;  //读取的当前字符
	int num = 0; //字符种数
 
	fread(&now, sizeof(unsigned char), 1, fp); //读取字符
	while(!feof(fp)) //未读到文件尾
	{
		int i;
		//重复字符
		for (i = 0; i < num; i++)
		{
			if (now == node[i].value)
			{
				node[i].frequency++;
				break;
			}
 
		}
		//未重复字符
		if (i==num)
		{
			node[i].value = now;
			node[i].frequency=1;
			num++;
		}
		fread(&now, sizeof(unsigned char), 1, fp); //读取字符
	}
	fclose(fp);
	return num;
}
 
//构造Huffman树
//*node为用于保存数据的数组，n为字符种数
struct Node* buildHuffman(HuffmanCode *node, int n)
{
	struct Node **arr,*temp; //arr为造数用数组，temp为最终返回的树
	arr = (struct Node**)malloc(n*sizeof(struct Node));
 
	//初始化数组
	for (int i = 0; i < n; i++)
	{
		arr[i] = (struct Node*)malloc(sizeof(struct Node));
		arr[i]->value = node[i].value;
		arr[i]->frequency = node[i].frequency;
		arr[i]->Lchild = arr[i]->Rchild = NULL;
	}
 
	//建树
	for (int i = 0; i < n-1; i++)
	{
		int m1=-1, m2;  //最小的两个权值在数组中下标
		
		//将m1,m2指向头两棵树
		for (int j = 0; j < n; j++)
		{
			if (m1 == -1 && arr[j] != NULL)
			{
				m1 = j;
				continue;
			}
			if (arr[j] != NULL)
			{
				m2 = j;
				break;
			}
		}
		//比较权值大小,找到最小的两个
		for (int j = m2; j < n; j++)
		{
			if (arr[j]!=NULL && arr[j]->frequency < arr[m1]->frequency)
			{
				m2 = m1;
				m1 = j;
			}
			else if (arr[j] != NULL && arr[j]->frequency < arr[m2]->frequency)
				m2 = j;
		}
		//将两个权值最小的构成新树
		temp = (struct Node*)malloc(sizeof(struct Node));
		temp->Lchild = arr[m1];
		temp->Rchild = arr[m2];
		temp->frequency = arr[m1]->frequency + arr[m2]->frequency;
		temp->value = NULL;
		//将新树加入数组
		arr[m1] = temp;
		arr[m2] = NULL;
	}
	free(arr);
	return temp; //最终temp为树根
}
//Huffman编码
//*node为根节点，len为当前编码长度,*arr为用于保存数据的数组，num为字符种数
void codeByHuffman(struct Node *node,int len,HuffmanCode *arr,int num) 
{
	static char code[100];  //编码
 
	//左儿子不为空，编码为0
	if (node->Lchild != NULL)
	{
		code[len] = '0';
		code[len + 1] = '\0';
		codeByHuffman(node->Lchild, len+1,arr,num); //对左儿子调用此函数
	}
	//右儿子不为空，编码为1
	if (node->Rchild != NULL)
	{
		code[len] = '1';
		code[len + 1] = '\0';
		codeByHuffman(node->Rchild, len + 1, arr, num); //对右儿子调用此函数
	}
	//叶节点
	else
	{
		for (int i = 0; i < num; i++)
		{
			//将编码复制给数组里的元素
			if (arr[i].value == node->value)
			{
				strcpy(arr[i].code, code);
				arr[i].codelen = 0;
				for (int j = 0; arr[i].code[j] != '\0'; j++)
					arr[i].codelen++;
				return;
			}
		}
	}
}
//将文件内容转为Huffman编码
//sourceFile为原文件名，*arr为用于保存数据的数组，n为字符种数，aimFile为目标文件名
void writeCode(char sourceFile[],HuffmanCode *arr,int n,char aimFile[])
{
	FILE *fSource, *fAim; //原文件以及目标文件
	unsigned char now;//读取的当前字符
	unsigned char save = 0; //每次保存的一个字节长度
	int len = 0; //每次保存的一个字节已存了多少长度
	int totalLen = 0; //文件编码总长度
	int last;  //最后一次写入时的位数
 
	//总字节长度
	for (int i = 0; i < n; i++)
		totalLen = totalLen + arr[i].codelen*arr[i].frequency;
	//计算最后一次写入多少位
	last = totalLen % 8;
 
	fSource = fopen(sourceFile, "rb");
	fAim = fopen(aimFile, "wb");
 
	//先将huffman编码输进文件,以">"作为标识符 用于译码
	fwrite("->",1,2,fAim);
	fwrite(&n, sizeof(int), 1, fAim);  //写入字符种数
	fwrite(&last, sizeof(int), 1, fAim); //写入最后一次写入的位数
	//写入个字符值和字符频数
	for (int i = 0; i < n; i++)
	{
		fwrite(&arr[i].value, sizeof(unsigned char), 1, fAim);
		fwrite(&arr[i].frequency, sizeof(int), 1, fAim);
	}
 
	fread(&now, sizeof(unsigned char), 1, fSource); //读取源文件字符
	
	while (!feof(fSource))
	{
		for (int i = 0; 1; i++)
		{
			if (now == arr[i].value)
			{
				for(int j=0;j<arr[i].codelen;j++)
				{
					//按位操作保存编码
					if(len!=0)
						save=save<<1;  
					save=save|(arr[i].code[j]-'0');
					len++;
					//一个字节已存满，写入文件
					if(len==8)
					{
						fwrite(&save,sizeof(unsigned char),1,fAim);
						save=0;
						len=0;
					}
				}
				break;
			}
		}
		fread(&now, sizeof(unsigned char), 1, fSource); //读取字符
	}
	//最后一次可能没写满一个字节也要写入文件
	if(len!=0)
		fwrite(&save,sizeof(unsigned char),1,fAim);
	fclose(fSource);
	fclose(fAim);
}
//译码
//sourceFile为原文件名，*arr为用于保存数据的数组，aimFile为目标文件名
void writeDecode(char sourceFile[], HuffmanCode *arr, char aimFile[])
{
	FILE *fSource, *fAim; //原文件以及目标文件
	int n; //字符种数
	int last=0; //最后一次读取的位数
	unsigned char now;//读取的当前字符
 
	fSource = fopen(sourceFile, "rb");
 
	//确认是否以此代码编码的Huffman
	for (int i = 0; i < 2;i++)
	{
		fread(&now, sizeof(char), 1, fSource); //读取字符
		if (i == 0)
		{
			if (now == '-')
				continue;
			else
			{
				printf("原文件huffman编码格式不正确\n");
				fclose(fSource);
				return;
			}
		}
		if (now == '>')
			break;
		else
		{
			printf("原文件huffman编码格式不正确\n");
			fclose(fSource);
			return;
		}
	}
	//
	fread(&n, sizeof(int), 1, fSource);	//字符种数
	fread(&last, sizeof(int), 1, fSource); //最后一次读的位数
	for (int i = 0; i < n; i++)
	{
		fread(&arr[i].value, sizeof(unsigned char), 1, fSource);  //字符
		fread(&arr[i].frequency, sizeof(int), 1, fSource);//字符频数
	}
 
	struct Node *root = buildHuffman(arr, n); //建树
	codeByHuffman(root, 0, arr, n);
	struct Node *pNow = root;  //当前结点
	unsigned char temp; //每次读1个字节
	fAim = fopen(aimFile, "wb");
 
	fread(&temp, sizeof(unsigned char), 1, fSource);
	while (!feof(fSource))
	{
		unsigned char ifLast;  //用于判断是否读到文件末尾，方便读取固定位数
		fread(&ifLast, sizeof(unsigned char), 1, fSource);
		int i;
		if (feof(fSource))
			i = last-1;
		else
			i = 7;
		for (; i >= 0; i--)
		{
			if ((temp>>i & 1)==0)
				pNow = pNow->Lchild;
			else
				pNow = pNow->Rchild;
			if (pNow->Lchild == NULL && pNow->Rchild == NULL)
			{
				fwrite(&pNow->value, sizeof(unsigned char), 1, fAim);
				pNow = root;
			}
		}
		temp=ifLast;
	}
	fclose(fSource);
	fclose(fAim);
}
 
void main()
{
	while (1)
	{
		HuffmanCode node[2000];
		int num;  //字符种数
		char Sfilename[100] = ""; //原文件名
		char Afilename[100] = "";//输出文件名
		char choose[3] = "";
 
 
		printf("请选择:\n");
		printf("\t1.编码\n");
		printf("\t2.译码\n");
		printf("\t3.退出\n");
 
		scanf("%s", choose);
		fflush(stdin);
		if (!strcmp(choose, "1"))
		{
			while (1)
			{
				printf("请输入你想要编码的文件名:\n");
				scanf("%s", Sfilename);
				fflush(stdin);
				FILE *fp = fopen(Sfilename, "rb");
				if (fp == NULL)
				{
					printf("未找到文件.\n");
					continue;
				}
				else
				{
					fclose(fp);
					break;
				}
			}
				printf("请输入编码后的文件名:\n");
				scanf("%s", Afilename);
				fflush(stdin);
				num = count(Sfilename, node); //统计
				root = buildHuffman(node, num); //建树
			
				codeByHuffman(root, 0, node, num);//各个字符的Huffman编码
				
				writeCode(Sfilename, node, num, Afilename); //输出Huffman编码文件
				printf("编码完成!\n\n");
		}
		else if (!strcmp(choose, "2"))
		{
			while (1)
			{
				printf("请输入你想要译码的文件名:\n");
				scanf("%s", Sfilename);
				fflush(stdin);
				FILE *fp = fopen(Sfilename, "rb");
				if (fp == NULL)
				{
					printf("未找到文件.\n");
					continue;
				}
				else
				{
					fclose(fp);
					break;
				}
			}
			printf("请输入译码后的文件名:\n");
			scanf("%s", Afilename);
			fflush(stdin);
			writeDecode(Sfilename, node, Afilename); //译码并写文件
			printf("译码完成!\n\n");
		}
		else if (!strcmp(choose, "3"))
			return;
		else
		{
			printf("输入有误!\n");
			continue;
		}
	}
}
