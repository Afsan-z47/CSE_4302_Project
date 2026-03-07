#include "AttendanceRecord.h"
#include <iostream>
#include <sstream>

AttendanceRecord::AttendanceRecord(std::string sID, std::string cCode, std::string d, bool status)
: studentID(sID), courseCode(cCode), date(d), isPresent(status) 
{}

void AttendanceRecord::displayAttendance() const {
	std::cout << "Date: " << date <<std::endl;
	std ::cout<< "Course: " << courseCode <<std::endl;
	std::cout<<"Student ID: " << studentID <<std::endl;
	std ::cout<<"Status: " << (isPresent ? "Present" : "Absent") << std::endl;
}

// NOTE: ---- Serialise ----

std::string AttendanceRecord::serialise() const {
	std::ostringstream ss;
	ss << studentID  << '|'
		<< courseCode << '|'
		<< date       << '|'
		<< (isPresent ? 1 : 0);
	return ss.str();
}
