#ifndef GRAPH_DENSEGRAPH_H
#define GRAPH_DENSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//稠密图  --邻接矩阵
class DenseGraph
{
	public:
		DenseGraph( int n,bool directed )
		{
			this->n = n;
			this->m = 0;
			this->directed = directed;

			for( int i = 0 ; i < n ; i ++ )
			{
				g.push_back( vector<bool>(n,false));
			}
		}

		int V(){ return n; } 
		int E(){ return m; }

		void addEdge(int v ,int w)
		{
			if(hasEdge(v,w)) return ;


			//首先判断不会出界
			/*assert( v >= 0 && v < n); 由于hasEdge已经判断了边界情况，这里就不需要在做判断
			assert( w >= 0 && w < n);*/
			//有向图只加 1　条边
			g[v][w] = true;
			
			//如果是无向图,则还要增加 1 条边 
			if( !directed )
			{
				g[w][v] = true;
			}

			m++;
		}

		bool hasEdge( int v,int w)
		{
			assert( v >= 0 && v < n);
			assert( w >= 0 && w < n);

			return g[v][w];
		}

	private:
		int n,m; //点和边
		bool directed; //记录有向图还是无向图 true 为有向图
		vector<vector<bool>>  g;

};


#endif
