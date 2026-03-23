// TODO: [ ] - Move it to a .h file
//  	[ ] - Make the code cleaner and easier to read

#include "assessment.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
Assessment::Assessment() {
	for (int i = 0; i < 6; i++) {
		if (i < 4) {
			maxMarks[i]  = 15;
			weightage[i] = 5;
		} else {
			maxMarks[i]  = 120;
			weightage[i] = 40;
		}
		marks_obtained[i] = 0;
	}
}
void Assessment::set_id(const std::string &ID) { studentID_ = ID; }
void Assessment::set_courceCode(const std::string &code) { courseCode_ = code; }

void Assessment::set_quiz1(const double marks) {
	if (marks > 15) {
		std::cout << "Quiz marks cannot be more than 15 marks\n";
		return;
	}
	marks_obtained[0] = marks;
}

void Assessment::set_quiz2(const double marks) {
	if (marks > 15) {
		std::cout << "Quiz marks cannot be more than 15 marks\n";
		return;
	}
	marks_obtained[1] = marks;
}
void Assessment::set_quiz3(const double marks) {
	if (marks > 15) {
		std::cout << "Quiz marks cannot be more than 15 marks\n";
		return;
	}
	marks_obtained[2] = marks;
}

void Assessment::set_quiz4(const double marks) {
	if (marks > 15) {
		std::cout << "Quiz marks cannot be more than 15 marks\n";
		return;
	}
	marks_obtained[3] = marks;
}

void Assessment::set_midterm(const double marks) {
	if (marks > 120) {
		std::cout << "Midterm marks cannot be greater than 120\n";
		return;
	}
	marks_obtained[4] = marks;
}

void Assessment::set_final(const double marks) {
	if (marks > 120) {
		std::cout << "Final marks cannot be greater than 120\n";
		return;
	}
	marks_obtained[5] = marks;
}

double Assessment::get_quiz1() const { return marks_obtained[0]; }

double Assessment::get_quiz2() const { return marks_obtained[1]; }

double Assessment::get_quiz3() const { return marks_obtained[2]; }

double Assessment::get_quiz4() const { return marks_obtained[3]; }

double Assessment::get_midterm() const { return marks_obtained[4]; }

double Assessment::get_final() const { return marks_obtained[5]; }

void Assessment::set_all_marks_together(double m[6]) {
	if (m[0] > 15 || m[1] > 15 || m[2] > 15 || m[3] > 15 || m[4] > 120 || m[5] > 120) {
		std::cout << "Marks is out of bounds please check again"
		          << "\nFor reference all quizzes marks are 15 and midterm and final validate till "
		             "120 marks\n";
		return;
	}
	set_quiz1(m[0]);
	set_quiz2(m[1]);
	set_quiz3(m[2]);
	set_quiz4(m[3]);
	set_midterm(m[4]);
	set_final(m[5]);
}

double Assessment::get_percentage() const {
	double sum = 0;
	for (int i = 0; i < 6; i++) {
		sum += marks_obtained[i] * weightage[i] / maxMarks[i];
	}
	return sum;
}

std::string Assessment::getStudentID() const { return studentID_; }
std::string Assessment::getCourseCode() const { return courseCode_; }

void Assessment::display() const {

	std::cout << "\n";
	std::cout << std::setfill('-') << std::setw(40) << "" << '\n';
	std::cout << std::setfill(' ');

	std::cout << std::left << std::setw(20) << "Assessment" << std::setw(15) << "Obtained Marks"
	          << '\n';

	std::cout << std::setfill('-') << std::setw(40) << "" << '\n';
	std::cout << std::setfill(' ');

	// Quiz marks
	for (int i = 0; i < 4; i++) {
		std::cout << std::left << std::setw(20) << ("Quiz " + std::to_string(i + 1))
		          << std::setw(15) << marks_obtained[i] << '\n';
	}

	// Midterm
	std::cout << std::left << std::setw(20) << "Midterm" << std::setw(15) << marks_obtained[4]
	          << '\n';

	// Final
	std::cout << std::left << std::setw(20) << "Final" << std::setw(15) << marks_obtained[5]
	          << '\n';

	std::cout << std::setfill('-') << std::setw(40) << "" << '\n';
	std::cout << std::setfill(' ');
}

// Format: studentID|q1|q2|q3|q4|mid|fin
std::string Assessment::serialize() const {
	std::ostringstream ss;
	ss << studentID_ << '|' << get_quiz1() << '|' << get_quiz2() << '|' << get_quiz3() << '|'
	   << get_quiz4() << '|' << get_midterm() << '|' << get_final();
	return ss.str();
}

Assessment Assessment::deserialize(std::string &line) {
	std::stringstream ss(line);
	std::string       id, q1, q2, q3, q4, mid, fin;
	std::getline(ss, id, '|');
	std::getline(ss, q1, '|');
	std::getline(ss, q2, '|');
	std::getline(ss, q3, '|');
	std::getline(ss, q4, '|');
	std::getline(ss, mid, '|');
	std::getline(ss, fin);
	double m[6] = {
	    std::stod(q1),
	    std::stod(q2),
	    std::stod(q3),
	    std::stod(q4),
	    std::stod(mid),
	    std::stod(fin)
	};
	Assessment ret;
	ret.set_id(id);
	ret.set_all_marks_together(m);
	return ret;
}

void Assessment::save(std::ostream &f_out) const { f_out << serialize(); }

Assessment Assessment::load(std::istream &f_in) {
	std::string line;
	std::getline(f_in, line);
	return deserialize(line);
}
