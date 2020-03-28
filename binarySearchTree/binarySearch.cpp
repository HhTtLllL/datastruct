//##################################################################
// File Name: binarySearch.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年03月27日 星期五 22时26分49秒
//=============================================================
//!/usr/bin/python

#include <iostream>
#include <algorithm>

using namespace std;

//lower_bound,upper_bound

//二分查找法，在有序数组arr中，查找target
//如果没有找到target，返回相应的索引index
//如果没有找到target,返回 -1
template<typename T>
int binarySearch(T arr[], int n, T target)
{
	//在arr[l..r]之中查找target
	int l = 0,r = n-1;

	while(l <= r)
	{
		//int mid = (l+r)/2; //当l 和 r 都成为int 的最大范围时，会整形溢出，所以这里最好使用 减法
		int mid = l + (r-l)/2;

		if( arr[mid] == target ) return mid;

		if(target < arr[mid])
			//这里需不需要有 -1 需要判断在查找区间内，是否已经查找过 mid
			r = mid - 1;
		
		else //(target > arr[mid])
			l = mid + 1; //这里是否 + 1也是需要判断，需要判断在查找区间内，是否已经查找过mid
	}

	return -1;
}

int main()
{
	int a[10] = {1,1,2,2,3,3,5,5};

	cout << lower_bound(a,a+10,4) - a << endl;
	cout << upper_bound(a,a+10,4) - a << endl;


	//cout << binarySearch(a,5,3) << endl;; 


	return 0;
}
