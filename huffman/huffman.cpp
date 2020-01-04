//##################################################################
// File Name: huffman.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2019年12月30日 星期一 23时01分27秒
//=============================================================
//!/usr/bin/python
#include <sys/stat.h>
#include <time.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "./huffman.h"
#define fflush while((ch = getchar()) != '\n');

char ch;
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

void commpression()
{
	struct Node *root;
        HuffmanCode node[1000];
        memset(node,0,sizeof(node));
        int num = 0;  //记录一共有多少组数
        char path[100];
	printf("输入文件名:");
        scanf("%s",path);   //读取路径名
	fflush;

        int pathlen = strlen(path);
        char writepath[100];
        strncpy(writepath,path,pathlen);
        writepath[pathlen] = '.';
        writepath[pathlen + 1] = 'H';
        writepath[pathlen + 2] = 'z';
        writepath[pathlen + 3] = '\0';

        num = read_cnt(path,node);

        root = build(node,num);

        Huffmancode(root,0,node,num);   //各个字符的 huffman 编码

        for(int i = 0;i < num;i++)
        {
                printf("i = %d  ,,value = %s  ,time = %d\n",i,node[i].value,node[i].time);
        }

//      printf("len = %ld\n",strlen(path));

        writecode(path,node,num,writepath);

	struct stat statbuf;
	int size1,size2;
	stat(path,&statbuf);
	size1 = statbuf.st_size;
	stat(writepath,&statbuf);
	size2 = statbuf.st_size;
	printf("压缩比:%lf\n",(size2*1.0) / (size1*1.0));
	printf("文件创建时间:%s\n",ctime(&statbuf.st_atime));

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

				//printf("字母\n");
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
				node[num].value[1] = '\0';
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
	//				printf("重定位\n");
					lseek(fd,-read_count + i,SEEK_CUR);
					break;
				}
			}
		}
	}

	close(fd);

//	printf("num = %d\n",num);
/*	for(int i = 0;i < num;i++)
	{
		printf("i = %d  ,,value = %s  ,time = %d\n",i,node[i].value,node[i].time);
	}

*/

//	printf("over\n");

	return num;
}



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


/*	for(int i = 0;i < num;i++)
	{
		printf("i = %d  ,,value = %s  ,time = %d\n",i,node[i].value,node[i].time);
	}
*/
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
			if(!strcmp(arr[i].value,node->value))
			{
		//		printf("value = %s,,,node->value = %s\n",arr[i].value,node->value);
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
	struct stat statbuf;
	stat(writepath,&statbuf);
	strcpy(head.ctime,ctime(&statbuf.st_atime));

	head.num = num;
	head.time = totallen / 8;

	fsource = open(path,O_RDONLY);
	faim = open(writepath,O_RDWR | O_CREAT,0644);

	write(faim,&head,sizeof(head));
	
	//写入字符值和字符频率
	for(int i = 0;i < num;i++)
	{
	//	printf("writevalue = %s,time = %d\n",arr[i].value,arr[i].time);
		write(faim,&arr[i].value,sizeof(arr[i].value));
		write(faim,&arr[i].time,sizeof(arr[i].time));
	}

	int read_count = 0;
	char read_buf[1024];
	memset(read_buf,0,sizeof(read_buf));
	//printf("306\n");
	while((read_count = read(fsource,read_buf,1024)) && read_count > 0)
	{
		for(int i = 0;i < read_count;i++)
		{
			if(read_buf[i] >= 0 && read_buf[i] <= 126)
			{
				int j = 0;
				while(true)
				{
		//			printf("j = %d\n",j);
		//			printf("read_buf = %c,,,arr.value = %c\n",read_buf[i],arr[j].value[0]);
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
//						printf("j = %d   ",j);
				//		printf("temp = %s\n",temp);
				//		printf("value = %s\n",arr[j].value);
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
					i += 2;
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



//译码
//fsource 为原文件名， *arr用于保存数据数组，aim为目标文件名
void Decode()
{
	int curtime = 0;//统计一共译码的个数

	char sourcepath[100];
	char aimpath[100];
	printf("输入解压文件名:");
	scanf("%s",sourcepath);
	fflush;
	int len = strlen(sourcepath);
	strncpy(aimpath,sourcepath,len);
	aimpath[len - 3] = '_';
	aimpath[len - 2] = '1';
	aimpath[len - 1] = '\0';
	//printf("输入目标文件名:");
	//scanf("%s",aimpath);
	//fflush;

	char read_buf[1024];
	memset(read_buf,0,sizeof(read_buf));
	int read_count = 0;
	HuffmanCode arr[2000];

	int fsource,faim;
	fsource = open(sourcepath,O_RDONLY);
	struct filehead head;
	read(fsource,&head,sizeof(head));
	//printf("文件压缩时间:%s\n",head.ctime);
	for(int i = 0;i < head.num;i++)
	{
		read(fsource,&arr[i].value,sizeof(arr[i].value));
		read(fsource,&arr[i].time,sizeof(arr[i].time));
	//	printf("readvalue = %s,readtime = %d\n",arr[i].value,arr[i].time);
	}

	struct Node *root = build(arr,head.num);
	Huffmancode(root,0,arr,head.num);

	struct Node*pNow = root; //当前结点

	unsigned char temp;  //每次读一个字节
	faim = open(aimpath,O_RDWR | O_CREAT,0644);

	while((read_count = read(fsource,read_buf,1024)) && read_count > 0)
	{
		unsigned char ifLast;//用于判断是否到达文件末尾

		for(int i = 0;i < read_count;i++)
		{
			temp = read_buf[i];
			int j;
			if(curtime < head.time)
			{
				curtime++;
				j = 7;
			}
			else
			{
				j = head.last - 1;
			}

			for(;j >= 0;j--)
			{
				if((temp >> j & 1) == 0) pNow = pNow->Lchild;
				else pNow = pNow->Rchild;

				if(pNow->Lchild == NULL && pNow->Rchild == NULL) //到了叶子结点
				{
	//				printf("writevalue = %s\n",pNow->value);
					if(pNow->value[0] >= 0 && pNow->value[0] <= 126)
					{
						write(faim,&pNow->value[0],sizeof(char));
					}
					else write(faim,&pNow->value,sizeof(pNow->value));
					pNow = root;
				}
			}

	//		temp = read_buf[i];
		}
	}

	close(fsource);
	close(faim);



	return ;
}

