//##################################################################
// File Name: Guide_UI.c
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2019年12月31日 星期二 15时54分05秒
//=============================================================
//!/usr/bin/python
#include "./Guide_group_Pre.h"

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
				Guide_Updata_Attraction();
                                //更新景点
                                break;
                        case 3:
				Guide_Updata_load();
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
				Guide_Found_PathByValue();
                                break;
                }

        }while(select != 4);

        return ;
}

