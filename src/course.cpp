#include<iostream>
#include<vector>
class Course{
	std::string courseCode;
	std::string courseName;
	std::string studentnumber;
	//Teacher t1;
	// vector<Student>s1;
	// vector<Assessment>a1;
public:
	Course(){}
	Course(std::string code,std::string sid){
	courseCode = code;
	studentnumber = sid;
	}
	// void add_students(Student s2){
	// s1.push_back(s2);
	// }
	// void add_assessment(Assessment a2){
	// a1.push_back(a2);
	// }
};
