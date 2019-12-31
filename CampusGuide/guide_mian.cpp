//##################################################################
// File Name: guide_mian.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2019年12月31日 星期二 14时01分38秒
//=============================================================
//!/usr/bin/python

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define fflush while((ch = getchar()) != '\n');
char ch;
int Guide_Account();
void Guide_tour_UI()
{
	int select;
	do
	{
		printf("1.查看地图\n");
		printf("2.查看景点\n");
		printf("3.寻找最优路径\n");
		printf("4.退出\n");
		printf("输入选项:");
		scanf("%d",&select);
		fflush;
		switch(select)
		{
			case 1:
				//查看地图
				break;
			case 2:
				//查看景点
				break;
			case 3:
				//寻找最佳路径
				break;
		}

	}while(select != 4);

	return ;
}
void Guide_admin_UI()
{
	int select;
	do
	{
		printf("1.更新地图\n");
		printf("2.更新景点\n");
		printf("3.更新道路\n");
		printf("4.退出\n");
		printf("输入选项:");
		scanf("%d",&select);
		fflush;
		switch(select)
		{
			case 1:
				//更新地图
				break;
			case 2:
				//更新景点
				break;
			case 3:
				//更新道路
				break;
		}
	}while(select != 4);
}
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
				Guide_tour_UI();
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

int Guide_Account()
{
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
	mysql_init(&mysql);
	
	if(!mysql_real_connect(&mysql,"0.0.0.0","root","073848","guide",0,NULL,0)) printf("连接数据库失败\n");
	//if(mysql_query(&mysql,"set name utf8")) printf("设置中文失败\n");

	char account[20];
	char password[20];
	char data[1000];

	printf("输入账号:");
	scanf("%s",account);
	printf("输入密码:");
	scanf("%s",password);
	sprintf(data,"select password from Guide_account where account = '%s'",account);
	if(mysql_query(&mysql,data)) printf("超照出错\n");
	
	result = mysql_store_result(&mysql);
	if(result == NULL) printf("结果集为空\n");

	row = mysql_fetch_row(result);
	if(NULL == row) printf("查找结果为空\n");
	
	if(!strcmp(row[0],password)) return 1;
	else return 0;

	

	
	
	
	
	
/*sprintf(data,"select '密码' from '账号信息' where '账号' = '%s'",account);
	if(mysql_query(&mysql,data))  printf("查找账户信息错误\n");

	result = mysql_store_result(&mysql);

	if(result == NULL) printf("结果集为空\n");

	row = mysql_fetch_row(result);
	if(NULL == row) printf("查找结果为空\n");
	
	if(!strcmp(row[0],password)) return 1;
	else return 0;
*/
}
