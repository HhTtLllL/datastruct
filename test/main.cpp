//##################################################################
// File Name: main.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年04月07日 星期二 17时10分35秒
//=============================================================
//!/usr/bin/python

#include <iostream>
#include "Calculation.h"
#include "Common.h"


vector<string> lesson;
int lesson_num;
int student_num;

int main()
{
	vector<Calculation> sum;
	vector<string> lesson; 
	
	
	cout << "请输入一共有多少个同学:";
	cin >> student_num;
	
	sum = vector<Calculation>(student_num);

	cout << "输入一共有几科课程:";
	cin >> lesson_num;

	for( int i = 0 ; i < student_num ; i ++ )
	{
		sum[i].update_lesson_num(lesson_num);
	}


	for( int i = 0 ; i < lesson_num ; i ++ )
	{
		string temp;
		printf("请输入课程名:");
		cin >> temp;
		lesson.push_back(temp);
	}

	cout << "开始录入信息...\n" << endl;
	
	for( int i = 0 ; i < student_num ; i ++ )
	{
		cout << "输入学生姓名:";
	
		string name_temp;
		
		cin >> name_temp;
		sum[i].add_name(name_temp);


		for( int j = 0 ; j < lesson.size() ; j ++ )
		{
			cout << "请输入" << lesson[j] << "的成绩:";
			double temp;
			cin >> temp;
			sum[i].add_achieve(lesson[j] , temp);
		}
	}


	int select = 0;

	while(1)
	{
		cout << "\n输入0 退出程序....\n";
		cout << "1. 求某个学生的平均成绩\n";
		cout << "2. 求某一课的最高成绩\n";
		cout << "3. 求某一课的最低成绩\n";
		cout << "输入选项:";
		cin >> select;

		switch(select)
		{
			case 1 : 
				cul_aver(sum,student_num); break;
			case 2:
				high_aver(sum,student_num);break;
			case 3:
				low_aver(sum,student_num);break;
		}
		
		if(select == 0) break;
	}
	
	return 0;
}


