#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include <stack>
#include <string.h>

using namespace std;
class Student
{
public:
	string name;
	string id;
	string password;
	string year;
	vector<Course> courses_finished; 
	vector<Course> courses_inprogress;
	Student();
	string ArrtoStr(vector<Course>& courses);
	int findCourse(string code, vector<Course>& courses);
	int findStudent(string code, vector<Student>& students,char op);
	string login(vector<Student>& students); //done
	void view_available(vector<Course> &courses); //Hana done
	void view_details(int index, vector<Course> &courses); //Hana done
	void register_course(string code, vector<Course>& courses, vector<Student>& students); //Tony done
	void view_all(string id , vector<Student>& students, vector<Course>& courses); //Yumyum done
	void edit_data(string id ,vector<Student> &students);  //Alia done
	void menu(vector<Course>& courses, vector<Student>& students,string id);
	~Student();
};

