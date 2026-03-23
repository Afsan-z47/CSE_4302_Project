#include "assessment.h"
#include "AttendanceRecord.h"
#include "course.cpp"
#include "file_ops.h"
#include "grade.h"
#include "user.h"
#include <cstdint>

enum Privilege_type : uint8_t {
	GUEST   = 0,
	STUDENT = 1,
	TEACHER = 2,
	ADMIN   = 3,
};

class SchoolSystem {
private:
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

public:
};
