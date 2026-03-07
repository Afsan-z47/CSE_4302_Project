#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <string>
#include "user.h" // karon student er id  ekane lagbe .

class AttendanceRecord {
private:
	std::string studentID; // User class e id ase
	std::string courseCode;
	std::string date;
	bool isPresent;

public:
	AttendanceRecord(std::string sID, std::string cCode, std::string d, bool status);


	void displayAttendance() const;
//	NOTE: ----- Getters ------
	//id check  korar jonno(jate report card e subidha hoy)

	std::string getStudentID()  const { return studentID; }
	std::string getCourseCode() const { return courseCode; }
	std::string getDate()       const { return date; }
	bool        getStatus()     const { return isPresent; }

//	NOTE: ----- Serialise -----

	// Format: studentID|courseCode|date|isPresent(0/1)
	std::string serialise() const;
};

#endif
