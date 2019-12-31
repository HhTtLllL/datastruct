//##################################################################
// File Name: Guide_UI.c
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2019年12月31日 星期二 15时54分05秒
//=============================================================
//!/usr/bin/python
#include "./Guide_UI.h"

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
				Find_Group();
                                //查看地图
                                break;
                        case 2:
				Find_Attractions();
                                //查看景点
                                break;
                        case 3:
                                //寻找最佳路径
                                break;
                }

        }while(select != 4);

        return ;
}

void Find_Group()
{
	char data[1000];
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
  
	mysql_init(&mysql);
        if(!mysql_real_connect(&mysql,"0.0.0.0","root","073848","guide",0,NULL,0)) printf("连接数据库失败\n");
	if(mysql_set_character_set(&mysql,"utf8")) printf("中文设置错误\n");
	AdjList list;
	//读取景点/顶点
	sprintf(data,"select *from Guide_Attractions");
	if(mysql_query(&mysql,data)) printf("查询出错\n");
	result = mysql_store_result(&mysql);

	if(result == NULL)
	{
		printf("无结果\n");
		return ;
	}
	int i = 0; //记录顶点数
	while(row = mysql_fetch_row(result))
	{
		if(NULL == row)
		{
			break;
		}
		strcpy(list.vertex[i].data.name,row[0]);
		strncpy(list.vertex[i].data.info,row[1],sizeof(row[1]));
		list.vertex[i].data.x = atoi(row[2]);
		list.vertex[i].data.y = atoi(row[3]);
		i++;
	}
	list.vexnum = i;
	
	//查询道路/边

	sprintf(data,"select *from Guide_load");
	if(mysql_query(&mysql,data)) printf("查询出错\n");
	result = mysql_store_result(&mysql);

	if(result == NULL)
	{
		printf("无结果\n");
		return ;
	}
	i = 0;  //记录边数
	// bug
	while(row = mysql_fetch_row(result))
	{
		i++;
		ArcNode *endpoint1 = (ArcNode*)malloc(sizeof(ArcNode));
		ArcNode *endpoint2 = (ArcNode*)malloc(sizeof(ArcNode));
	
		int index1 = indexbyname(row[0],&list);
		int index2 = indexbyname(row[1],&list);
	
		ArcNode *temp1 = Find_end(&list,index1);
		temp1 = endpoint1;
		temp1->nextarc = NULL;
		temp1->adjvex = index2;
		temp1->info.weight = atoi(row[2]);
		strncpy(temp1->info.info,row[3],sizeof(row[3]));


		ArcNode *temp2 = Find_end(&list,index2);
		temp2 = endpoint2;
		temp2->nextarc = NULL;
		temp2->adjvex = index1;
		temp2->info.weight = atoi(row[2]);
		strncpy(temp1->info.info,row[3],sizeof(row[3]));
	}
	list.arcnum = i;
//遍历AdjList 输出地图
	
	for(int i = 0;i < list.vexnum;i++)
	{
		printf("111\n");
		ArcNode *temp = list.vertex[i].firstarc;
		while(temp != NULL)
		{
			printf("%s->%s\n",list.vertex[i].data.name,temp->info.info);
			
			temp = temp->nextarc;	
		}
	}



}
ArcNode *Find_end(AdjList *list,int index)
{
	ArcNode *temp = list->vertex[index].firstarc;
	while(temp != NULL)
	{
		temp = temp->nextarc;
	}

	return temp;
}

int indexbyname(char *name,const AdjList *list)
{
	for(int i = 0;i < list->vexnum;i++)
	{
		//printf("listname = %s,name = %s\n",list->vertex[i].data.name,name);
		if(!strcmp(list->vertex[i].data.name,name))
		{
			return i;
		}
	}
	
	printf("出错\n");
	return -1;

}

void Find_Attractions()
{
	char data[1000];
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
  
	mysql_init(&mysql);
        if(!mysql_real_connect(&mysql,"0.0.0.0","root","073848","guide",0,NULL,0)) printf("连接数据库失败\n");
	if(mysql_set_character_set(&mysql,"utf8")) printf("设置中文失败\n");
	
	sprintf(data,"select *from Guide_Attractions");
	if(mysql_query(&mysql,data)) printf("查询出错\n");
	result = mysql_store_result(&mysql);

	if(result == NULL)
	{
		printf("无结果\n");
		return ;
	}
	
	while(row = mysql_fetch_row(result))
	{
		if(NULL == row)
		{
			printf("空\n");
			break;
		}
		printf("名字: %s  特征: %s 坐标:x = %d,y = %d\n",row[0],row[1],atoi(row[2]),atoi(row[3]));
	}
	
	return ;
}
