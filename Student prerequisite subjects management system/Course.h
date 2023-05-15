#pragma once
#include <iostream>
#include <string>
#include<vector>
#include<queue>
using namespace std;
class Course
{
public:
	string name;
	string code;
	int max;//comment H
	int current=0;
	vector<Course> pre_required;  //Quene
	string hours;
	Course();
	~Course();
	//Q

};

