#include <sqlite3.h>
#include <stdio.h>
#include<string>
#include <iostream>
#include "Sqlite.h"
#include "Course.h"
#include"Admin.h"
#include"Course.h"

using namespace std;

// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
int Sqlite::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		// column name and value
		cout << azColName[i] << ": " << argv[i] << endl;
	}

	cout << endl;

	return 0;
}
Sqlite::Sqlite(void) {

}

int Sqlite::createDB(const char* s)
{
	sqlite3* DB;

	int exit = 0;
	exit = sqlite3_open(s, &DB);

	sqlite3_close(DB);

	return 0;
}

int Sqlite::createTable(const char* s, const char* sql1)
{
	sqlite3* DB;
	char* messageError;
	string sql = sql1;


	try
	{
		int exit = 0;
		exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error in createTable function." << endl;
			sqlite3_free(messageError);
		}
		else
			//cout << "Table created Successfully" << endl;
		sqlite3_close(DB);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
}

int Sqlite::insertDataAdmin(const char* s,string name, string password)
{

	sqlite3* DB;
	char* messageError;

	string sql("INSERT INTO ADMIN (NAME, PASSWORD) VALUES('" + name + "', '" + password + "');");

	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in insertData function." << endl;
		sqlite3_free(messageError);
	}
	else
		//cout << "Records inserted Successfully!" << endl;

	return 0;
}
int Sqlite::insertDataStudent(const char* s,string name, string id, string year, string password, string finished, string inprogress) {
	sqlite3* DB;
	char* messageError;

	string sql("INSERT INTO STUDENT (ID, NAME, FINISHED, INPROGRESS, YEAR, PASSWORD) VALUES('"+id+"', '"+ name +"', '" + finished + "', '" + inprogress + "','"+year+"', '" + password + "');");

	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in insertData function." << endl;
		sqlite3_free(messageError);
	}
	else
		//cout << "Records inserted Successfully!" << endl;

	return 0;
}
int Sqlite::insertDataCourse(const char* s, string name, string code, int maximum, int current, string hours) {
	sqlite3* DB;
	char* messageError;

	string sql("INSERT INTO COURSE (CODE, NAME, MAX, CURRENT, HOURS) VALUES('"+ code +"', '"+ name +"', '" + to_string(maximum) + "', '" + to_string(current) + "', '" + hours + "');");

	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in insertData function." << endl;
		sqlite3_free(messageError);
	}
	else
		//cout << "Records inserted Successfully!" << endl;

	return 0;
}

int Sqlite::updateDataStudent(const char* s, string name, string id, string year, string password, string finished, string inprogress)
{
	sqlite3* DB;
	char* messageError;


	string sql("UPDATE STUDENT SET NAME = '" + name + "', YEAR = '" + year + "', PASSWORD = '" + password + "', FINISHED = '" + finished + "', INPROGRESS = '" + inprogress + "' WHERE ID = '" + id + "'");

	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in updateData function." << endl;
		sqlite3_free(messageError);
	}
	else
		//cout << "Records updated Successfully!" << endl;

	return 0;
}

int Sqlite::updateDataCourse(const char* s, string name, string code, int maximum, int current, string prerequired, string hours,string query)
{
	sqlite3* DB;
	char* messageError;
	string sql("UPDATE COURSE SET NAME = '"+ name +"', MAX = '" + to_string(maximum) + "', CURRENT = '" + to_string(current) + "', PREREQ = '" + prerequired + "', HOURS = '" + hours + "', CODE = '" + code + "' WHERE CODE = '"+query+"'");

	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in updateData function." << endl;
		sqlite3_free(messageError);
	}
	else
		//cout << "Records updated Successfully!" << endl;

	return 0;
}

int Sqlite::deleteData(const char* s, string table)
{
	sqlite3* DB;
	char* messageError;
	string sql = "DELETE FROM "+ table +";";

	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in deleteData function." << endl;
		sqlite3_free(messageError);
	}
	else
		//cout << "Records deleted Successfully!" << endl;

	return 0;
}

int Sqlite::selectData(const char* s,string table)
{
	sqlite3* DB;
	char* messageError;
	string sql = "SELECT * FROM "+table+";";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in selectData function." << endl;
		sqlite3_free(messageError);
	}
	else
		//cout << "Records selected Successfully!" << endl;
	return 0;
}

void Sqlite::StrtoArr(string s, vector<Course>& courses)
{
	Course c;
	size_t pos = 0;
	string token1;
	string delim = ",";
	while ((pos = s.find(delim)) != std::string::npos)
	{
		token1 = s.substr(0, pos);
		s.erase(0, pos + delim.length());
		c.code = token1;
		if (c.code != "") {
			courses.push_back(c);
		}
	}
	c.code = s;
	if (c.code != "") {
		courses.push_back(c);
	}
}



int Sqlite::loadFromDB(vector<Student>& students, vector<Course>& courses, vector<Admin>& admins)
{
	sqlite3* DB;
	sqlite3_stmt* stmt;
	int exit = sqlite3_open(R"(DS.db)", &DB);
	string statement = "SELECT * FROM ADMIN;";
	int rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, nullptr);
	if (rc != SQLITE_OK) {
		// handle the error
	}
	// Loop through the results, a row at a time.
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		Admin a;
		a.name = (const char*)sqlite3_column_text(stmt, 0);
		a.password = (const char*)sqlite3_column_text(stmt, 1);
		admins.push_back(a);
	}
	sqlite3_finalize(stmt);

	statement = "SELECT * FROM STUDENT;";
	rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, nullptr);
	if (rc != SQLITE_OK) {
		// handle the error
	}
	// Loop through the results, a row at a time.
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		Student s;
		s.id = (const char*)sqlite3_column_text(stmt, 0);
		s.name = (const char*)sqlite3_column_text(stmt, 1);
		StrtoArr((const char*)sqlite3_column_text(stmt, 2),s.courses_finished);
		StrtoArr((const char*)sqlite3_column_text(stmt, 3), s.courses_inprogress);
		s.year = (const char*)sqlite3_column_text(stmt, 4);
		s.password = (const char*)sqlite3_column_text(stmt, 5);
		students.push_back(s);
	}
	// Free the statement when done.
	sqlite3_finalize(stmt);

	statement = "SELECT * FROM COURSE;";
	rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, nullptr);
	if (rc != SQLITE_OK) {
		// handle the error
	}
	// Loop through the results, a row at a time.
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		Course c;
		const char* d = "";
		const char* s = (const char*)sqlite3_column_text(stmt, 3);
		c.code = (const char*)sqlite3_column_text(stmt, 0);
		c.name = (const char*)sqlite3_column_text(stmt, 1);
		c.max = sqlite3_column_int(stmt, 2);
		c.current= sqlite3_column_int(stmt, 3);
		if ((const char*)sqlite3_column_text(stmt, 4) != NULL&&strcmp(d,s)==-1) {
			StrtoArr((const char*)sqlite3_column_text(stmt, 4), c.pre_required);
		}
		c.hours = (const char*)sqlite3_column_text(stmt, 5);
		courses.push_back(c);
	}
	// Free the statement when done.
	sqlite3_finalize(stmt);

	return 0;
}

Sqlite ::~Sqlite(void)
{
}
