#ifndef GRADE_CPP
#define GRADE_CPP

//TODO: [ ] - Move it to a .h file

#include<iostream>
#include "assessment.cpp"
// #include "student.cpp"
class Grade{
	// Student s1;
	 Assessment a1;
	char grade;
public:
	// Grade(Student s2,Assessment a2):s1(s2),a1(a2){}
	char calculate_grade(){
	double percent = a1.get_percentage();

//	BUG: It can return multiple characters??

	if(percent >= 80) return 'A+';
	else if(percent >= 75) return 'A';
	else if(percent >= 70) return 'A-';
	else if(percent >=65) return 'B+';
	else if(percent >=60) return 'B';
	else if(percent >= 55) return 'B-';
	else if(percent >= 50) return 'C+';
	else if(percent >= 45) return 'C';
	else if(percent >= 40) return 'D';
	else return 'F';
	}
};

#endif // GRADE_CPP
