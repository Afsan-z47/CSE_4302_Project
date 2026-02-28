/*
*
*NOTE:------------------------------------
* User
* 	- ID
* 	- user_name
* 	- email
* 	- salt (what is this??)
* 	- passwordHash?
*	-> makeSalt()
*	-> hashpass()
*	-> setPass()
*	-> login()
*	-> forgotpass()
*
* Student : User
* 	- name? (repeat?)
* 	- fathername
* 	- mothername
* 	- ID ? (repeat?)
*	- address
*	- phoneNumber
*	- email ? (repeat?)
*	= student count
*	-> SETTER FUNCTIONS
*
* Teacher
* 	- 
* Admin : User
* 	- adminID
* 	- name
* 	-> generateSID (what's a SID?)
* 	-> generatePass (why is this under admin?)
* 	-> addStudent (add where?)
*
* Course
* 	- courseCode
* 	- courseName
* 	- Teacher (should be vector <student> ?)
* 	- vector<Student>
* 	- studentnumber (admitted course student count)
* 	-> add_students() (assign student to course)
*
*
* Grade
*	- Assessment
*	- char grade (should use enmus?)
*	-> calculate_grade()
*
* Assessment
* 	- id
* 	- maxMarks[6]
* 	- weightage[6]
* 	- marks_obtained[6]
* 	-> SETTER FUNCTIONS
* 	-> GETTER FUNCTIONS
*	-> get_percentage()
*
* Attendance Record
* Report Card
* -----------------------------------------
*/



/*
*TODO:
* > SchoolSystem
* 	- Inherits all of the stuff at the end
* 	
* 	> User space controls
* 		- Login
* 		- Select type
* 		- Provide typewise access
* 	
* 	- Course info handling
* 	
* 	> Save info?
* 		- Virtual functions?
* 		- Templates?
* 	> Load info?
* 		- Virtual functions?
* 		- Templates?
* 	- Admission teacher/student?
*	
*	WARNING:
* 	[ ] Race-condition not handled yet!
* 	[ ] Deriving multiple schoolSystem!
*/

#include "user.h"
#include "course.cpp"
#include <cstdint>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include "file_ops.h"


enum Privilege_type : uint8_t {
	GUEST,
	STUDENT,
	TEACHER,
	ADMIN,
};

class Display {
private:

public:
	void head() {
		std::cout << "--------------------------------------------\n"
			<< "|         School Management System         |\n"
			<< "--------------------------------------------\n"
			<< "                   Login                     \n"
			<< "                                             \n"
			<< "Provide username:          \n";
	}

	void head_pass() {
		std::cout << "Provide Password:          \n";

	}

	void main_menu(Privilege_type privilege) {
		switch (privilege) {
			case Privilege_type::ADMIN :
				std::cout << "----------->     Main Menu (Admin)   <-------------\n"
					<< "1. Admission \n"
					<< "2. Course Info \n"
					<< "3. Attendance \n"
					<< "4. Report Card\n";
				break;


			case Privilege_type::TEACHER :
				std::cout << "----------->     Main Menu (Teacher)   <-------------\n"
					<< "1. Course Info \n"
					<< "2. Attendance \n"
					<< "3. Report Card\n";
				break;

			case Privilege_type::STUDENT :
				std::cout << "----------->     Main Menu (Student)   <-------------\n"
					<< "1. Course Info \n"
					<< "2. Attendance \n"
					<< "3. Report Card\n";
				break;

			default:
				std::cout << "----------->     Main Menu (Guest)   <-------------\n"
					<< "1. Course Info \n"
					<< "2. Attendance \n"
					<< "3. Report Card\n";
		}
	}



};

class SchoolSystem : private Display { 
private:
	Privilege_type privilege;

	std::fstream file_user;
	std::fstream file_student;
	std::fstream file_admin;
	std::fstream file_teacher;
	std::fstream file_course;
	std::fstream file_report_card;
	std::fstream file_attendance_record;

	std::vector<Student> student_list;
	std::vector<Admin> admin_list;
//	std::vector<Teacher> course_list;
	std::vector<Course> course_list;
//	std::vector<report_card> user_list;
//	std::vector<attendance_record> user_list;


public:

	SchoolSystem(
		const std::string &path_to_user,
		const std::string &path_to_student,
		const std::string &path_to_admin,
		const std::string &path_to_teacher,
		const std::string &path_to_course,
		const std::string &path_to_report_card,
		const std::string &path_to_attendance_record
	)
	: privilege(GUEST)
	{
		file_user.open(path_to_user, std::ios::in | std::ios::out | std::ios::app);
		if(!file_user) {
			throw std::runtime_error("Cannot open user file");
		}
		file_student.open(path_to_student, std::ios::in | std::ios::out | std::ios::app);
		if(!file_student) {
			throw std::runtime_error("Cannot open student file");
		}

		file_teacher.open(path_to_teacher, std::ios::in | std::ios::out | std::ios::app);
		if(!file_teacher) {
			throw std::runtime_error("Cannot open teacher file");
		}

		file_admin.open(path_to_admin, std::ios::in | std::ios::out | std::ios::app);
		if(!file_admin) {
			throw std::runtime_error("Cannot open admin file");
		}

		file_course.open(path_to_course, std::ios::in | std::ios::out | std::ios::app);
		if(!file_course) {
			throw std::runtime_error("Cannot open course file");
		}


		file_report_card.open(path_to_report_card, std::ios::in | std::ios::out | std::ios::app);
		if(!file_report_card) {
			throw std::runtime_error("Cannot open report_card file");
		}

		file_attendance_record.open(path_to_attendance_record, std::ios::in | std::ios::out | std::ios::app);
		if(!file_attendance_record) {
			throw std::runtime_error("Cannot open attendance_record file");
		}





	}

	~SchoolSystem() = default;
	

	void run() {
		Display output;
		output.head();

		std::string email;
		std::string password;

		std::cin >> email;

		output.head_pass();

		std::cin >> password;

//		User user(;

//		user.login(email, password);
		

	}



};
