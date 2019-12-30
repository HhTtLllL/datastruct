//##################################################################
// File Name: huffman_1.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2019年12月29日 星期日 20时34分57秒
//=============================================================
//!/usr/bin/python

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


typedef struct
{
	char value[4];     //字符值
	char code[100];    //字符编码
	int time;          //字符出现的次数
	int codelen;       //字符编码长度
}HuffmanCode;

struct Node
{
	int time;  //结点次数
	char value[4];   //字符值
	struct Node *Lchild;   //左结点
	struct Node *Rchild;   //右节点
};
struct filehead
{
	int totallen;
	int last;
	int time;
	int num;
};

int strncmp(char *a,char *b,int num)
{
	for(int i = 0;i < num;i++)
	{
		if(a[i] != b[i])
		{
			return 0;
		}

	}

	return 1;
}


int  read_cnt(char *path,HuffmanCode *node)
{
	//读文件中每个单词出现的频率 存进time数组
	int read_count = 0;
	char read_buf[1024]; 
	memset(read_buf,0,sizeof(read_buf));

	int fd = open(path,O_RDONLY);

	int num = 0; //统计一共有多少种数
	while((read_count = read(fd,read_buf,1024)) && read_count > 0)
	{
	//	printf("read_count = %d\n",read_count);
		for(int i = 0;i < read_count;i++)
		{
			if(read_buf[i] >= 0 && read_buf[i] <= 126)
			{

				printf("字母\n");
				//判断是否有重复
				for(int j = 0;j < num;j++)
				{
					if(read_buf[i] == node[j].value[0])
					{
						node[j].time++;
						goto repeat;
					}
				}
				//如果没有重复
				strncpy(node[num].value,read_buf + i,1);
				node[num].time = 1;
				num++;
repeat:{}
			}
			else   //不是一个英文字母
			{
				// 判断剩余字符是否大于等于  3
				if((read_count - i) >= 3)
				{
					int j;
					//读取三个字符
					char temp[3];
					memset(temp,0,sizeof(temp));
					strncpy(temp,read_buf+i,3);
			//		printf("temp = %s\n",temp);
					
					//判断是否有重复
					for(int j = 0;j < num;j++)
					{
				//		printf("%d\n",strncmp(temp,node[j].value,3));
						if(1 == strncmp(temp,node[j].value,3))
						{
							node[j].time++;
							goto repeat1;
						}
					}

					//如过没有重复
					strncpy(node[num].value,temp,3);
					node[num].time = 1;
					num++;

repeat1: {}
					i += 2;   //因为在这里读取了 三个节，循环处 + 1，这里 + 2. 一共三个字节
					
				}
				else  //如果剩下的字节 小于 3，则重新定位 文件指针的偏移
				{
					printf("重定位\n");
					lseek(fd,-read_count + i,SEEK_CUR);
					break;
				}


				
			}


//			letter[read_buf[i]]++;
		}


		//for(int i = 0;i < read_count;i++) printf("%d",read_buf[i]);
	}

	close(fd);
	
	printf("num = %d\n",num);
	for(int i = 0;i < num;i++)
	{
		printf("value = %s  ,time = %d\n",node[i].value,node[i].time);
	}



	printf("over\n");

	return num;
}

struct Node *root;

struct Node* build(HuffmanCode *node,int num)
{
	struct Node **arr,*temp;  //arr为造数用数组，temp 为最重返回的树
	arr = (struct Node **)malloc(num * sizeof(struct Node));


	//初始化数组
	for(int i = 0;i < num;i++)
	{
		arr[i] = (struct Node*)malloc(sizeof(struct Node));
		strncpy(arr[i]->value,node[i].value,3);
		arr[i]->time = node[i].time;
		arr[i]->Lchild = arr[i]->Rchild = NULL;
	}


	//build
	for(int i = 0;i < num - 1;i++)
	{
		int m1 = -1,m2; //最小额两个权值在数组中下标

		//将m1,m2指向头两棵树
		for(int j = 0;j < num;j++)
		{
			if(m1 == -1 && arr[j] != NULL)
			{
				m1 = j;
				continue;
			}
			if(arr[j] != NULL)
			{
				m2 = j;
				break;
			}
		}

		//比较权值大小，找到最小的两个
		for(int j = m2;j < num;j++)
		{
			if(arr[j] != NULL && (arr[j]->time < arr[m1]->time))
			{
				m2 = m1;
				m1 = j;
			}
			else if(arr[j] != NULL && (arr[j]->time < arr[m2]->time))
				m2 = j;
		}
			//将两个权值最小的构成新树

			temp = (struct Node *)malloc(sizeof(struct Node));
			temp->Lchild = arr[m1];
			temp->Rchild = arr[m2];

			temp->time = arr[m1]->time + arr[m2]->time;
			//temp->value = "\0";
			strcpy(temp->value,"\0");

			//将新树加入数组
			arr[m1] = temp;
			arr[m2] = NULL;
	}
	free(arr);

	return temp;   //最终temp为树根

}

void Huffmancode(struct Node *node,int len,HuffmanCode *arr,int num)
{
	static char code[10000];   //编码

	//左儿子 不为空，编码为 0
	if(node->Lchild != NULL)
	{
		code[len] = '0';
		code[len + 1] = '\0';
		Huffmancode(node->Lchild,len + 1,arr,num);  //递归
	}

	//右儿子不为空，编码为1   
	if(node->Rchild != NULL)
	{
		code[len] = '1';
		code[len + 1] = '\0';
		Huffmancode(node->Rchild,len + 1,arr,num);
	}
	else
	{
		for(int i = 0;i < num;i++)
		{
			//将编码复制给数组里的元素
			if(strcmp(arr[i].value,node->value))
			{
				printf("111\n");
				strcpy(arr[i].code,code);
				arr[i].codelen = 0;
				for(int j = 0;arr[i].code[j] != '\0';j++)
				{
					arr[i].codelen++;
				}

				return ;
			}
		}
	}
}

//将文件内容转为 Huffman

void writecode(char *path,HuffmanCode *arr,int num,char *writepath)
{
	struct filehead head;
	int fsource,faim;
	char curvalue[3];  //读取当前字符
	unsigned char save = 0;  //每次保存一个字节的长度
	int len = 0;  //每次保存的一个字节已经存了多少长度
	int totallen = 0;  //文件编码总长度
	int last;  //最后一次写入时的位数

	//总子节长度
	for(int i = 0;i < num;i++)
	{
		totallen = totallen + arr[i].codelen * arr[i].time;
	}
	head.totallen = totallen;
	

	//计算最后一次写入多少位
	last = totallen%8;
	head.last = last;

	head.num = num;
	head.time = totallen / 8;

	fsource = open(path,O_RDONLY);
	faim = open(writepath,O_RDWR | O_CREAT,0644);

	write(faim,&head,sizeof(head));
	//写入字符值和字符频率
	for(int i = 0;i < num;i++)
	{
		write(faim,&arr[i].value,sizeof(arr[i].value));
		write(faim,&arr[i].time,sizeof(arr[i].time));
	}

	int read_count = 0;
	char read_buf[1024];
	memset(read_buf,0,sizeof(read_buf));
	while((read_count = read(fsource,read_buf,1024)) && read_count > 0)
	{
		for(int i = 0;i < read_count;i++)
		{
			if(read_buf[i] >= 0 && read_buf[i] <= 126)
			{
				int j = 0;
				while(true)
				{
					if(read_buf[i] == arr[j].value[0])
					{
						for(int k = 0;k < arr[j].codelen;k++)
						{
							//按位操作保存编码
							if(len != 0) save = save << 1;

							save = save | (arr[j].code[k] - '0');
							len++;
							//一个字节已存满,写入文件

							if(len == 8)
							{
								write(faim,&save,sizeof(save));
								save = 0;
								len = 0;
							}
						}
						break;
					}
					j++;
				}
			}
			else
			{
				if((read_count - i) >= 3)
				{
					char temp[3];
					memset(temp,0,sizeof(temp));
					strncpy(temp,read_buf+i,3);
					int j = 0;
					while(true)
					{
						if(1 == strncmp(temp,arr[j].value,3))
						{
							for(int k = 0;k < arr[j].codelen;k++)
							{
								//按位操作保存编码
								if(len != 0) save = save << 1;

								save = save | (arr[j].code[k] - '0');
								len++;
								//一个字节已存满
								if(len == 8)
								{
									write(faim,&save,sizeof(save));
									save = 0;
									len = 0;
								}
							}
							break;
						}
						j++;
					}
				}
				else
				{
					lseek(fsource,-read_count + i,SEEK_CUR);
					break;
				}
			}
		}
	}
	
	if(len != 0) write(faim,&save,sizeof(save));

	close(fsource);
	close(faim);

}


int main()
{
	HuffmanCode node[1000];
	memset(node,0,sizeof(node));
	int num = 0;  //记录一共有多少组数
	char path[100];
	
	scanf("%s",path);   //读取路径名
	int pathlen = strlen(path);
	char writepath[100];
	strncpy(writepath,path,pathlen);
	writepath[pathlen] = '.';
	writepath[pathlen + 1] = 'H';
	writepath[pathlen + 2] = 'z';

	num = read_cnt(path,node);      

	root = build(node,num);

	Huffmancode(root,0,node,num);   //各个字符的 huffman 编码
	
	printf("len = %ld\n",strlen(path));


	writecode(path,node,num,writepath);
	return 0;
}


