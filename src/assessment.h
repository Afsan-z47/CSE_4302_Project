#ifndef __ASSESSMENT__
#define __ASSESSMENT__

#include <string>
class Assessment {
	std::string id;
	double      maxMarks[6];
	double      weightage[6];
	double      marks_obtained[6];
	// first 4 are quiz marks(out of 15) and the next 2 are midterm and final marks respectfully
public:
	Assessment();
	void   set_id(std::string ID);
	void   set_quiz1(double marks);
	void   set_quiz2(double marks);
	void   set_quiz3(double marks);
	void   set_quiz4(double marks);
	void   set_midterm(double marks);
	void   set_final(double marks);
	double get_quiz1() const;
	double get_quiz2() const;
	double get_quiz3() const;
	double get_quiz4() const;
	double get_midterm(double marks);
	double get_final();

	void   set_all_marks_together(double m[6]);
	double get_percentage() const;
	void   display() const;
};

#endif
