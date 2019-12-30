//##################################################################
// File Name: huffman_main.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2019年12月30日 星期一 23时04分59秒
//=============================================================
//!/usr/bin/python

#include "./huffman.h"
#include <stdio.h>
#include <string.h>


int main()
{
	struct Node *root;
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
	writepath[pathlen + 3] = '\0';

	num = read_cnt(path,node);

	root = build(node,num);

	Huffmancode(root,0,node,num);   //各个字符的 huffman 编码

	for(int i = 0;i < num;i++)
	{
		printf("i = %d  ,,value = %s  ,time = %d\n",i,node[i].value,node[i].time);
	}

	printf("len = %ld\n",strlen(path));

	writecode(path,node,num,writepath);


	printf("输入一个数\n");
	int select;
	char ch;
	scanf("%d",&select);
	while((ch = getchar()) != '\n');
	if(select == 1)
	{
		Decode();
	}



	return 0;
}
