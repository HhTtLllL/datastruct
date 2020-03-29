//##################################################################
// File Name: main.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年03月29日 星期日 16时19分48秒
//=============================================================
//!/usr/bin/python

#include <iostream>
#include "UnionfindTest.h"


//经过路径压缩后，并查集的操作，时间复杂度几乎是O(1)的。

using namespace std;

int main()
{

	int n = 100000000;
	//UnionfindTest::testUF1(n);
	//UnionfindTest::testUF2(n);
	//UnionfindTest::testUF3(n);
	UnionfindTest::testUF4(n);
	UnionfindTest::testUF5(n);

	return 0;
}
