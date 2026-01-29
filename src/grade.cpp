#include<iostream>
class Grade{
	// Student s1;
	// Assessment a1;
	double marks_obtained;
public:
	Grade(){}
	// Grade(Student s2,Assessment a2,double marks):s1(s2),a1(a2),marks_obtained(marks){}
	void set_marks(double d1){
	marks_obtained = d1;
		std::cout<<"Set the marks to:"<<d1<<std::endl;
	}
	// double get_percentage(){
	// }
	// double getWeightedMarks(){}
};
