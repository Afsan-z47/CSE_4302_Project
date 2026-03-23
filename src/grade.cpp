#include "grade.h"

#include "assessment.h"
#include "user.h"
#include <utility>

Grade::Grade(Student student, Assessment assessment)
    : a1(std::move(assessment)),
      s1(std::move(student)) {
	calculate_grade();
}

std::string Grade::calculate_grade() {
	double percent = a1.get_percentage();

	if (percent >= 80) {
		grade = "A+";
		return "A+";
	} else if (percent >= 75) {
		grade = "A";
		return "A";
	} else if (percent >= 70) {
		grade = "A-";
		return "A-";
	} else if (percent >= 65) {
		grade = "B+";
		return "B+";
	} else if (percent >= 60) {
		grade = "B";
		return "B";
	} else if (percent >= 55) {
		grade = "B-";
		return "B-";
	} else if (percent >= 50) {
		grade = "C+";
		return "C+";
	} else if (percent >= 45) {
		grade = "C";
		return "C";
	} else if (percent >= 40) {
		grade = "D";
		return "D";
	} else {
		grade = "F";
		return "F";
	}
}
std::string Grade::get_grade() const { return grade; }
