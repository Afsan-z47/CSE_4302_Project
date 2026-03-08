#include "user.h"

int students = 0;
int teachers = 0;

// ─── User ────────────────────────────────────────────────────────────────────

std::string User::makeSalt() { return std::to_string(rand()) + std::to_string(rand()); }

std::size_t User::hashPass(const std::string &salt, const std::string &pass) {
	return std::hash<std::string>{}(salt + pass);
}

User::User()
    : ID(""),
      username(""),
      email(""),
      salt(""),
      passwordHash(0) {}

User::User(
    const std::string &id,
    const std::string &uname,
    const std::string &pass,
    const std::string &mail
)
    : ID(id),
      username(uname),
      email(mail) {
	salt         = makeSalt();
	passwordHash = hashPass(salt, pass);
}

void User::setPassword(const std::string &pass) { passwordHash = hashPass(salt, pass); }

bool User::login(const std::string &uname, const std::string &pass) const {
	try {
		if ((uname == username) && (passwordHash == hashPass(salt, pass))) {
			std::clog << "Login is successful" << std::endl;
			return true;
		} else {
			throw failure();
		}
	} catch (const failure &f) {
		std::cerr << "Username or password is incorrect" << std::endl;
	}
	return false;
}

void User::forgotPass() {
	std::string mail;
	std::cout << "Enter your email: ";
	std::cin >> mail;
	if (mail == email) {
		std::string newPass = "Tmp@" + std::to_string(rand() % 10000);
		setPassword(newPass);
		std::cout << "Password reset. Temporary password: " << newPass << std::endl;
	} else {
		std::cout << "Email not found." << std::endl;
	}
}

std::string User::getID() const { return ID; }
std::string User::getUsername() const { return username; }
std::string User::getEmail() const { return email; }

// ─── Student ─────────────────────────────────────────────────────────────────

Student::Student()
    : User() {}

Student::Student(
    const std::string &n,
    const std::string &fn,
    const std::string &mn,
    const std::string &addr,
    const std::string &pn,
    const std::string &mail,
    const std::string &password,
    const std::string &id
)
    : User(id, n, password, mail),
      name(n),
      fatherName(fn),
      motherName(mn),
      address(addr),
      phoneNumber(pn) {
	std::cout << "Welcome to our school, " << n << "!" << std::endl;
}

Student::~Student() {
	std::cout << "Thank you for studying in our school. Hope you shine bright in your future."
	          << std::endl;
}

std::string Student::getName() const { return name; }
std::string Student::getFatherName() const { return fatherName; }
std::string Student::getMotherName() const { return motherName; }
std::string Student::getAddress() const { return address; }
std::string Student::getPhoneNumber() const { return phoneNumber; }

void Student::setName(const std::string &n) { name = n; }
void Student::setFatherName(const std::string &fn) { fatherName = fn; }
void Student::setMotherName(const std::string &mn) { motherName = mn; }
void Student::setAddress(const std::string &addr) { address = addr; }
void Student::setPhoneNumber(const std::string &pn) { phoneNumber = pn; }

void Student::getType() const { std::cout << "User is of a student-type" << std::endl; }

// ─── Teacher ─────────────────────────────────────────────────────────────────

Teacher::Teacher()
    : User(),
      age(0),
      salary(0) {}

Teacher::Teacher(
    const std::string &id,
    const std::string &n,
    int                a,
    const std::string &p,
    const std::string &ps,
    int                s,
    const std::string &mail,
    const std::string &c
)
    : User(id, n, ps, mail),
      name(n),
      age(a),
      phone_number(p),
      course(c),
      salary(s) {}

void Teacher::displayInfo() const {
	std::cout << "Teacher ID: " << ID << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Course: " << course << std::endl;
	std::cout << "Phone: " << phone_number << std::endl;
	std::cout << "Salary: " << salary << std::endl;
}

void Teacher::setCourse(const std::string &c) { course = c; }
void Teacher::updateSalary(int newSalary) { salary = newSalary; }

void Teacher::contact() const {
	std::cout << "Calling " << name << " at " << phone_number << std::endl;
}

void Teacher::getType() const { std::cout << "User is of teacher-type" << std::endl; }

// ─── Admin ───────────────────────────────────────────────────────────────────

Admin::Admin(
    const std::string &id,
    const std::string &uname,
    const std::string &pass,
    const std::string &mail
)
    : User(id, uname, pass, mail),
      adminID(id),
      name(uname) {}

std::string Admin::generatePass(const std::string &phn) {
	std::string demo = phn;
	for (int i = 0; i < (int)demo.length() / 2; i++) {
		char temp                   = demo[i];
		demo[i]                     = demo[demo.length() - i - 1];
		demo[demo.length() - i - 1] = temp;
	}
	int               r = rand() % 1000;
	std::stringstream ss;
	ss << std::setw(3) << std::setfill('0') << r;
	return demo + ss.str();
}

std::string Admin::generateSID() {
	students++;
	std::stringstream ss;
	ss << "123000" << std::setw(4) << std::setfill('0') << students;
	return ss.str();
}

std::string Admin::generateTID() {
	teachers++;
	std::stringstream ss;
	ss << "2600" << std::setw(6) << std::setfill('0') << teachers;
	return ss.str();
}

void Admin::addStudent(
    const std::string &nm,
    const std::string &fn,
    const std::string &mn,
    const std::string &addr,
    const std::string &phone,
    const std::string &mail
) {
	std::string id   = generateSID();
	std::string pass = generatePass(phone);
	Student     s(nm, fn, mn, addr, phone, mail, pass, id);
}

std::string Admin::addTeacher(
    const std::string &nm,
    int                a,
    const std::string &pn,
    const std::string &c,
    int                sal,
    const std::string &mail
) {
	std::string id   = generateTID();
	std::string pass = generatePass(pn);
	Teacher     t(id, nm, a, pn, pass, sal, mail, c);
	return id;
}

void Admin::getType() const { std::cout << "User is of admin-type" << std::endl; }
