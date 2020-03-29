#ifndef UNIONFIND_UNIONFIND_2_H
#define UNIONFIND_UNIONFIND_2_H

namespace UF2
{
	class UnionFind
	{
		public:
			UnionFind( int count )
			{
				parent = new int[count];
				this->count = count;
				for( int i = 0 ; i < count ; i ++ )
				{
					parent[i] = i;
				}
			}
			~UnionFind()
			{
				delete[] parent;
			}

			int find( int p )
			{
				while( p != parent[p])
				{
					p = parent[p];
				}

				return p;
			}

			bool isConnected( int p, int q)
			{
				return find(p) == find(q);
			}

			void unionElements( int p,int q)
			{
				int proot = find(p); //找到p 元素对应的根
				int qroot = find(q);

				if( proot == qroot) return ;

				
				parent[proot] = qroot;

				return ;
			}


		private:
			int *parent;
			int count;
	};
}


#endif //UNIONFIND_UNIONFIND_2_H
