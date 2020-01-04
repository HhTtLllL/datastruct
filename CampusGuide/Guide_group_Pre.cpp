//##################################################################
// File Name: Guide_group_Pre.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年01月02日 星期四 22时03分46秒
//=============================================================
//!/usr/bin/python
#include "Guide_group_Pre.h"

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
	
	while(row = mysql_fetch_row(result))
	{
		if(NULL == row ) break;
		for(int i = 0;i < 15;i++)
		{
			for(int j = 0;j < 15;j++)
			{
				if((i == atoi(row[2])) && (j == atoi(row[3])))
				{
					printf("%d.%s",atoi(row[0]),row[1]);
				}
				else
				{
					printf(" ");
				}
	
			}
			if((i%2))
				printf("\n");
		}
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
	for(int i = 0;i < list.vexnum;i++)
	{
		list.vertex[i].firstarc = NULL;
	}
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
		int index1 = indexbyname(row[1],&list);
		int index2 = indexbyname(row[2],&list);
	
	//	ArcNode *temp1 = list.vertex[index1].firstarc;
	//	if(temp1 == NULL) printf("NULL\n");
	//	while(temp1 != NULL) temp1 = temp1->nextarc;
		
		endpoint1->nextarc = NULL;
		endpoint1->adjvex = index2;
		endpoint1->info.weight = atoi(row[2]);
		strcpy(endpoint1->info.info,row[3]);
	//	printf("row = %s\n",row[3]);
		//while(list.vertex[index1].firstarc != NULL) list.vertex[index1].firstarc = list.vertex[index1].firstarc->nextarc;
		if(list.vertex[index1].firstarc == NULL )
		{
			printf("333 index1 = %d\n",index1);
			list.vertex[index1].firstarc = endpoint1;
		}
		else
		{
			printf("444\n");
			ArcNode *temp = list.vertex[index1].firstarc;
			while(temp->nextarc != NULL) 
				temp = temp->nextarc;
			
			temp->nextarc = endpoint1;
			
		}


	//	temp1 = endpoint1;
	

	//	printf("temp = %d\n",temp1->adjvex);

	//	ArcNode *temp2 = Find_end(&list,index2);
	//	temp2 = endpoint2;
		endpoint2->nextarc = NULL;
		endpoint2->adjvex = index1;
		endpoint2->info.weight = atoi(row[2]);
		strcpy(endpoint2->info.info,row[3]);
		
		if(list.vertex[index2].firstarc == NULL )
		{
			printf("222 index = %d\n",index2);
			list.vertex[index2].firstarc = endpoint2;
		}
		else
		{
			printf("111\n");
			ArcNode *temp = list.vertex[index2].firstarc;
			while(temp->nextarc != NULL) 
				temp = temp->nextarc;
			
			temp->nextarc = endpoint2;
			
			/*while(list.vertex[index2].firstarc->nextarc != NULL)
				list.vertex[index2].firstarc = list.vertex[index2].firstarc->nextarc;
			list.vertex[index2].firstarc->nextarc = endpoint2;*/
		}
	//	list.vertex[index2].firstarc = endpoint2;
	}
	list.arcnum = i*2;

//遍历AdjList 输出地图
	
/*	printf("222\n");
	for(int i = 0;i < list.vexnum;i++)
	{
		if(list.vertex[i].firstarc != NULL)
		printf("%s\n",list.vertex[i].firstarc->info.info);
	}
	*/
	
	for(int i = 0;i < list.vexnum;i++)
	{
		printf("输出路径\n");
		ArcNode *temp = list.vertex[i].firstarc;
	/*	while(temp != NULL)
		{
			printf("%s->%s\n",list.vertex[i].data.name,temp->info.info);
			
			temp = temp->nextarc;	
		}
*/
		if(temp != NULL)
		{
			printf("%s->%s\n",list.vertex[i].data.name,temp->info.info);
			temp = temp->nextarc;
			while(temp != NULL)
			{
			  printf("%s->%s\n",list.vertex[i].data.name,temp->info.info);

			  temp = temp->nextarc;	
			}
		}
		else printf("空\n");
	}



}
ArcNode *Find_end(AdjList *list,int index)
{
	ArcNode *temp = list->vertex[index].firstarc;
	printf("Find\n");
	while(temp != NULL)
	{
		printf("22222\n");
		printf("adjvex = %d\n",temp->adjvex);
		temp = temp->nextarc;
	}

	return temp;
}

int indexbyname(char *name,const AdjList *list)
{
	for(int i = 0;i < list->vexnum;i++)
	{
		printf("listname = %s,name = %s\n",list->vertex[i].data.name,name);
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
		printf("名字: %s  特征: %s 坐标:x = %d,y = %d\n",row[1],row[2],atoi(row[3]),atoi(row[4]));
	}
	
	return ;
}


void Guide_Updata_load()
{
	char data[1000];
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
  	
	char endpoint1[30];
	char endpoint2[30];
	int value;
	char information[100];


	mysql_init(&mysql);
        if(!mysql_real_connect(&mysql,"0.0.0.0","root","073848","guide",0,NULL,0)) printf("连接数据库失败\n");
	if(mysql_set_character_set(&mysql,"utf8")) printf("设置中文失败\n");
	printf("输入这条路的起点:");
	scanf("%s",endpoint1);
	printf("输入这条路的终点:");
	scanf("%s",endpoint2);
	printf("输入这条路的权值:");
	scanf("%d",&value);
	printf("输入这条路描述:");
	scanf("%s",information);
	
	sprintf(data,"insert into Guide_load values ('%s','%s',%d,'%s')",endpoint1,endpoint2,value,information);
	if(mysql_query(&mysql,data)) printf("插入错误\n");
	else printf("插入成功\n");

	return ;
}
void Guide_Updata_Attraction()
{
	char data[1000];
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
	char name[30];
	char features[30];
	int x;
	int y;

	mysql_init(&mysql);
        if(!mysql_real_connect(&mysql,"0.0.0.0","root","073848","guide",0,NULL,0)) printf("连接数据库失败\n");
	if(mysql_set_character_set(&mysql,"utf8")) printf("设置中文失败\n");
  	printf("输入景点名字:");
	scanf("%s",name);
	printf("输入景点描述:");
	scanf("%s",features);
	printf("输入横坐标:");
	scanf("%d",&x);
	printf("输入纵坐标:");
	scanf("%d",&y);
	sprintf(data,"insert into Guide_Attractions values (%ld,'%s','%s',%d,%d)",NULL,name,features,x,y);
	if(mysql_query(&mysql,data)) printf("插入错误\n");
	else printf("插入成功\n");
	
	return ;
}

void Guide_Found_PathByValue()
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
		strcpy(list.vertex[i].data.name,row[1]);
		strncpy(list.vertex[i].data.info,row[2],sizeof(row[2]));
		list.vertex[i].data.x = atoi(row[3]);
		list.vertex[i].data.y = atoi(row[4]);
		i++;
	}
	list.vexnum = i;
	for(int i = 0;i < list.vexnum;i++)
	{
		list.vertex[i].firstarc = NULL;
	}


	sprintf(data,"select *from Guide_load");
	if(mysql_query(&mysql,data)) printf("查询出错\n");
	result = mysql_store_result(&mysql);

	if(result == NULL)
	{
		printf("无结果\n");
		return ;
	}
	i = 0;  //记录边数
	while(row = mysql_fetch_row(result))
	{
		printf("加边\n");
		i++;
		ArcNode *endpoint1 = (ArcNode*)malloc(sizeof(ArcNode));
		ArcNode *endpoint2 = (ArcNode*)malloc(sizeof(ArcNode));
		int index1 = indexbyname(row[0],&list);
		int index2 = indexbyname(row[1],&list);

		endpoint1->nextarc = NULL;
		endpoint1->adjvex = index2;
		endpoint1->info.weight = atoi(row[2]);
		strcpy(endpoint1->info.info,row[3]);
		if(list.vertex[index1].firstarc == NULL )
		{
			printf("111\n");
			list.vertex[index1].firstarc = endpoint1;
		}
		else
		{
			printf("222\n");
			ArcNode *temp = list.vertex[index1].firstarc;
			while(temp->nextarc != NULL) 
				temp = temp->nextarc;

			temp->nextarc = endpoint1;

		}



		endpoint2->nextarc = NULL;
		endpoint2->adjvex = index1;
		endpoint2->info.weight = atoi(row[2]);
		strcpy(endpoint2->info.info,row[3]);

		if(list.vertex[index2].firstarc == NULL )
		{
			printf("333\n");
			list.vertex[index2].firstarc = endpoint2;
		}
		else
		{
			printf("444\n");
			ArcNode *temp = list.vertex[index2].firstarc;
			while(temp->nextarc != NULL)
				temp = temp->nextarc;

			temp->nextarc = endpoint2;

		}
	}
	list.arcnum = i*2;
	
	for(int i = 0;i < list.vexnum;i++)
	{
		ArcNode *temp = list.vertex[i].firstarc;
		
		if(temp != NULL)
		{
			printf("%s->%s\n",list.vertex[i].data.name,temp->info.info);
			temp = temp->nextarc;
			while(temp != NULL)
			{
			  printf("%s->%s\n",list.vertex[i].data.name,temp->info.info);

			  temp = temp->nextarc;	
			}
		}
		else printf("空\n");
	}


	int arcs[list.vexnum][list.vexnum];

	for(int i = 0;i < list.vexnum;i++)
	{
		for( int j = 0;j < list.vexnum;j++)
		{
			arcs[i][j] = 9999;
		}
	}
	
	sprintf(data,"select *from Guide_load");
	if(mysql_query(&mysql,data)) printf("查询出错\n");
	result = mysql_store_result(&mysql);

	if(result == NULL)
	{
		printf("无结果\n");
		return ;
	}
	i = 0;  //记录边数
	//建立邻接矩阵
	while(row = mysql_fetch_row(result))
	{
		int ind1 = Guide_Found_index(row[0]);
		int ind2 = Guide_Found_index(row[1]);

		arcs[ind1][ind2] = atoi(row[2]);
		arcs[ind2][ind1] = atoi(row[2]);
	}

	for(int i = 0;i < list.vexnum;i++)
	{
		for(int j = 0;j < list.vexnum;j++)
		{
			printf("%d  ",arcs[i][j]);
		}
		printf("\n");
	}
	
	int mindist,start = 1,end = 5,k,t = 1;

	int path[1000][1000];
	int dist[1000];

	for(int i = 0;i < list.vexnum;i++)
	{
		dist[i] = arcs[start][i];
		if(arcs[start][i] != 9999) path[i][1] = start;
	}

	path[start][0] = 1;
	mindist = 9999;
	for(int j = 0;j < list.vexnum;j++)
	{
		if(!path[j][0] && dist[j] < mindist) 
		{
			k = j;
			mindist = dist[j];
		}
	}

	path[k][0] = 1;
	for(int j = 0;j < list.vexnum;j++)  
	{
		if(!path[j][0] && arcs[k][j] < 9999 && dist[k] + arcs[k][j] < dist[j])
		{
			dist[j] = dist[k] = arcs[k][j];
			t = 1;
			while(path[k][t] != 0)
			{
				path[j][t] = path[k][t];
				t++;
			}
			path[j][t] = k;
			path[j][t+1] = 0;
		}

	}

	for(int i = 0;i < list.vexnum;i++)
	{
		for(int j = 0;j < list.vexnum;j++)
		{
			printf("%d ",path[i][j]);
		}
		printf("\n");
	}








	
	/*
	for(int i = 0;i < list.vexnum;i++)
	{
	   if(i == Graph->Nv)	ArcNode *temp = list.vertex[i].firstarc;
		temp = temp->nextarc;
		while(temp != NULL)
		{
			int index = Guide_Found_index(temp->name);
			arcs[i][index] = 
		}

	}


*/




}


	

int Guide_Found_index(char *name)
{
	char data[1000];
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;

	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql,"0.0.0.0","root","073848","guide",0,NULL,0)) printf("连接数据库失败\n");
	if(mysql_set_character_set(&mysql,"utf8")) printf("中文设置错误\n");

	sprintf(data,"select *from Guide_Attractions");
	if(mysql_query(&mysql,data)) printf("查询出错\n");
	result = mysql_store_result(&mysql);

	if(result == NULL)
	{
		printf("无结果\n");
		//return ;
	}
	int i = 0;

	while(row = mysql_fetch_row(result))
	{
		if(NULL == row)
		{
			break;
		}
		if(!strcmp(name,row[1]))
		{
			return i;
		}
		i++;
	}

	return i;

}

