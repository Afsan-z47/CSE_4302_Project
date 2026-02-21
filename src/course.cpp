#include"user.h"
#include<iostream>
#include <vector>
#include "grade.cpp"
#include<iomanip>
class Course{
	std::string courseCode;
	std::string courseName;
	std::string studentnumber;
	std::string instructorName;
	std::vector<Grade>g1;
	std::vector<Student>s1;
	std::vector<Assessment>a1;
public:
	Course(){}
	Course(std::string code,std::string sid){
	courseCode = code;
	studentnumber = sid;
	}
	void add_students(const Student &s2){
	s1.push_back(s2);
	 }
	void add_assessment(const Assessment &a2){
	a1.push_back(a2);
	}
	void setCourseInfo(const std::string &id,const std::string &name,const std::string &instructor){
	courseCode = id;
	courseName = name;
	instructorName = instructor;
	}
	void displayCourseInfo()const{
	std::cout<<"Course Id: "<<courseCode<<"| Course Name: "<<courseName<<"| Instructor Name: "<<instructorName<<" | number of students: "<<s1.size()<<"\n";
	}
	void search_student(Assessment& assessments,Student& students,std::string id)const{
	for(int i = 0;i<s1.size();i++){
	if(id == students.getID()){
	assessments = a1[i];
	students = s1[i];
	return;
	}
	}
	}
	void displayStudentInfo()const{
	std::cout<<"Enter the student ID to search for: ";
	std::string id;
	std::cin>>id;
	Assessment assessments;
	Student students;
	search_student(assessments,students,id);
	std::cout<<"\n--------------------------------\n";
	std::cout<<std::left
		<<std::setw(15)<<"Student ID"
		<<std::setw(25)<<"Student Name"
		<<std::setw(10)<<"Marks"
		<<"\n";
	std::cout<<"--------------------------------\n";
	std::cout<<std::left
		<<std::setw(15)<<students.getID()
		<<std::setw(25)<<students.getName();
	assessments.display();
	}
};
