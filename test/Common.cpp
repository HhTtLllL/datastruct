//##################################################################
// File Name: Common.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年04月08日 星期三 01时38分23秒
//=============================================================
//!/usr/bin/python

#include "Common.h"


void cul_aver(vector<Calculation>& sum,int student_num)
{
	cout << "输入学生名字:";
	string name;
	cin >> name;

	for( int i = 0 ; i < student_num ; i ++ )
	{
		if(name == sum[i].getname())
		{
			cout << name << " 的平均成绩为 " << sum[i].average() << endl;
		}
	}
}

void high_aver( vector<Calculation>& sum ,int student_num)
{
	cout << "输入课程名称: ";
	string search_lesson;
	cin >> search_lesson;

	double temp_high = -1;

	for( int i = 0 ; i < student_num ; i ++ )
	{
		temp_high = max(temp_high,sum[i].search_achieve(search_lesson));
	}

	cout << "最高成绩为 " << temp_high << endl;

}

void low_aver( vector<Calculation>& sum ,int student_num)
{
	cout << "输入课程名称:";
	string search_lesson;
	cin >> search_lesson;

	double temp_high = 10000000;

	for( int i = 0 ; i < student_num ; i ++ )
	{
		temp_high = min(temp_high,sum[i].search_achieve(search_lesson));
	}

	cout << "最低成绩为 " << temp_high << endl;

}


