#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Calculation
{
	public:
		Calculation()
		{
			//TODO
		}

		double search_achieve(string name)
		{
			for( int i = 0 ; i < lesson_num_ ; i ++ )
			{
				if(cul[i].first == name) return cul[i].second;
			}

			return 0;
		}

		double average()
		{
			if(aver_) return aver_;

			double sum = 0;
			for( auto i : cul )
			{
				sum += i.second;
			}
			aver_ = sum/lesson_num_;

			return aver_;
		}

		string getname() 
		{
			return name;
		}

		void add_name(string name_temp)
		{
			name = name_temp;
		}

		void add_achieve(string lesson , double achieve )
		{
			cul.push_back( make_pair(lesson,achieve) );
		}

		void update_lesson_num( int num )
		{
			lesson_num_ = num;
		}

		/*void add_lesson(string name)
		{
			lesson_num++;
			lesson.push_back(name);
		}*/





	private:
		vector<pair<string,double>> cul;
		string name; //人名
		int lesson_num_;
		double aver_ = 0;

};


#endif
