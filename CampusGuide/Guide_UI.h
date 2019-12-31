#ifndef GUIDE_UI_H
#define GUIDE_UI_H
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#define MAXVEX 100

typedef struct //道路类型
{
	int weight;//道路权值
	char info[100];  //道路信息描述
}EdgeInfo;

typedef struct ArcNode //边结点类型
{
	int adjvex;               //邻接点    保存这个结点在临结数组的下标
	struct ArcNode * nextarc;
	EdgeInfo info;
}ArcNode;

typedef struct //景点类型
{
	char name[30];  //景点名称
	char info[100];   //景点特征，功能介绍
	int x,y;  //景点坐标
}VertexData;

typedef struct VertexNode  //图表头数组类型
{
	VertexData data;
	ArcNode *firstarc;
}VertexNode;

typedef struct //邻接表类型
{
	VertexNode vertex[MAXVEX];  //邻接表表头数组
	int vexnum,arcnum;  //景点数量,道路数量

}AdjList;


int indexbyname(char *name,const AdjList *list);
ArcNode *Find_end(AdjList *list,int index);
void Find_Group();
void Guide_tour_UI();
void Guide_admin_UI();
void Find_Attractions();

#endif
