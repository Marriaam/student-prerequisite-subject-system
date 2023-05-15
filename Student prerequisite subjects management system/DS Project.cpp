#include <iostream>
#include "sqlite3.h"
#include <cstdlib>
#include <vector>
#include"Sqlite.h"
#include "Student.h"
#include "Admin.h"
using namespace std;
int main() {
	vector <Course> c;
	vector <Admin> a;
	vector <Student> s;
	/*Admin a1;
	Student s1;
	Course c1;
	a.push_back(a1);
	c.push_back(c1);
	s.push_back(s1);*/
	//a.at(0).add_course(c);
	//a.at(0).add_student(s);
	const char* dir = R"(DS.db)";
	Sqlite sql;
	sql.loadFromDB(s, c, a);
	//sql.insertDataAdmin(dir, "Youssef", "admin");
	//sql.deleteData(dir, "COURSE");
	//a.at(0).login(a);
	//s.at(0).login(s);
	//a.at(0).view_all_student_courses("30", c, s);
	//a.at(0).add_course(c);
	//a.at(0).add_student(s,c);
	//s.at(0).edit_data(s.at(0).id, s,c);
	//s.at(0).register_course("24", c, s);
	//s.at(0).view_all("22", s,c);
	//cout << s.at(5).courses_finished.size() << endl;
	//cout << s.at(5).courses_inprogress.size() << endl;
	//a.at(0).edit_course("404", c);
	//a.at(0).add_prerequisite("e", c);
	//a.at(0).add_prerequisite("606", c);
	//cout << a.at(0).name <<" "<< a.at(0).password << endl;
	//cout << s.at(0).name << " " << s.at(0).password << " " << endl;
	//cout << s.at(0).courses_finished.at(0).code << " " << s.at(0).courses_inprogress.at(1).code << endl;
	//if (!c.at(0).pre_required.empty()) {
		//cout << c.at(0).name << " " << c.at(0).pre_required.at(0).code << endl;
	//}
	//a.at(0).ArrtoStr(s.at(0).courses_finished);
	//a.at(0).view_students_in("5", c,s);
	/*const char* sql1 = "CREATE TABLE IF NOT EXISTS ADMIN("
		"NAME      TEXT NOT NULL, "
		"PASSWORD     TEXT NOT NULL);";
	sql.createDB(dir);
	sql.createTable(dir,sql1);
	sql1 = "CREATE TABLE IF NOT EXISTS STUDENT("
		"ID		TEXT NOT NULL, "
		"NAME      TEXT NOT NULL, "
		"FINISHED	TEXT NOT NULL, "
		"INPROGRESS	TEXT NOT NULL, "
		"YEAR	TEXT NOT NULL, "
		"PASSWORD     TEXT NOT NULL);";
	sql.createDB(dir);
	sql.createTable(dir, sql1);
	sql1 = "CREATE TABLE IF NOT EXISTS COURSE("
		"CODE TEXT NOT NULL, "
		"NAME      TEXT NOT NULL, "
		"MAX      INTEGER NOT NULL, "
		"CURRENT      INTEGER NOT NULL, "
		"PREREQ      TEXT, "
		"HOURS     TEXT NOT NULL);";
	sql.createDB(dir);
	sql.createTable(dir, sql1);*/
	//s.deleteData(dir,"ADMIN"); 
	//sql.insertDataAdmin(dir,"Mohamed", "pass123"); 
	//sql.insertDataStudent(dir, "Youssef", "1", "pass", "101,404", "202");
	//s.updateData(dir);
	//sql.selectData(dir,"ADMIN");
	//sql.selectData(dir, "STUDENT");*/
	char choice;
	cout << "Welecome to Student Prerequisite Subjects Management System\n";
	cout << "Press 1 to login as admin or Press 2 to login as student: ";
	cin >> choice;
	if (choice == '1') {
		if (!a.empty()) {
			string id = a.at(0).login(a);
			if (id!= "-1") {
				a.at(0).menu(a, c, s,id);
			}
		}
		else {
			cout << "There is no registered admins\n";
		}
	}
	else if (choice == '2') {
		if (!s.empty()) {
			string id = s.at(0).login(s);
			if (id != "-1") {
				s.at(0).menu(c, s,id);
			}
		}
		else {
			cout << "There is no registered students\n";
		}
		
	}
}

