#ifndef __COURSE__
#define __COURSE__

// TODO: [ ] - Build a .h file

#include "file_ops.h"
#include "grade.cpp"
#include "user.h"
#include <iomanip>
#include <iostream>
#include <vector>
class Course : public File_ops<Course> {
	// FIX: Explicitly wrote private here. Better visibility
private:
	std::string courseCode;
	std::string courseName;
	std::string instructorName;

	std::vector<Student>    students_;
	std::vector<Assessment> assessment_;

	// FIX: Moved to studentCount  function as studnet number counter
	//  std::string studentnumber;

	// BUG: Redundent Grade g1
	//  std::vector<Grade>g1;

public:
	Course() = default;

	/*	BUG: Does not initialize instructor name like the setCourseInfo method.
	    BUG: why initialize sid here?
	    Course(std::string code,std::string sid){
	    courseCode = code;
	    studentnumber = sid;
	    }

	*/
	//	FIX:
	Course(std::string code, std::string name, std::string instructor) {
		setCourseInfo(code, name, instructor);
	}

	// NOTE: Explicit definations of copy and move operators
	Course(const Course &other)
	    : courseCode(other.courseCode),
	      courseName(other.courseName),
	      instructorName(other.instructorName),
	      students_(other.students_),
	      assessment_(other.assessment_) {}

	Course(Course &&other) noexcept
	    : courseCode(std::move(other.courseCode)),
	      courseName(std::move(other.courseName)),
	      instructorName(std::move(other.instructorName)),
	      students_(std::move(other.students_)),
	      assessment_(std::move(other.assessment_)) {}

	//	NOTE: ------- Setters/Adders -----------

	//	WARNING: Bad naming of id. Naming the same thing as id and courseCode
	void
	setCourseInfo(const std::string &id, const std::string &name, const std::string &instructor) {
		courseCode     = id;
		courseName     = name;
		instructorName = instructor;
	}

	void add_students(const Student &s2) { students_.push_back(s2); }

	void add_assessment(const Assessment &a2) { assessment_.push_back(a2); }

	//	FIX: There were no Getters
	//------- Getters -----------

	std::string getCourseCode() const { return courseCode; }
	std::string getCourseName() const { return courseName; }
	std::string getInstructorName() const { return instructorName; }
	std::size_t studentCount() const { return students_.size(); }

	//	NOTE: ------------- Display Methods --------------

	void displayCourseInfo() const {
		std::cout << "Course Id: " << courseCode << "| Course Name: " << courseName
		          << "| Instructor Name: " << instructorName
		          << " | number of students: " << students_.size() << "\n";
	}

	void search_student(Assessment &assessment, Student &student, std::string id) const {
		for (int i = 0; i < students_.size(); i++) {
			if (id == student.getID()) {
				assessment = assessment_[i];
				student    = students_[i];
				return;
			}
		}
	}

	void displayStudentInfo() const {
		std::cout << "Enter the student ID to search for: ";
		std::string id;
		std::cin >> id;
		Assessment assessments;
		Student    students;
		search_student(assessments, students, id);
		std::cout << "\n--------------------------------\n";
		std::cout << std::left << std::setw(15) << "Student ID" << std::setw(25) << "Student Name"
		          << std::setw(10) << "Marks"
		          << "\n";
		std::cout << "--------------------------------\n";
		std::cout << std::left << std::setw(15) << students.getID() << std::setw(25)
		          << students.getName();
		assessments.display();
	}

	//	NOTE: ----- Serialization / Deserialization -----

	// Format: courseCode|courseName|instructorName
	std::string serialize() const {
		std::stringstream ss;
		ss << courseCode << '|' << courseName << '|' << instructorName;

		return ss.str();
	}

	Course deserialize(std::string &line) const {
		std::stringstream ss(line);
		Course            ret;

		std::getline(ss, ret.courseCode, '|');
		std::getline(ss, ret.courseName, '|');
		std::getline(ss, ret.instructorName);

		return ret;
	}

	// NOTE: ----- File_ops ------
	void save(std::ostream &f_out) const override { f_out << serialize(); }

	Course load(std::istream &f_in) override {
		std::string line;
		std::getline(f_in, line);
		return deserialize(line);
	}
};

#endif
