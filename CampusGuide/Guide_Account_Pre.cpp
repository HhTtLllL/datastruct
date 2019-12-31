//##################################################################
// File Name: Guide_Account_Pre.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2019年12月31日 星期二 16时09分13秒
//=============================================================
//!/usr/bin/python

#include "Guide_Account_Pre.h"

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
