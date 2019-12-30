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

typedef struct
{
	int time;  //结点次数
	char value[4];   //字符值
	struct Node *Lchild;   //左结点
	struct Node *Rchild;   //右节点
}Node;

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
	
	

}

struct Node *root;

struct Node* build(HuffmanCode *node,int num)
{
	struct Node **arr,*temp;  //arr为造数用数组，temp 为最重返回的树
	arr = (struct Node **)malloc(num * sizeof(struct Node));


	//初始化数组
	for(int i = 0;i < n;i++)
	{
		arr[i] = (struct Node*)malloc(sizeof(struct Node));
		strncpy(arr[i]->value,node[i].value,3);
		arr[i]->time = node[i].time;
		arr[i]->Lchild = arr[i]->Rchild = NULL;
	}


	build

}


int main()
{
	HuffmanCode node[1000];
	memset(node,0,sizeof(node));
	int num = 0;  //记录一共有多少组数
	char path[100];
	scanf("%s",path);   //读取路径名

	num = read_cnt(path,node);      

	return 0;
}


