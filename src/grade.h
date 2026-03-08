#include"assessment.h"
#include"user.h"
#include<string>
class Grade{
	Assessment a1;
	std::string grade;
	Student s1;
public:
	Grade(Student s2,Assessment a2);
	std::string calculate_grade();
	std::string get_grade()const;
};
