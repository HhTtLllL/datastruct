//##################################################################
// File Name: guide_mian.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2019年12月31日 星期二 14时01分38秒
//=============================================================
//!/usr/bin/python

#include <stdio.h>
#include "./Guide_UI.h"
#include "./Guide_Account_Pre.h"
#define fflush while((ch = getchar()) != '\n');
#define MAXVEX 100
char ch;

int main()
{
	int select;
	do
	{
		printf("1.游客登录\n");
		printf("2.管理员登录\n");
		printf("3.退出\n");
		printf("输入选型:");
		scanf("%d",&select);
		fflush;
		switch(select)
		{
			case 1:
				Guide_tour_UI( );
				break;
			case 2:
				if(Guide_Account() == 1)//管理员登录
				{
					Guide_admin_UI();
				}
				else printf("密码错误\n");
				break;
			
		}

	}while(select != 3);

	return 0;
}
