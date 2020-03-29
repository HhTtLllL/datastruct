#ifndef UNIONFIND_UNIONFIND3_H
#define UNIONFIND_UNIONFIND3_H

using namespace std;

namespace UF3
{
	class UnionFind
	{
		public:
			UnionFind(int n)
			{
				this->parent = new int[n];
				this->sz = new int[n];
				this->count = n;

				for( int i = 0 ; i < n ; i ++ )
				{
					parent[i] = i;
					sz[i] = 1;
				}
			}

			~UnionFind()
			{
				delete[] parent;
				delete[] sz;
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

				if( sz[proot] < sz[qroot])
				{
					parent[proot] = qroot;
					sz[qroot] += sz[proot];
				}
				else
				{
					parent[qroot] = proot;
					sz[proot] += sz[qroot];
				}
			
				//	qroot = parent[proot];

				return ;
			}
		private:
			int *parent;
			int *sz; //sz[i]表示以 i 为根的集合元素个数
			int count;

	};

}

#endif
