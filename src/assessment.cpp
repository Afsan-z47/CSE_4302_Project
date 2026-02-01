#include<iostream>
class Assessment{
	std::string id;
	double maxMarks[6];
	double weightage[6];
	double marks_obtained[6];
public:
	Assessment(){
	for(int i=0;i<6;i++)
	{
		if(i<4){
		maxMarks[i] = 20;
		weightage[i] = 6.667;
		}
		else {maxMarks[i] = 120;
		weightage[i] = 40;
		}
	marks_obtained[i] = 0;
	}
	}
	void set_id(std::string ID){
	id = ID;
	}
	void set_quiz1(double marks){
	marks_obtained[0] = marks;
	}
	void set_quiz2(double marks){
	marks_obtained[1] = marks;
	}
	void set_quiz3(double marks){
	marks_obtained[2] = marks;
	}
	void set_quiz4(double marks){
	marks_obtained[3] = marks;
	}
	void set_midterm(double marks){
	marks_obtained[4] = marks;
	}
	void set_final(double marks){
	marks_obtained[5] = marks;
	}
	double get_quiz1()const{
	return marks_obtained[0];
	}
	double get_quiz2()const{
	return marks_obtained[1];
	}
	double get_quiz3()const{
	return marks_obtained[2];
	}
	double get_quiz4()const{
	return marks_obtained[3];
	}
	double get_midterm(double marks){
	return marks_obtained[4];
	}
	double get_final(){
	return marks_obtained[5];
	}

	void set_all_marks_together(double m[6]){
	set_quiz1(m[0]);
	set_quiz2(m[1]);
	set_quiz3(m[2]);
	set_quiz4(m[3]);
	set_midterm(m[4]);
	set_final(m[5]);
	}
	double get_percentage()const{
	double sum = 0;
	for(int i=0;i<6;i++){
	sum += marks_obtained[i] * weightage[i] / maxMarks[i];
	}
	return sum;
	}
};
