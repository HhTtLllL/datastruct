#ifndef GRAPH_SPARSEGRAPH_H
#define GRAPH_SPARSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//稀疏图 --邻接表
//缺点: 不能解决平行边的问题，需要自己实现
//
class SparseGraph
{
	public:
		SparseGraph( int n,bool directed )
		{
			this->n = n;
			this->m = 0;
			this->directed = directed;

			for( int i = 0 ; i < n ; i ++ )
			{
				g.push_back( vector<int> () );
			}
		}

		~SparseGraph()
		{

		}

		int E()
		{
			return n;
		}

		int V()
		{
			return m;
		}

		void addEdge( int v,int w )
		{

			hasEdge(v,w);

			//判断已经存在这条边
			//assert( v >= 0 && v < n );
			//assert( w >= 0 && w < n );

			g[v].push_back(w);
			
			//如果v == w,则为自环边
			if( v != w && !directed ) g[w].push_back(v);  //如果是有向图

			m ++;
		}

		bool hasEdge( int v ,int w )
		{
			assert( v >= 0 && v < n );
			assert( w >= 0 && w < n );

			for( int i = 0 ; i < g[v].size() ; i ++ )
			{
				if(g[v][i] == w) return ture;
			}
			
			return false;
		}



	private:
		int n,m;
		vector<vector<int>> g;
		bool directed; //代表是否为有向图

};


#endif
