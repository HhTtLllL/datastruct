#ifndef UNIONFIND_UNIONFIND4_H
#define UNIONFIND_UNIONFIND4_H

using namespace std;

namespace UF4
{
	class UnionFind
	{
		public:
			UnionFind(int n)
			{
				this->parent = new int[n];
				this->rank = new int[n];
				this->count = n;

				for( int i = 0 ; i < n ; i ++ )
				{
					parent[i] = i;
					rank[i] = 1;
				}
			}

			~UnionFind()
			{
				delete[] parent;
				delete[] rank;
			}

			int find(int p)
			{
				while( p != parent[p] )
				{
					p = parent[p];
				}

				return p;
			}

			bool isConnect(int p,int q)
			{
				return find(p) == find(q);
			}

			void unionElements( int p,int q )
			{
				int proot = find(p);
				int qroot = find(q);

				if(proot == qroot) return ;

				if( rank[proot] < rank[qroot])
				{
					parent[proot] = qroot;
				}
				else if(rank[qroot] < rank[proot])
				{
					parent[qroot] = proot;
				}
				else  //
				{
					parent[proot] = qroot;
					rank[qroot] += 1;

				}
				
				return ;
			}
		private:
			int *parent;
			int *rank; // rank[i] 表示以 i 为根的集合所表示的树的层数
			int count;

	};

}

#endif
