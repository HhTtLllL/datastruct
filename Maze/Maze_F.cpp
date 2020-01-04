#include <iostream>
#include <string.h>
#include <math.h>
#include <list>

#define L 20
using namespace std;
typedef struct
{
	char attr; //节点属性
	int access; //标记是否访问
	int x;
	int y;
}Maze;
char name[1000];
struct data
{
	int x;
	int y;
};
Maze array[L+2][L+2];

void Init() //初始化迷宫数组
{
	for(int i=0;i<L+2;i++)
		for(int j=0;j<L+2;j++)
			array[i][j].access = 0;
}


void Print() //打印迷宫数组
{
	cout << endl;
	cout << endl;
	for(int i=1;i<L+1;i++)
	{
		for(int j=1;j<L+1;j++)
		{
			if(array[i][j].attr == '0')
			{
				if(array[i][j].access == 0)
					printf("0");
				else
					printf(" ");
			}
			else
				printf("1");
		}

		printf("\n");
	}
}

void creat_rand(unsigned int seed) //随机创建迷宫数组
{
	for(int i=0;i<L+2;i++)
		for(int j=0;j<L+2;j++)
		{
			array[i][j].attr = 1;
			array[i][j].access = 0;
		}

	srand(unsigned(seed));
	for(int i=1;i<L+1;i++)
		for(int j=1;j<L+1;j++)
		{
			array[i][j].x = 0;            array[i][j].y = 0;
			array[i][j].attr = (rand())%2 + '0';
		}
	array[1][1].attr = '0';
}

int Findway() //非递归遍历找到出路
{
	list<struct data> lst;
	lst.push_back({1,1});
	array[1][1].access = 1;

	while(array[L][L].access == 0 && !lst.empty())
	{
		auto p = lst.begin();
		int x = p->x;
		int y = p->y;

		if(array[x][y-1].attr == '0' && array[x][y-1].access == 0)
		{
			lst.push_back({x,y-1});
			array[x][y-1].x = x;
			array[x][y-1].y = y;
			array[x][y-1].access = 1;
		}
		if(array[x][y+1].attr == '0' && array[x][y+1].access == 0)
		{
			lst.push_back({x,y+1});
			array[x][y+1].x = x;
			array[x][y+1].y = y;
			array[x][y+1].access = 1;
		}
		if(array[x-1][y].attr == '0' && array[x-1][y].access == 0)
		{
			lst.push_back({x-1,y});
			array[x-1][y].x = x;
			array[x-1][y].y = y;
			array[x-1][y].access = 1;
		}        if(array[x+1][y].attr == '0' && array[x+1][y].access == 0)
		{
			lst.push_back({x+1,y});
			array[x+1][y].x = x;
			array[x+1][y].y = y;
			array[x+1][y].access = 1;
		}
		lst.pop_front();
	}

	if(array[L][L].access == 1) 
	{
		for(int i=1;i<L+1;i++)
			for(int j=1;j<L+1;j++)
				array[i][j].access = 0;

		int i = L,j = L;
		while(1)
		{
			array[i][j].access = 1;
			int x = array[i][j].x;
			int y = array[i][j].y;
			i = x;
			j = y;
			if(i==1 && j==1)
				break;
		}
//	printf("\n");
		array[1][1].access = 1;
		return 1;
	}
	else
		return 0;
}

int main()
{
	srand(time(NULL));
	for(int i=rand()%1000;i<10000;i++)
	{        Init();
		creat_rand(i);
		if(Findway() == 1)
		{
			cout << "输入要创建到的文件名: " ;
			scanf("%s",name);
			FILE *infile = fopen(name,"w");
			for(int i=1;i<L+1;i++)
			{ 
				for(int j=1;j<L+1;j++)
				{
					if(array[i][j].attr == '0')
						fprintf(infile,"*");
					if(array[i][j].attr == '1')
						fprintf(infile,"#");
				}
				fprintf(infile,"\n");
			}
			fclose(infile);
			break;
		}
	}
	Print();
	FILE *outfile = fopen("outfile.txt","w");
	for(int i=1;i<L+1;i++)
	{
		for(int j=1;j<L+1;j++)
		{
			fprintf(outfile,"%d",array[i][j].access);
		}
		fprintf(outfile,"\n");
	}

	fclose(outfile);
	return 0;
}

