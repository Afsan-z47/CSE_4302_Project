#ifndef ASSESSMENT_CPP
#define ASSESSMENT_CPP

// TODO: [ ] - Move it to a .h file
//  	[ ] - Make the code cleaner and easier to read

#include "assessment.h"
#include <iomanip>
#include <iostream>
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
void Assessment::set_id(std::string ID) { id = ID; }

void Assessment::set_quiz1(double marks) {
	if (marks > 15) {
		std::cout << "Quiz marks cannot be more than 15 marks for this design\n";
		return;
	}
	marks_obtained[0] = marks;
}

void Assessment::set_quiz2(double marks) {
	if (marks > 15) {
		std::cout << "Quiz marks cannot be more than 15 marks for this design\n";
		return;
	}
	marks_obtained[1] = marks;
}
void Assessment::set_quiz3(double marks) {
	if (marks > 15) {
		std::cout << "Quiz marks cannot be more than 15 marks for this design\n";
		return;
	}
	marks_obtained[2] = marks;
}

void Assessment::set_quiz4(double marks) {
	if (marks > 15) {
		std::cout << "Quiz marks cannot be more than 15 marks for this design\n";
		return;
	}
	marks_obtained[3] = marks;
}

void Assessment::set_midterm(double marks) {
	if (marks > 120) {
		std::cout << "Midterm marks cannot be greater than 120\n";
		return;
	}
	marks_obtained[4] = marks;
}

void Assessment::set_final(double marks) {
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

double Assessment::get_midterm(double marks) { return marks_obtained[4]; }

double Assessment::get_final() { return marks_obtained[5]; }

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

#endif // ASSESSMENT_CPP
