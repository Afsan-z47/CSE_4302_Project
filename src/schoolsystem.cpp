#include "assessment.h"
#include "AttendanceRecord.h"
#include "course.cpp"
#include "file_ops.h"
#include "grade.h"
#include "user.h"
#include <cassert>
#include <cstdint>
#include <string>

enum Privilege_type : uint8_t {
	GUEST   = 0,
	STUDENT = 1,
	TEACHER = 2,
	ADMIN   = 3,
};

class SchoolSystem {
private:
	// Following a constant naming style as per
	// cpp core guidelines ending with _ .
	// NOTE: Session
	Privilege_type privilege_ = GUEST;
	std::string    sessionID_;

	// NOTE: DATA Vectors
	// TODO: [ ] Change this to shared memory?
	std::vector<Student>          students_;
	std::vector<Teacher>          teachers_;
	std::vector<Admin>            admins_;
	std::vector<Course>           courses_;
	std::vector<AttendanceRecord> attendance_;
	std::vector<Assessment>       assessments_;

	// NOTE: File paths
	static constexpr const char *F_STUDENTS    = "students.txt";
	static constexpr const char *F_TEACHERS    = "teachers.txt";
	static constexpr const char *F_ADMINS      = "admins.txt";
	static constexpr const char *F_COURSES     = "courses.txt";
	static constexpr const char *F_ATTEND      = "attendance.txt";
	static constexpr const char *F_ASSESSMENTS = "assessments.txt";

	//NOTE: Necessary constants
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
	
	//NOTE: TUI Helpers
	
	int read_choice(const int low, const int high) {
		int choice = 0;
		while(true) {
			std::cin >> choice;
			if(choice >= low || choice <= high) break;
			std::cout << " Must be between " << low << " and " << high << " . Try again\n";
		}
		return choice;
	}

	void print_line(char type = '-', int width = 64) { std::cout << std::string(width, type) << '\n'; }

	void print_title(const std::string& title) {
		print_line('=');
		int pad = std::max(0, (LINE_WIDTH - (int)title.size()) / 2);
		std::cout << std::string(pad, ' ') << title << '\n';
		print_line('=');
		std::cout << '\n';
	}

	//NOTE: Menu

	bool guestMenu() {
		print_title("SCHOOL MANAGEMENT SYSTEM");
		std::cout << "  [1]  Login\n";
		std::cout << "  [0]  Exit\n\n";
		if (read_choice(0, 1) == 0) return false;

		print_title("Login");
		std::string uname;
		std::cout << "Username : ";
		std::getline(std::cin, uname);


		std::string pass;
		std::cout << "Password : ";
		std::getline(std::cin, pass);

		if (login(uname, pass))
			std::cout << "\n  Login successful.\n";
		else
			std::cout << "\n  Invalid username or password.\n";

		return true;
	}



public:


};
