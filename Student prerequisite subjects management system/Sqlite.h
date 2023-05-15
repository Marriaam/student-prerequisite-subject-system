#pragma once
#include "sqlite3.h"
#include <string>
#include<vector>
#include<string.h>
#include"Admin.h"
#include"Course.h"
#include"Student.h"

class Sqlite
{
public:
	Sqlite();
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	static int createDB(const char* s);
	static int createTable(const char* s, const char* sql);
	static int deleteData(const char* s, std::string table);

	static int insertDataAdmin(const char* s, std::string name, std::string password);
	static int insertDataStudent(const char* s,std::string name, std::string id, std::string year, std::string password, std::string finished, std::string inprogress);
	static int insertDataCourse(const char* s,std::string name, std::string code, int maximum, int current, std::string hours);

	static int updateDataCourse(const char* s, std::string name, std::string code, int maximum, int current, std::string prerequired, std::string hours,std::string query);
	static int updateDataStudent(const char* s, std::string name, std::string id, std::string year, std::string password, std::string finished, std::string inprogress);

	static int selectData(const char* s,std::string table);

	static void StrtoArr(string s, vector<Course>& courses);
	
	static int loadFromDB(vector<Student>& students, vector<Course>& courses, vector<Admin>& admins);
	~Sqlite(void);
};