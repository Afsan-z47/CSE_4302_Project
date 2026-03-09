#include "grade.cpp"
#include "user.h"

class Course{
private:
	std::string courseCode;
	std::string courseName;
	std::string instructorName;
	std::vector<Student> students_;
	std::vector<Assessment> assessment_;
public:
	Course();
	Course(std::string code,std::string name,std::string instructor);
	//Setters/Adders
	void setCourseInfo(const std::string &id,const std::string &name,const std::string &instructor);
	void add_students(const Student& s2);
	void add_assessment(const Assessment& a2);
	//Getters
	
	std::string getCourseCode()const;
	std::string getCourseName()const;
	std::string getInstructorName()const;
	std::size_t studentCount()const;

	//Display methods
	
	void displayCourseInfo() const;

	void search_student(Assessment &assessments, Student &students, std::string id) const;

	void displayStudentInfo() const;

	//	NOTE: ----- Serialization -----

	// Format: courseCode|courseName|instructorName
	std::string serialise() const;
};
