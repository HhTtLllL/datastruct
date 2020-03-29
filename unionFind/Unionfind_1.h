//##################################################################
// File Name: unionfind.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年03月28日 星期六 17时59分03秒
//=============================================================
//!/usr/bin/python

#ifndef UNIONFIND_UNIONFIND1_H
#define UNIONFIND_UNIONFIND1_H


#include <iostream>
#include <cassert>

using namespace std;

namespace UF1{
	class UnionFind
	{
		public:
			UnionFind( int n )
			{
				count = n;
				id = new int[n];

				for( int i = 0 ; i < n ; i ++ )
				{
					id[i] = i;
				}
			}
			~UnionFind()
			{
				delete[] id;
			}

			int find( int p )
			{
				return id[p];
			}

			bool isConnected( int p , int q ) 
			{
				return find(p) == find(q);
			}

			void unionElements( int p ,int q)
			{
				int pID = find(p);
				int qID = find(q);

				if(pID == qID) return ;

				for( int i = 0 ; i < count ; i ++ )
				{
					if( id[i] == pID) id[i] = qID;
				}

			}

		private:
			int* id;
			int count;

	};

}

#endif
