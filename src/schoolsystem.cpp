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
