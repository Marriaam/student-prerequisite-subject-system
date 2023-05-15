#pragma once
#include <iostream>
#include <string>
#include<vector>
#include "Student.h"
#include "Course.h"
using namespace std;
class Admin
{
public:
	string name;
	string password;
	Admin();
	int findCourse(string code, vector<Course>& courses);
	int findStudent(string code, vector<Student>& students,char op);
	int findAdmin(string name, vector<Admin>& admin);
	string login(vector<Admin>& admin); //done
	string ArrtoStr(vector<Course>& courses);
	void add_student(vector<Student> &students, vector<Course>& courses); //Malak	done
	void add_course(vector<Course> &courses); //Malak	done
	void add_prerequisite(string code, vector<Course> &courses); //Youssef	done
	void view_all_student_courses(string id, vector<Course>& courses, vector<Student>& students); //Salma	done
	void edit_course(string code, vector<Course> &courses); //Youssef	done
	void view_students_in(string code,vector<Course> &courses, vector<Student>& students); //Salma	done
	void menu(vector<Admin>& admin, vector<Course>& courses, vector<Student>& students,string id);
	~Admin();
};