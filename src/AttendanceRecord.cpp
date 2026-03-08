#include "AttendanceRecord.h"
#include <iostream>
#include <sstream>
#include <utility>

AttendanceRecord::AttendanceRecord(std::string sID, std::string cCode, std::string d, bool status)
    : studentID(std::move(sID)), courseCode(std::move(cCode)), date(std::move(d)),
      isPresent(status) {}

void AttendanceRecord::displayAttendance() const {
    std::cout << "Date: " << date << std::endl;
    std ::cout << "Course: " << courseCode << std::endl;
    std::cout << "Student ID: " << studentID << std::endl;
    std ::cout << "Status: " << (isPresent ? "Present" : "Absent") << std::endl;
}

// NOTE: ----- Serialise/Deserialise -----
//  Format: studentID|courseCode|date|isPresent(0/1)

std::string AttendanceRecord::serialize() const {
    std::ostringstream ss;
    ss << studentID << '|' << courseCode << '|' << date << '|' << (isPresent ? 1 : 0);
    return ss.str();
}

AttendanceRecord desirialize(std::string &line) {
    std::stringstream ss(line);

    std::string studentID;
    std::string courseCode;
    std::string date;
    std::string presentStr;

    std::getline(ss, studentID, '|');
    std::getline(ss, courseCode, '|');
    std::getline(ss, date, '|');
    std::getline(ss, presentStr, '|');

    bool isPresent = (presentStr == "1");

    return AttendanceRecord(studentID, courseCode, date, isPresent);
}

// NOTE: ----- File_ops ------
void AttendanceRecord::save(std::ostream &f_out) const { f_out << serialize(); }

AttendanceRecord AttendanceRecord::load(std::istream &f_in) {
    std::string line;
    f_in >> line;
    return desirialize(line);
}
