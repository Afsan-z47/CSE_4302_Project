#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include "file_ops.h"
#include "user.h" // karon student er id  ekane lagbe .
#include <string>

class AttendanceRecord : public File_ops<AttendanceRecord> {
private:
	std::string studentID; // User class e id ase
	std::string courseCode;
	std::string date;
	bool        isPresent;

public:
	AttendanceRecord() = default;
	AttendanceRecord(std::string sID, std::string cCode, std::string d, bool status);

	AttendanceRecord(const AttendanceRecord &other);

	AttendanceRecord(AttendanceRecord &&other) noexcept;

	void displayAttendance() const;
	// NOTE: ----- Getters ------
	// id check  korar jonno(jate report card e subidha hoy)

	std::string getStudentID() const { return studentID; }
	std::string getCourseCode() const { return courseCode; }
	std::string getDate() const { return date; }
	bool        getStatus() const { return isPresent; }

	// NOTE: ----- Serialise/Deserialise -----

	// Format: studentID|courseCode|date|isPresent(0/1)
	std::string      serialize() const;
	AttendanceRecord desirialize(std::string &line) const;

	// NOTE: ----- File_ops ------
	void             save(std::ostream &f_out) const override;
	AttendanceRecord load(std::istream &f_in) override;
};

#endif
