#include<iostream>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<vector>
#include<string>
using namespace std;

static int students = 0;
static int teachers = 0;

class failure {
    // empty class to handle login error
};


class User {
protected:
    string ID;
    string username;
    string email;
    string salt;
    size_t passwordHash;

private:
    static string makeSalt() {
        return to_string(rand()) + to_string(rand());
    }

    static size_t hashPass(const string& salt, const string& pass) {
        return hash<string>{}(salt + pass);
    }

public:
    User() : ID(""), username(""), email(""), salt(""), passwordHash(0) {}

    User(const string& id, const string& uname, const string& pass, const string& mail)
        : ID(id), username(uname), email(mail) {
        salt = makeSalt();
        passwordHash = hashPass(salt, pass);
    }

    void setPassword(const string& pass) {
        passwordHash = hashPass(salt, pass);
    }

    bool login(const string& uname, const string& pass) const {
        try {
            if ((uname == username) && (passwordHash == hashPass(salt, pass))) {
                clog << "Login is successful" << endl;
                return true;
            }
            else {
                throw failure();
            }
        }
        catch (const failure& f) {
            cerr << "Username or password is incorrect" << endl;
        }
        return false;
    }

    void forgotPass() {
        string mail;
        cout << "Enter your email: ";
        cin >> mail;
        if (mail == email) {
            string newPass = "Tmp@" + to_string(rand() % 10000);
            setPassword(newPass);
            cout << "Password reset. Temporary password: " << newPass << endl;
        }
        else {
            cout << "Email not found." << endl;
        }
    }

    string getID()       const { return ID; }
    string getUsername() const { return username; }
    string getEmail()    const { return email; }

    virtual void getType() const = 0;
    virtual ~User() {}
};


class Student : public User {
    string name;
    string fatherName;
    string motherName;
    string address;
    string phoneNumber;

public:
    // Default constructor (needed for vector/search use)
    Student() : User() {}

    Student(const string& n, const string& fn, const string& mn,
            const string& addr, const string& pn, const string& mail,
            const string& password, const string& id)
        : User(id, n, password, mail),
          name(n), fatherName(fn), motherName(mn),
          address(addr), phoneNumber(pn) {
        cout << "Welcome to our school, " << n << "!" << endl;
    }

    ~Student() {
        cout << "Thank you for studying in our school. Hope you shine bright in your future." << endl;
    }

    string getName()        const { return name; }
    string getFatherName()  const { return fatherName; }
    string getMotherName()  const { return motherName; }
    string getAddress()     const { return address; }
    string getPhoneNumber() const { return phoneNumber; }

    void setName(const string& n)        { name = n; }
    void setFatherName(const string& fn) { fatherName = fn; }
    void setMotherName(const string& mn) { motherName = mn; }
    void setAddress(const string& addr)  { address = addr; }
    void setPhoneNumber(const string& pn){ phoneNumber = pn; }

    void getType() const override {
        cout << "User is of a student-type" << endl;
    }
};

class Teacher : public User {
    string name;
    int age;
    string phone_number;
    string course;
    int salary;

public:
    Teacher() : User(), age(0), salary(0) {}

    Teacher(const string& id, const string& n, int a, const string& p,
            const string& ps, int s, const string& mail, const string& c)
        : User(id, n, ps, mail),
          name(n), age(a), phone_number(p), course(c), salary(s) {}

    void displayInfo() const {
        cout << "Teacher ID: " << ID        << endl;
        cout << "Name: "       << name      << endl;
        cout << "Age: "        << age       << endl;
        cout << "Course: "     << course    << endl;
        cout << "Phone: "      << phone_number << endl;
        cout << "Salary: "     << salary    << endl;
    }

    void setCourse(const string& c)  { course = c; }
    void updateSalary(int newSalary) { salary = newSalary; }

    void contact() const {
        cout << "Calling " << name << " at " << phone_number << endl;
    }

    void getType() const override {
        cout << "User is of teacher-type" << endl;
    }
};


class Admin : public User {
    string adminID;
    string name;

public:
    Admin(const string& id, const string& uname,
          const string& pass, const string& mail)
        : User(id, uname, pass, mail), adminID(id), name(uname) {}

    string generatePass(const string& phn) {
        string demo = phn;
        for (int i = 0; i < (int)demo.length() / 2; i++) {
            char temp = demo[i];
            demo[i] = demo[demo.length() - i - 1];
            demo[demo.length() - i - 1] = temp;
        }
        int r = rand() % 1000;
        stringstream ss;
        ss << setw(3) << setfill('0') << r;
        return demo + ss.str();
    }

   
    string generateSID() {
        students++;
        stringstream ss;
        ss << "123000" << setw(4) << setfill('0') << students;
        return ss.str();
    }

    
    string generateTID() {
        teachers++;
        stringstream ss;
        ss << "2600" << setw(6) << setfill('0') << teachers;
        return ss.str();
    }

    void addStudent(const string& nm, const string& fn, const string& mn,
                    const string& addr, const string& phone, const string& mail) {
        string id   = generateSID();
        string pass = generatePass(phone);
        Student s(nm, fn, mn, addr, phone, mail, pass, id);
    }

    string addTeacher(const string& nm, int a, const string& pn,
                      const string& c, int sal = 20000, const string& mail = "") {
        string id   = generateTID();
        string pass = generatePass(pn);
        Teacher t(id, nm, a, pn, pass, sal, mail, c);
        return id;
    }

    void getType() const override {
        cout << "User is of admin-type" << endl;
    }
};


class AttendanceRecord {
    string studentID;
    string courseCode;
    string date;
    bool   isPresent;

public:
    AttendanceRecord(const string& sID, const string& cCode,
                     const string& d, bool status)
        : studentID(sID), courseCode(cCode), date(d), isPresent(status) {}

    void displayAttendance() const {
        cout << "Date: "       << date       << endl;
        cout << "Course: "     << courseCode << endl;
        cout << "Student ID: " << studentID  << endl;
        cout << "Status: "     << (isPresent ? "Present" : "Absent") << endl;
    }

    string getStudentID() const { return studentID; }
    bool   getStatus()    const { return isPresent; }
};


class Assessment {
    string id;
    double maxMarks[6];
    double weightage[6];
    double marks_obtained[6];


public:
    Assessment() {
        for (int i = 0; i < 6; i++) {
            if (i < 4) { maxMarks[i] = 15;  weightage[i] = 5;  }
            else        { maxMarks[i] = 120; weightage[i] = 40; }
            marks_obtained[i] = 0;
        }
    }

    void set_id(const string& ID) { id = ID; }

   
    void set_quiz(int quizNumber, double marks) {
        if (quizNumber < 1 || quizNumber > 4) {
            cout << "Invalid quiz number. Must be 1-4." << endl;
            return;
        }
        if (marks > 15) {
            cout << "Quiz marks cannot exceed 15." << endl;
            return;
        }
        marks_obtained[quizNumber - 1] = marks;
    }

    void set_midterm(double marks) {
        if (marks > 120) { cout << "Midterm marks cannot exceed 120." << endl; return; }
        marks_obtained[4] = marks;
    }

    void set_final(double marks) {
        if (marks > 120) { cout << "Final marks cannot exceed 120." << endl; return; }
        marks_obtained[5] = marks;
    }

    double get_quiz(int quizNumber) const {
        if (quizNumber < 1 || quizNumber > 4) return -1;
        return marks_obtained[quizNumber - 1];
    }

   
    double get_midterm() const { return marks_obtained[4]; }
    double get_final()   const { return marks_obtained[5]; }

    void set_all_marks(double m[6]) {
        if (m[0]>15 || m[1]>15 || m[2]>15 || m[3]>15 || m[4]>120 || m[5]>120) {
            cout << "Marks out of bounds. Quizzes max 15, midterm/final max 120." << endl;
            return;
        }
        for (int i = 0; i < 4; i++) set_quiz(i + 1, m[i]);
        set_midterm(m[4]);
        set_final(m[5]);
    }

    double get_percentage() const {
        double sum = 0;
        for (int i = 0; i < 6; i++)
            sum += marks_obtained[i] * weightage[i] / maxMarks[i];
        return sum;
    }

    void display() const {
        cout << "\n";
        cout << setfill('-') << setw(40) << "" << "\n";
        cout << setfill(' ');
        cout << left << setw(20) << "Assessment" << setw(15) << "Obtained Marks" << "\n";
        cout << setfill('-') << setw(40) << "" << "\n";
        cout << setfill(' ');
        for (int i = 0; i < 4; i++)
            cout << left << setw(20) << ("Quiz " + to_string(i+1))
                         << setw(15) << marks_obtained[i] << "\n";
        cout << left << setw(20) << "Midterm" << setw(15) << marks_obtained[4] << "\n";
        cout << left << setw(20) << "Final"   << setw(15) << marks_obtained[5] << "\n";
        cout << setfill('-') << setw(40) << "" << "\n";
        cout << setfill(' ');
        cout << "Total Percentage: " << get_percentage() << "%" << "\n";
    }
};


class Grade {
    Assessment a1;
    string grade;

public:
    Grade() {}
    Grade(const Assessment& a) : a1(a) {}

   
    string calculate_grade() {
        double percent = a1.get_percentage();
        if      (percent >= 80) return "A+";
        else if (percent >= 75) return "A";
        else if (percent >= 70) return "A-";
        else if (percent >= 65) return "B+";
        else if (percent >= 60) return "B";
        else if (percent >= 55) return "B-";
        else if (percent >= 50) return "C+";
        else if (percent >= 45) return "C";
        else if (percent >= 40) return "D";
        else                    return "F";
    }

    void display() {
        grade = calculate_grade();
        a1.display();
        cout << "Grade: " << grade << "\n";
    }
};


class Course {
    string courseCode;
    string courseName;
    string instructorName;
    vector<Student>    s1;
    vector<Assessment> a1;
   

public:
    Course() {}

    Course(const string& code, const string& name, const string& instructor) {
        courseCode     = code;
        courseName     = name;
        instructorName = instructor;
    }

    void add_student(const Student& s)       { s1.push_back(s); }
    void add_assessment(const Assessment& a) { a1.push_back(a); }

    void setCourseInfo(const string& id, const string& name, const string& instructor) {
        courseCode     = id;
        courseName     = name;
        instructorName = instructor;
    }

    void displayCourseInfo() const {
        cout << "Course ID: "       << courseCode
             << " | Course Name: "  << courseName
             << " | Instructor: "   << instructorName
             << " | Students: "     << s1.size() << "\n";
    }

   
    bool search_student(Assessment& assessments, Student& student, const string& id) const {
        for (int i = 0; i < (int)s1.size(); i++) {
            if (id == s1[i].getID()) {
                assessments = a1[i];
                student     = s1[i];
                return true;
            }
        }
        return false;
    }

   
    void displayStudentInfo(const string& id) const {
        Assessment assessments;
        Student    student;  

        if (!search_student(assessments, student, id)) {
            cout << "Student with ID " << id << " not found." << endl;
            return;
        }

        cout << "\n" << setfill('-') << setw(40) << "" << "\n" << setfill(' ');
        cout << left << setw(15) << "Student ID"
                     << setw(25) << "Student Name" << "\n";
        cout << setfill('-') << setw(40) << "" << "\n" << setfill(' ');
        cout << left << setw(15) << student.getID()
                     << setw(25) << student.getName() << "\n";
        assessments.display();
        Grade g(assessments);
        cout << "Grade: " << g.calculate_grade() << "\n";
    }
};
int main(){

}