#include "assessment.h"
#include "AttendanceRecord.h"
#include "course.cpp"
#include "file_ops.h"
#include "grade.h"
#include "user.h"
#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

// Data model
// ──────────
//
//  ┌─────────────────────────┐       ┌──────────────────────────────┐
//  │ Student                 │       │ Course                       │
//  │ ID, name, contact info  │       │ code, name, instructor name  │
//  └────────────┬────────────┘       └──────────────┬───────────────┘
//               │  1                            N   │
//               └──────────────┬────────────────────┘
//                              │
//                    ┌─────────▼──────────┐
//                    │ Enrollment         │  ← explicit join table
//                    │ studentID          │    one student, many courses
//                    │ courseCode         │    one course, many students
//                    └────────┬───────────┘
//                             │
//             ┌───────────────┴────────────────┐
//             │                                │
//   ┌─────────▼──────────┐        ┌────────────▼───────────┐
//   │ AttendanceRecord   │        │ AssessmentRecord       │
//   │ studentID          │        │ studentID              │
//   │ courseCode         │        │ courseCode             │
//   │ date               │        │ q1 q2 q3 q4 mid final  │
//   │ isPresent          │        └────────────┬───────────┘
//   └────────────────────┘                     │
//                                              │ + Student obj
//                                              ▼
//                                    ┌───────────────────┐
//                                    │ Grade             │  ← not stored
//                                    │ computed on demand│    Grade(Student,
//                                    └───────────────────┘    Assessment)
//

enum Privilege_type : uint8_t {
	GUEST   = 0,
	STUDENT = 1,
	TEACHER = 2,
	ADMIN   = 3,
};

template <typename T>
concept DATA_VECTOR =
    std::same_as<T, Student> || std::same_as<T, Teacher> || std::same_as<T, Admin> ||
    std::same_as<T, Course> || std::same_as<T, AttendanceRecord> || std::same_as<T, Assessment>;

class SchoolSystem {
private:
	// Following a constant naming style as per
	// cpp core guidelines ending with _ .
	// NOTE: Session
	Privilege_type privilege_ = GUEST;
	std::string    sessionID_;

	// NOTE: DATA Vectors
	// TODO: [ ] Change this to shared memory?
	std::vector<Student> students_;
	std::vector<Teacher> teachers_;
	std::vector<Admin>   admins_;
	std::vector<Course>  courses_;

	std::vector<std::pair<std::string, std::string>> enrollments_;

	std::vector<AttendanceRecord> attendance_;
	std::vector<Assessment>       assessments_;

	// NOTE: File paths
	static constexpr const char *F_STUDENTS = "students.txt";
	static constexpr const char *F_TEACHERS = "teachers.txt";
	static constexpr const char *F_ADMINS   = "admins.txt";
	static constexpr const char *F_COURSES  = "courses.txt";

	static constexpr const char *F_ENROLLMENTS = "enrollments.txt";

	static constexpr const char *F_ATTEND      = "attendance.txt";
	static constexpr const char *F_ASSESSMENTS = "assessments.txt";

	// NOTE: Necessary constants
	static constexpr int LINE_WIDTH = 64;

	// NOTE: FILE LOADS/SAVES
	template <typename T> void load_records(const char *path, std::vector<T> &data_vector) {
		T             obj_type;
		std::ifstream file_path(path);
		if (!file_path)
			return;
		data_vector.clear(); // needed for clean, new loads
		std::string line;

		while (std::getline(file_path, line)) {
			if (line.empty())
				continue;
			std::istringstream ss(line);
			data_vector.push_back(obj_type.load(ss));
		}
	}

	template <typename T> void save_records(const char *path, const std::vector<T> &vec) {
		std::ofstream file_path(path);
		for (const auto &item : vec) {
			item.save(file_path);
			file_path << '\n';
		}
	}

	bool login(const std::string &uname, const std::string &pass) {
		// TODO: Use std::ranges::any_of() following cpp core guidelines

		for (auto &student : students_) {
			if (student.login(uname, pass)) {
				privilege_ = STUDENT;
				sessionID_ = student.getID();
				return true;
			}
		}
		for (auto &teacher : teachers_) {
			if (teacher.login(uname, pass)) {
				privilege_ = TEACHER;
				sessionID_ = teacher.getID();
				return true;
			}
		}

		for (auto &admin : admins_) {
			if (admin.login(uname, pass)) {
				privilege_ = ADMIN;
				sessionID_ = admin.getID();
				return true;
			}
		}

		return false;
	}

	void logout() {
		privilege_ = GUEST;
		sessionID_.clear();
	}

	// NOTE: TUI Helpers

	int read_choice(const int low, const int high) {

		int choice = 0;
		while (true) {
			std::cin >> choice;
			if (choice >= low || choice <= high)
				break;
			std::cout << " Must be between " << low << " and " << high << " . Try again\n";
		}
		return choice;
	}

	void print_line(char type = '-', int width = 64) {
		std::cout << std::string(width, type) << '\n';
	}

	void print_title(const std::string &title) {

		print_line('=');
		int pad = std::max(0, (LINE_WIDTH - (int)title.size()) / 2);
		std::cout << std::string(pad, ' ') << title << '\n';
		print_line('=');
		std::cout << '\n';
	}

	static std::string read_line(const std::string &prompt) {
		std::string s;
		std::cout << "  " << prompt;
		std::getline(std::cin, s);
		return s;
	}

	static double read_double(const std::string &prompt) {
		double v = 0.0;
		std::cout << "  " << prompt;
		std::cin >> v;
		// using getline after this causes problem
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return v;
	}

	// NOTE: Helper Functions

	static std::string current_date() {

		std::time_t current_time = std::time(nullptr);
		char        buffer[11];

		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&current_time));

		std::string ret(buffer);
		return ret;
	}

	// FIX: THIS find impletation is too complex and bugprone
	// The Concept is declared as DATA_VECTOR
	template <DATA_VECTOR T> std::vector<T> &get_vec() {

		if constexpr (std::same_as<T, Student>) {
			return students_;
		} else if constexpr (std::same_as<T, Teacher>) {
			return teachers_;
		} else if constexpr (std::same_as<T, Admin>) {
			return admins_;
		} else if constexpr (std::same_as<T, Course>) {
			return courses_;
		} else if constexpr (std::same_as<T, AttendanceRecord>) {
			return attendance_;
		} else {
			return assessments_;
		}
	}

	template <DATA_VECTOR T> static consteval auto get_projection() {

		if constexpr (std::same_as<T, Course>) {
			return &Course::getCourseCode;

		} else if constexpr (std::same_as<T, AttendanceRecord>) {

			// NOTE: [ capture ] ( parameters ) -> return_type { body }
			return [](const T &item) {
				return std::make_tuple(item.getStudentID(), item.getCourseCode());
			};

		} else if constexpr (std::same_as<T, Assessment>) {

			return [](const T &item) {
				return std::make_tuple(item.getStudentID(), item.getCourseCode());
			};

		} else {
			return &T::getID;
		}
	}

	template <DATA_VECTOR T>
	    requires(!std::same_as<T, AttendanceRecord> && !std::same_as<T, Assessment>)
	T *find_data(const std::string &key) {
		auto &vec = get_vec<T>();

		auto item = std::ranges::find(vec, key, get_projection<T>());

		return (item != vec.end()) ? &(*item) : nullptr;
	}

	template <DATA_VECTOR T>
	    requires(std::same_as<T, Assessment> || std::same_as<T, AttendanceRecord>)
	T *find_data(const std::string &id, const std::string &code) {
		auto &vec = get_vec<T>();

		auto item = std::ranges::find(vec, std::make_tuple(id, code), get_projection<T>());

		return (item != vec.end()) ? &(*item) : nullptr;
	}

	// FIX: THIS find impletation is too complex and messy

	// NOTE: GUEST Menu

	bool guest_menu() {
		print_title("SCHOOL MANAGEMENT SYSTEM");
		std::cout << "  [1]  Login\n";
		std::cout << "  [0]  Exit\n\n";
		if (read_choice(0, 1) == 0)
			return false;

		print_title("Login");
		std::string uname = read_line("Username : ");
		std::string pass  = read_line("Password : ");
		;
		if (login(uname, pass))
			std::cout << "\n  Login successful.\n";
		else
			std::cout << "\n  Invalid username or password.\n";

		return true;
	}

	// NOTE: Student Menu

	void view_my_courses(const Student &current_user) {
		print_title("My Courses");
		std::cout << std::left << std::setw(12) << "Code" << std::setw(28) << "Name"
		          << "Instructor\n";
		print_line();

		bool any_enrollments = false;
		for (const auto &[code, sid] : enrollments_) {

			if (sid != current_user.getID()) {
				continue;
			}
			any_enrollments = true;

			auto *obj = find_data<Course>(code);
			if (obj == nullptr) {
				continue;
			}

			Course &user_course = *obj;

			std::cout << std::left << std::setw(12) << user_course.getCourseCode() << std::setw(28)
			          << user_course.getCourseName() << user_course.getInstructorName() << '\n';
		}

		if (!any_enrollments) {
			std::cout << "  No courses enrolled.\n";
		}
	}

	void view_my_attendance(const Student &current_user) {

		print_title("My Attendance");
		std::cout << std::left << std::setw(14) << "Date" << std::setw(12) << "Course"
		          << "Status\n";
		print_line();

		int present = 0;
		int total   = 0;

		for (const auto &item : attendance_) {

			if (item.getStudentID() != current_user.getID()) {
				continue;
			}

			std::cout << std::left << std::setw(14) << item.getDate() << std::setw(12)
			          << item.getCourseCode() << (item.getStatus() ? "Present" : "Absent") << '\n';
			total++;
			if (item.getStatus()) {
				present++;
			}
		}

		if (total == 0) {

			std::cout << "  No records.\n";

		} else {

			print_line();
			std::cout << "  Overall: " << present << '/' << total << "  (" << std::fixed
			          << std::setprecision(1) << 100.0 * present / total << "%)\n";
		}
	}

	void view_my_grades(const Student &current_user) {

		print_title("My Grades");
		std::cout << std::left << std::setw(12) << "Course" << std::setw(8) << "Q1" << std::setw(8)
		          << "Q2" << std::setw(8) << "Q3" << std::setw(8) << "Q4" << std::setw(10) << "Mid"
		          << std::setw(10) << "Final" << std::setw(8) << "%" << "Grade\n";
		print_line();

		bool any_enrollments = false;
		for (const auto &[code, sid] : enrollments_) {
			if (sid != current_user.getID()) {
				continue;
			}
			any_enrollments = true;

			auto *obj = find_data<Assessment>(current_user.getID(), code);
			if (obj == nullptr) {
				std::cout << std::left << std::setw(12) << code << "(no marks entered yet)\n";
			};

			Assessment &user_assessment = *obj;
			Grade       user_grade(current_user, user_assessment);
			std::cout << std::left << std::setw(12) << code << std::setw(8)
			          << user_assessment.get_quiz1() << std::setw(8) << user_assessment.get_quiz2()
			          << std::setw(8) << user_assessment.get_quiz3() << std::setw(8)
			          << user_assessment.get_quiz4() << std::setw(10)
			          << user_assessment.get_midterm() << std::setw(10)
			          << user_assessment.get_final() << std::setw(8) << std::fixed
			          << std::setprecision(1) << user_assessment.get_percentage()
			          << user_grade.get_grade() << '\n';
		}

		if (!any_enrollments) {
			std::cout << "  No courses enrolled.\n";
		}
	}

	void view_my_profile(const Student &current_user) {
		print_title("My Profile");
		std::cout << "  ID      : " << current_user.getID() << '\n';
		std::cout << "  name    : " << current_user.getName() << '\n';
		std::cout << "  Father  : " << current_user.getFatherName() << '\n';
		std::cout << "  Mother  : " << current_user.getMotherName() << '\n';
		std::cout << "  Address : " << current_user.getAddress() << '\n';
		std::cout << "  Phone   : " << current_user.getPhoneNumber() << '\n';
		std::cout << "  Email   : " << current_user.getEmail() << '\n';
	}

	void student_menu() {
		auto *obj = find_data<Student>(sessionID_);
		if (obj == nullptr) {
			logout();
			return;
		}

		Student &current_user = *obj;

		print_title("Student Panel");
		std::cout << "  Welcome, " << current_user.getName() << "  |  ID: " << current_user.getID()
		          << "\n\n";
		std::cout << "  [1]  My courses\n";
		std::cout << "  [2]  My attendance\n";
		std::cout << "  [3]  My grades\n";
		std::cout << "  [4]  My profile\n";
		std::cout << "  [0]  Logout\n\n";

		switch (read_choice(0, 4)) {
		case 0:
			logout();
			break;
		case 1:
			view_my_courses(current_user);
			break;
		case 2:
			view_my_attendance(current_user);
			break;
		case 3:
			view_my_grades(current_user);
			break;
		case 4:
			view_my_profile(current_user);
			break;
		}
	}

	// NOTE: Teacher Menu

	std::vector<Course> courses_by_teacher(const Teacher &current_user) {
		std::vector<Course> out;

		for (auto &item : courses_) {
			if (item.getInstructorName() == current_user.getUsername()) {
				out.push_back(item);
			}
		}

		return out;
	}

	void view_teacher_courses(const Teacher &current_user) {
		print_title("My Courses");

		auto teaches_courses = courses_by_teacher(current_user);

		if (teaches_courses.empty()) {
			std::cout << "  No courses assigned.\n";
		} else {
			for (auto &item : teaches_courses) {
				item.displayCourseInfo();
			}
		}
	}

	void view_enrolled_students(const Teacher &current_user) {
		print_title("Enrolled Students");

		auto teaches_courses = courses_by_teacher(current_user);
		if (teaches_courses.empty()) {
			std::cout << "  No courses assigned.\n";
			return;
		}

		for (auto &item : teaches_courses) {
			std::cout << "\n  " << item.getCourseCode() << "  –  " << item.getCourseName() << '\n';
			print_line('-');

			bool any_enrollment = false;
			for (const auto &[code, id] : enrollments_) {
				if (code != item.getCourseCode()) {
					continue;
				}
				any_enrollment = true;

				auto *student = find_data<Student>(id);

				if (student == nullptr) {
					std::cout << "  " << std::setw(14) << id << "(unknown)" << '\n';
				} else {
					std::cout << "  " << std::setw(14) << id << student->getName() << '\n';
				}
			}

			if (!any_enrollment) {
				std::cout << "  (no students enrolled)\n";
			}
		}
	}

	void mark_attendance(const Teacher &current_user) {
		print_title("Mark Attendance");
		auto teaches_courses = courses_by_teacher(current_user);
		if (teaches_courses.empty()) {
			std::cout << "  No courses assigned.\n";
			return;
		}

		for (std::size_t i = 0; i < teaches_courses.size(); i++) {
			std::cout << "  [" << i + 1 << "]  " << teaches_courses[i].getCourseCode() << " – "
			          << teaches_courses[i].getCourseName() << '\n';
		}
		std::cout << "  [0]  Back\n\n";
		int choice = read_choice(0, (int)teaches_courses.size());
		if (choice == 0) {
			return;
		}
		Course &course = teaches_courses[choice - 1];

		std::string date = current_date();
		std::cout << "\n  Course: " << course.getCourseCode() << "  |  Date: " << date << "\n\n";

		bool any_marked = false;
		for (const auto &[code, id] : enrollments_) {
			if (code != course.getCourseCode()) {
				continue;
			}
			any_marked = true;

			bool done = false;
			for (const auto &item : attendance_) {
				if (item.getStudentID() == id && item.getCourseCode() == code &&
				    item.getDate() == date) {
					done = true;
					break;
				}
			}
			if (done) {
				std::cout << "  " << id << "  already marked today\n";
				continue;
			}

			auto *student = find_data<Student>(id);

			std::cout << "  " << std::setw(14) << id << std::setw(22)
			          << ((student != nullptr) ? student->getName() : "?")
			          << "Present? [1=Yes / 0=No]: ";

			int choice = -1;
			while (choice != 0 && choice != 1) {
				std::cin >> choice;
			}

			attendance_.emplace_back(id, code, date, (choice == 1));
		}

		if (any_marked) {
			std::cout << "\n  Attendance saved.\n";
		} else {
			std::cout << "\n  Nothing to mark.\n";
		}
	}

	void enter_marks(const Teacher &current_user) {
		print_title("Enter Marks");
		auto teaches_courses = courses_by_teacher(current_user);
		if (teaches_courses.empty()) {
			std::cout << "  No courses assigned.\n";
			return;
		}

		for (std::size_t i = 0; i < teaches_courses.size(); i++) {
			std::cout << "  [" << i + 1 << "]  " << teaches_courses[i].getCourseCode() << " – "
			          << teaches_courses[i].getCourseName() << '\n';
		}
		std::cout << "  [0]  Back\n\n";

		int choice = read_choice(0, (int)teaches_courses.size());
		if (choice == 0) {
			return;
		}

		Course &course = teaches_courses[choice - 1];

		bool any_entered = false;
		for (const auto &[code, sid] : enrollments_) {

			if (code != course.getCourseCode()) {
				continue;
			}
			any_entered = true;

			auto *student = find_data<Student>(sid);
			if (student == nullptr) {
				continue;
			}

			std::cout << "\n  Student: " << sid << "  " << student->getName() << '\n';
			std::cout << "  (enter -1 for Quiz 1 to skip)\n";

			double q1 = read_double("  Quiz 1  (0-15)  : ");
			if (q1 < 0) {
				continue;
			}
			double q2  = read_double("  Quiz 2  (0-15)  : ");
			double q3  = read_double("  Quiz 3  (0-15)  : ");
			double q4  = read_double("  Quiz 4  (0-15)  : ");
			double mid = read_double("  Midterm (0-120) : ");
			double fin = read_double("  Final   (0-120) : ");

			auto      *obj = find_data<Assessment>(sid, code);
			Assessment assessment;
			if (obj == nullptr) {
				Assessment temp;
				temp.set_id(sid);
				temp.set_courceCode(code);
				assessments_.push_back(temp);
				assessment = assessments_.back();
			}

			double m[6] = {q1, q2, q3, q4, mid, fin};
			assessment.set_all_marks_together(m);

			Grade grade(*student, assessment);
			std::cout << "  → " << grade.get_grade() << "  (" << std::fixed << std::setprecision(1)
			          << assessment.get_percentage() << "%)\n";
		}

		if (any_entered) {
			std::cout << "\n  Marks saved.\n";
		}
	}

	void teacher_menu() {
		auto *obj = find_data<Teacher>(sessionID_);
		if (obj == nullptr) {
			logout();
			return;
		}

		Teacher &current_user = *obj;

		print_title("Teacher Panel");
		std::cout << "  Welcome, " << current_user.getUsername()
		          << "  |  ID: " << current_user.getID() << "\n\n";
		std::cout << "  [1]  My courses\n";
		std::cout << "  [2]  Enrolled students\n";
		std::cout << "  [3]  Mark attendance\n";
		std::cout << "  [4]  Enter marks\n";
		std::cout << "  [5]  My info\n";
		std::cout << "  [0]  Logout\n\n";

		switch (read_choice(0, 5)) {
		case 0:
			logout();
			break;
		case 1:
			view_teacher_courses(current_user);
			break;
		case 2:
			view_enrolled_students(current_user);
			break;
		case 3:
			mark_attendance(current_user);
			break;
		case 4:
			enter_marks(current_user);
			break;
		case 5:
			print_title("My Info");
			current_user.displayInfo();
			break;
		}
	}
	
	//NOTE: Admin menu

	void admin_menu() {
		print_title("Admin Panel");
		std::cout << "  [1]  Add student\n";
		std::cout << "  [2]  Add teacher\n";
		std::cout << "  [3]  Add course\n";
		std::cout << "  [4]  Enroll student in course\n";
		std::cout << "  [5]  List students\n";
		std::cout << "  [6]  List teachers\n";
		std::cout << "  [7]  List courses\n";
		std::cout << "  [8]  Course attendance report\n";
		std::cout << "  [0]  Logout\n\n";

		switch (read_choice(0, 8)) {
		case 0:
			logout();
			break;
		/*	case 1: add_student();       break;
		            case 2: add_teacher();       break;
		            case 3: add_course();        break;
		            case 4: enroll_student();    break;
		            case 5: list_students();     break;
		            case 6: list_teachers();     break;
		            case 7: list_courses();      break;
		            case 8: view_course_attendence(); break;
		*/}
	}

public:
	;
};
