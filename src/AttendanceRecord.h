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
    
    //id check  korar jonno(jate report card e subidha hoy)
    std::string getStudentID() const { return studentID; }
    bool getStatus() const { return isPresent; }
};

#endif