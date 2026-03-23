#ifndef __ASSESSMENT__
#define __ASSESSMENT__

#include <file_ops.h>
#include <string>

class Assessment {
	std::string id;
	double      maxMarks[6];
	double      weightage[6]; // BUG: Redundent?
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
	double get_midterm() const;
	double get_final() const;

	void   set_all_marks_together(double m[6]);
	double get_percentage() const;
	void   display() const;

	// Format: studentID|q1|q2|q3|q4|mid|fin
	std::string serialize() const;

	Assessment deserialize(std::string &line);

	void       save(std::ostream &f_out) const;
	Assessment load(std::istream &f_in);
};

#endif
