#include "Admin.h"
#include "Course.h"
#include <stack>
#include"Sqlite.h"
Sqlite sql;
const char* dir = R"(DS.db)";
using namespace std;
Admin ::Admin(void)
{
}

int Admin::findCourse(string code, vector<Course>& courses)
{

	for (int i = 0;i < courses.size();i++) {
		if (courses.at(i).code == code) {
			return i;
		}
	}
	return -1;
}

int Admin::findStudent(string code, vector<Student>& students, char op)
{
	if (op == 'i') {
		for (int i = 0;i < students.size();i++) {
			if (students.at(i).id == code) {
				return i;
			}
		}
		return -1;
	}
	else {
		for (int i = 0;i < students.size();i++) {
			if (students.at(i).name == code) {
				return i;
			}
		}
		return -1;
	}

}
int Admin::findAdmin(string name, vector<Admin>& admin)
{
	for (int i = 0;i < admin.size();i++) {
		if (admin.at(i).name == name) {
			return i;
		}
	}
	return -1;
}
string Admin::login(vector<Admin>& admin)
{


	string  name, pass;
	cout << "\t\t\t  Please Enter Admin Name and Password" << endl;
	cout << "Admin Name: ";
	cin.ignore();
	getline(cin, name, '\n');
	cout << endl << "Password: ";
	cin >> pass;

	
	int x = findAdmin(name, admin);
	if (x != -1) {
		if (name == admin.at(x).name && pass == admin.at(x).password) {

			cout << "\nLogged in Successfully!" << endl;
			return admin.at(x).name;
		}
		
		else if (name != admin.at(x).name && pass== admin.at(x).password) {

			cout << "\nUsername is incorrect!"<< endl;
			return "-1";
		}

		else if (name == admin.at(x).name && pass != admin.at(x).password) {

			cout << "\nPassword is incorrect!"<< endl;
			return "-1";
		}
		
		else {
			cout << "\nThere is something Wrong. Try Again!" << endl;
			return "-1";
		}
	}
	else {
		cout << "\nThere is something Wrong. Try Again!" << endl;
		return "-1";
	}
		

}

string Admin::ArrtoStr(vector<Course> &courses) {
	string str;
	for (int i = 0;i < courses.size();i++) {
		str = str + courses.at(i).code;
		if (i+1<courses.size()) {
			str = str + ",";
		}
	}
	return str;
}


void Admin::add_student(vector<Student> &students, vector<Course>& courses)
{
	Course c;
	Student s;
	cout << "Please enter the student's name: ";
	cin.ignore();
	getline(cin, s.name, '\n');
	while (findStudent(s.name, students, 'u') != -1) {
		cout << "\nThis Username already exisit: ";
		//cin.ignore();
		getline(cin, s.name, '\n');
	}
	//cout << endl;
	//cin >> s.name;
	cout << "Student's ID:";
	cin >> s.id;
	while (findStudent(s.id,students,'i') != -1) {
		cout << "\nThis ID already exisit: ";
		cin >> s.id;
	}
	//int index = findStudent(s.id, students);
	cout << "Enter password: "; 
	cin >> s.password;
	cout << "Enter the student's finished courses then enter q to finish: ";
	do {
		cin >> c.code;
		if (c.code != "q") {
			if (findCourse(c.code, courses) != -1) {
				s.courses_finished.push_back(c);

			}
			else {
				cout << "Enter a valid course: ";
			}
		}
	} while (c.code != "q");
	cout << "Enter the student's courses in progress then enter q to finish: ";
	do {
		cin >> c.code;
		if (c.code != "q") {
			int index=findCourse(c.code, courses);
			if (index != -1) {
				if (courses.at(index).current+1 <= courses.at(index).max) {
					bool pre = true;
					for (int i = 0;i < courses.at(index).pre_required.size();i++) {
						bool found = false;
						for (int j = 0;j < s.courses_finished.size();j++) {
							if (s.courses_finished.at(j).code == courses.at(index).pre_required.at(i).code) {
								found = true;
							}
						}if (!found) {
							cout << "You didn't meet the prerequisite for this course\n";
							pre = false;
							break;
						}
					}
					if (pre) {
						courses.at(index).current++;
						sql.updateDataCourse(dir, courses.at(index).name, courses.at(index).code, courses.at(index).max, courses.at(index).current, ArrtoStr(courses.at(index).pre_required), courses.at(index).hours, courses.at(index).code);
						s.courses_inprogress.push_back(c);
					}
				}
				else {
					cout << "This course is at maximum capacity" << endl;
				}
			}
			else {
				cout << "Enter a valid course: ";
			}
		}
	} while (c.code != "q");
	cout << "Academic year: ";
	cin >> s.year;
	students.push_back(s);
	sql.insertDataStudent(dir, s.name, s.id, s.year,s.password,ArrtoStr(s.courses_finished), ArrtoStr(s.courses_inprogress));
}

void Admin::add_course(vector<Course> &courses)
{
	Course c;
	cout << "Please enter the course's name: ";
	cin.ignore();
	getline(cin, c.name, '\n');
	//cout << endl;
	//cin >> c.name;
	cout << "course code: ";
	cin >> c.code;
	int index = findCourse(c.code, courses);
	if (index != -1) {
		cout << "This course already exists,please enter a new course: ";
		cout << "Please enter the course's name: ";
		cin.ignore();
		getline(cin, c.name, '\n');
		//cout << endl;
		//cin >> c.name;
		cout << "course code: ";
		cin >> c.code;
	}
	cout << "Maximum number of students for this course: ";
	cin >> c.max;
	c.current = 0;
	cout << "Number of hours: ";
	cin >> c.hours;
	courses.push_back(c);
	sql.insertDataCourse(dir, c.name, c.code,c.max,c.current,c.hours);
}

void Admin::add_prerequisite(string code, vector<Course> &courses)
{
	int counter = 0;
	int index = findCourse(code, courses);
	Course c;
	cout << "Enter the course's prerequisite then enter q to finish: ";
	do {
		cin >> c.code;
		if (c.code != "q") {
			if (findCourse(c.code, courses) != -1&&c.code!=code) {
				courses.at(index).pre_required.push_back(c);
				counter++;
			}
			else {
				cout << "Please enter a valid course" << endl;
				continue;
			}
		}
	} while (c.code != "q");
	if (counter != 0) {
		sql.updateDataCourse(dir, courses.at(index).name, courses.at(index).code, courses.at(index).max,courses.at(index).current, ArrtoStr(courses.at(index).pre_required), courses.at(index).hours, courses.at(index).code);
	}
}

void Admin::view_students_in(string code,vector<Course> &courses, vector<Student> &students)
{
	/*int x = -1;
	for (int i = 0; i <courses.size(); i++)
	{
		if (courses[i].code == code) {
			x = i;
		}
	}
	if (x == -1) {
		cout << "there is no course with this code\n";
		return;
	}*/
	if (findCourse(code, courses) == -1) {
		cout << "there is no course with this code\n";
		return;
	}
	for (int i = 0;i < students.size();i++) {
		for (int j = 0; j < students[i].courses_inprogress.size(); j++) {
			if (students[i].courses_inprogress[j].code == code) {
				cout << "Id: "<<students[i].id<<endl<<"Name: " << students[i].name<<endl;
				continue;
			}
		}
	}
}
void Admin::menu(vector<Admin>& admin, vector<Course>& courses, vector<Student>& students,string id)
{
	char choice;
	string code;
	int index;
	bool out = false;
	do{
		cout << "\n--------------------------------------------------------------------\n";
		cout << "Press 1 to Add new student" << endl;
		cout << "Press 2 to Add new course" << endl;
		cout << "Press 3 to Enter course prerequisite" << endl;
		cout << "Press 4 to View List of all students in a specific course" << endl;
		cout << "Press 5 to View List of all courses (Finished - Progressed) of a specific student" << endl;
		cout << "Press 6 to Edit all course data" << endl;
		cout << "Press 7 to Exit" << endl;
		cout << "\nYour choice: ";
		cin >> choice;
		switch (choice)
		{
		case '1':
			admin.at(0).add_student(students,courses);
			/*login(students);
			cout << "Please Login" << endl;
			cout << "Your username: ";
			cin >> userID;
			cout << "Your Password: ";
			cin >> password;
			int x = findStudent(id, students);

			if (userID == students.at(x).id && password == students.at(x).password) {

				cout << "Logged in Successfully!" << endl;
				return students.at(x).id;
			}
			else if (userID != students.at(x).id && password == students.at(x).password) {

				cout << "Username is incorrect!" << endl;


			}

			else if (userID == students.at(x).id && password != students.at(x).password) {

				cout << "Password is incorrect!" << endl;


			}
			else {
				cout << "There is something Wrong. Try Again!" << endl;

			}*/
			break;
		case '2':
			admin.at(0).add_course(courses);
			break;
		case '3':
			do {
				cout << "Please enter a valid code for the course: ";
				cin >> code;
				index = findCourse(code, courses);
			} while (index == -1);
			admin.at(0).add_prerequisite(code,courses);
			break;
		case '4':
			do {
				cout << "Please enter a valid code for the course: ";
				cin >> code;
				index = findCourse(code, courses);
			} while (index == -1);
			admin.at(0).view_students_in(code, courses,students);
			break;
		case '5':
			do {
				cout << "Please enter a valid id for the student: ";
				cin >> code;
				index = findStudent(code, students,'i');
			} while (index == -1);
			admin.at(0).view_all_student_courses(code, courses, students);
			break;
		case '6':
			do {
				cout << "Please enter a valid code for the course: ";
				cin >> code;
				index = findCourse(code, courses);
			} while (index == -1);
			admin.at(0).edit_course(code, courses);
			break;
		case '7':
			out = true;
			break;
		default:
			cout << "Please enter a valid choice\n";
		}
	} while(!out);
}
void Admin::view_all_student_courses(string id, vector<Course>& courses, vector<Student>& students)
{
	int x = findStudent(id,students,'i');
	/*for (int i = 0;i < students.size();i++) {
		if (students[i].id == id) {
			x = i;
		}
	}
	if (x == -1) {
		cout << "There is no student with this id";
		return;
	}*/
	cout << "courses finished: " << endl;
	for (int j = 0;j < students[x].courses_finished.size();j++) {
		cout << "Course " << j+1 << ": " << students[x].courses_finished[j].code<<endl;
	}
	cout << "courses inprogress: " << endl;
	for (int j = 0;j < students[x].courses_inprogress.size();j++) {
		cout << "Course " << j+1 << ": " << students[x].courses_inprogress[j].code<<endl;
	}
}
void Admin::edit_course(string code, vector<Course> &courses)
{
	int index = findCourse(code, courses);
	if (index == -1) {
		cout << "Please enter a valid course code"<<endl;
	}else{
		cout << "Please enter the course's name: ";
		cin.ignore();
		getline(cin, courses.at(index).name, '\n');
		//cout << endl;
		//cin >> courses.at(index).name;
		cout << "course code: ";
		cin >> courses.at(index).code;
		cout << "Maximum number of students for this course: ";
		cin >> courses.at(index).max;
		do {
			cout << "Current number of students for this course: ";
			cin >> courses.at(index).current;
		} while (courses.at(index).current > courses.at(index).max);
		cout << "Number of hours: ";
		cin >> courses.at(index).hours;
		sql.updateDataCourse(dir, courses.at(index).name, courses.at(index).code, courses.at(index).max, courses.at(index).current,ArrtoStr(courses.at(index).pre_required), courses.at(index).hours,code);
	}
	

}
Admin ::~Admin(void)
{
}
