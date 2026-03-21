#include "assessment.h" 
#include "grade.h"
#include "AttendanceRecord.h"
#include "file_ops.h"
#include "user.h"
#include "course.cpp"  
#include <cstdint>

enum Privilege_type : uint8_t {
	GUEST= 0,
	STUDENT = 1,
	TEACHER = 2,
	ADMIN= 3,
};

