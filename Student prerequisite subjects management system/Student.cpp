#include "Student.h"
#include "Admin.h"
#include <stack>
#include"Sqlite.h"
Sqlite sql1;
const char* dir1 = R"(DS.db)";
using namespace std;

Student::Student(void)
{
}
string Student::ArrtoStr(vector<Course>& courses)
{
	string str;
	for (int i = 0;i < courses.size();i++) {
		str = str + courses.at(i).code;
		if (i + 1 < courses.size()) {
			str = str + ",";
		}
	}
	return str;
}

int Student::findCourse(string code, vector<Course>& courses)
{
	for (int i = 0;i < courses.size();i++) {
		if (courses.at(i).code == code) {
			return i;
		}
	}
	return -1;
}


int Student::findStudent(string code, vector<Student>& students,char op)
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


string Student::login(vector<Student>& students)
{
	string userID, password;

	cout << "\t\t\t  Please Enter Username and Password" << endl;
	cout << "Username: ";
	cin.ignore();
	getline(cin, userID, '\n');
	cout << endl << "Password: ";
	cin >> password;

	int x = findStudent(userID, students,'u');
	if (x != -1) {
		if (userID == students.at(x).name && password == students.at(x).password) {

			cout << "Logged in Successfully!" << endl;
			return students.at(x).name;
		}
		else if (userID != students.at(x).name && password == students.at(x).password) {

			cout << "Username is incorrect!" << endl;
			return "-1";

		}
		else if (userID == students.at(x).name && password != students.at(x).password) {

			cout << "Password is incorrect!" << endl;
			return "-1";


		}
		else {
			cout << "There is something Wrong. Try Again!" << endl;
			return "-1";

		}
	}
	else {
		cout << "There is something Wrong. Try Again!" << endl;
		return "-1";
	}
}

void Student::view_available(vector<Course>& courses)
{
	int num = 1;
	cout << "Available courses: " << endl;
	for (int i = 0; i < courses.size(); i++) {
		if (courses[i].current < courses[i].max) {
			cout << "Course " << num << ":\n" << "\tName: " << courses[i].name << "\n\tCode: " << courses[i].code << endl;
			num++;
		}
	}
}

void Student::view_details(int index, vector<Course>& courses)
{
		cout << "Name: " << courses.at(index).name << endl;
		cout << "Code: " << courses.at(index).code << endl;
		cout << "Hours required: " << courses.at(index).hours << endl;
		if (ArrtoStr(courses.at(index).pre_required).empty()) {
			cout << "Prerequired: None";
		}
		else {
			cout << "Prerequired: " << ArrtoStr(courses.at(index).pre_required) << endl;
		}
}

void Student::register_course(string code, vector<Course>& courses, vector<Student>& students)
{
	cout << "\t\t\tRegister a course: " << endl;
	cout << "\t\t\t------------------\n\n" << endl;
	Course c;
	cout << "Please enter the course code or q to exit: ";
	cin >> c.code;
	int indexs = findStudent(code, students,'u');
	while (true)
	{

		if (c.code == "q") {
			break;
		}
		int index = findCourse(c.code, courses);
		if (index == -1) {
			cout << "Invalid course code,please enter a new course or q to exit: ";
			cin >> c.code;
		}
		else if (findCourse(c.code, students.at(indexs).courses_inprogress) != -1) {
			cout << "This course already exists,please enter a new course or q to exit: ";
			cin >> c.code;
		}
		else if (findCourse(c.code, students.at(indexs).courses_finished) != -1) {
			cout << "This course already have been completed, please enter a new course or q to exit: ";
			cin >> c.code;
		}
		else if (courses.at(index).current >= courses.at(index).max) {
			cout << "This course is full, please enter a new course or q to exit: ";
			cin >> c.code;
		}
		else {
			bool pre = true;
			for (int i = 0;i < courses.at(index).pre_required.size();i++) {
				bool found = false;
				for (int j = 0;j < students.at(indexs).courses_finished.size();j++) {
					if (students.at(indexs).courses_finished.at(j).code == courses.at(index).pre_required.at(i).code) {
						found = true;
					}
				}if (!found) {
					cout << "You didn't meet the prerequisite for this course\n";
					pre = false;
					break;
				}
			}
			if (pre) {
				students.at(indexs).courses_inprogress.push_back(c);
				courses.at(index).current++;
				cout << "Registered Successfully" << endl;
				sql1.updateDataCourse(dir1, courses.at(index).name, courses.at(index).code, courses.at(index).max, courses.at(index).current, ArrtoStr(courses.at(index).pre_required), courses.at(index).hours, courses.at(index).code);
				sql1.updateDataStudent(dir1, students.at(indexs).name, students.at(indexs).id, students.at(indexs).year, students.at(indexs).password, ArrtoStr(students.at(indexs).courses_finished), ArrtoStr(students.at(indexs).courses_inprogress));
				break;
			}
			else {
				break;
			}
		}
	}
}

void Student::view_all(string id, vector<Student>& students, vector<Course>& courses)
{
	int index = findStudent(id, students,'u');
	cout << "Finished Courses: " << endl;
	if (students[index].courses_finished.size() == 0) {
		cout << "\tNo courses finished yet\n";
	}
	for (int i = 0; i < students[index].courses_finished.size(); i++) {
		string code = students[index].courses_finished[i].code;
		int course_index = findCourse(code, courses);
		cout << courses[course_index].code << " : " << courses[course_index].name << endl;
	}
	cout << "Inprogress Courses: " << endl;
	if (students[index].courses_inprogress.size() == 0) {
		cout << "\tNo courses inprogress yet\n";
	}
	for (int i = 0; i < students[index].courses_inprogress.size(); i++) {
		string code = students[index].courses_inprogress[i].code;
		int course_index = findCourse(code, courses);
		cout << "\tcode: " << courses[course_index].code << "\n\tname: " << courses[course_index].name << endl;
	}

}

void Student::edit_data(string id, vector<Student>& students)
{
	int x = findStudent(id, students,'u');
	int year;
	string name;
	cout << "Enter New Name: ";
	cin.ignore();
	getline(cin, name, '\n');

	while (findStudent(name, students, 'u') != -1) {
		cout << "\nThis Name already exisit: ";
		//cin.ignore();
		getline(cin,name, '\n');
		//getline(cin, students.at(x).name, '\n');
	}
	students.at(x).name=name;
	//cout << endl;
	//cin >> students.at(x).name;
	cout << "Enter New Password:";
	cin >> students.at(x).password;
	/*cout << "Enter New Finished Courses then enter q to finish: " << endl;
	students.at(x).courses_finished.clear();
	do {
		cin >> c.code;
		int counter = 0;
		if (c.code != "q") {
			int index = findCourse(c.code, courses);
			if (index != -1) {
				students.at(x).courses_finished.push_back(c);
				counter++;
			}
			else {
				cout << "Enter a valid course" << endl;
			}
		}
	} while (c.code != "q");

	cout << "Enter New Courses in Progress then enter q to finish: " << endl;
	for (int i = 0; i < students.at(x).courses_inprogress.size(); i++) {
		courses.at(findCourse(students.at(x).courses_inprogress.at(i).code, courses)).current--;
	}
	students.at(x).courses_inprogress.clear();
	do {
		cin >> c.code;
		int counter = 0;
		if (c.code != "q") {
			int index = findCourse(c.code, courses);
			if (index != -1) {
				if (courses.at(index).current + 1 <= courses.at(index).max) {
					students.at(x).courses_inprogress.push_back(c);
					courses.at(index).current++;
					counter++;
					sql1.updateDataCourse(dir1, courses.at(index).name, courses.at(index).code, courses.at(index).max, courses.at(index).current, ArrtoStr(courses.at(index).pre_required), courses.at(index).hours, courses.at(index).code);
				}
				else {
					cout << "This course is at maximum capacity" << endl;
				}
			}
			else {
				cout << "Enter a valid course" << endl;
			}
		}
	} while (c.code != "q");
	*/
	do {
		cout << "Enter New Academic Year: ";
		cin >> year;
	} while (year < 2016 && year > 2022);
	students.at(x).year =to_string(year);
	sql1.updateDataStudent(dir1, students.at(x).name, students.at(x).id, students.at(x).year, students.at(x).password, ArrtoStr(students.at(x).courses_finished), ArrtoStr(students.at(x).courses_inprogress));
}

void Student::menu(vector<Course>& courses, vector<Student>& students,string id)
{
	char choice;
	string code;
	int index;
	bool out = false;
	
	do{
		cout << "\n--------------------------------------------------------------------\n";
		cout << "Press 1 to View List of all available courses" << endl;
		cout << "Press 2 to View details of a specific course" << endl;
		cout << "Press 3 to Register for a course" << endl;
		cout << "Press 4 to View all of your courses" << endl;
		cout << "Press 5 to Edit your data" << endl;
		cout << "Press 6 to Exit" << endl;
		cout << "\nYour choice: ";

		cin >> choice;
		switch (choice)
		{
		case '1':
			students.at(0).view_available(courses);
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
			do {
				cout << "Please enter a valid code for the course: ";
				cin >> code;
				index = findCourse(code, courses);
			} while (index == -1);
			students.at(0).view_details(index, courses);
			break;
		case '3':
			students.at(0).register_course(id, courses, students);
			break;
		case '4':
			students.at(0).view_all(id, students, courses);
			break;
		case '5':
			students.at(0).edit_data(id, students);
			break;
		case '6':
			out = true;
			break;
		default:
			cout << "Please enter a valid choice\n";
		}
	}while(!out);
}	
Student::~Student(void)
{
}
