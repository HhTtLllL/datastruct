#include <stdio.h>
#include <queue>
#include <string.h>

using namespace std;

int a[400][400];
int book[25];
char  pot[25];
int n,m;

void dfs(int step)
{
	book[step] = 1;
	for(int i = 0;i < n;i++)
	{
		if(!book[i] && a[step][i])
		{
			dfs(i);
		}
	}


}

int main()
{
	scanf("%d%d",&n,&m);
	getchar( );
	for(int i = 0;i < n;i++) scanf("%c",&pot[i]);
	getchar();
	for(int i = 0;i < m;i++)
	{
		char temp1,temp2;
		scanf("%c%c",&temp1,&temp2);
		getchar();
		a[temp1 - 'A'][temp2 - 'A'] = 1;
	}
/*	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			if(i == j) a[i][j] = 1;
		}
	}
*/


	int cnt = 0;
	for(int i = 0;i < n;i++)
	{
		if(book[i] == 0) 
		{
			dfs(i);
			cnt++;
		}
	}

	printf("%d\n",cnt);

	return 0;
}

