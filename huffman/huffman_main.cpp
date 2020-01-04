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
	int select;
	do
	{
		printf("1  压缩\n");
		printf("2  解压缩\n");
		printf("3  退出\n");
		printf("输入选项:");
		scanf("%d",&select);
		fflush;
		switch(select)
		{
			case 1:
				commpression();
				printf("压缩成功\n");
				break;
			case 2:
				Decode();
				printf("解压成功\n");
				break;
		}

	}while(select != 3);

	return 0;
}
