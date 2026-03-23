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
      email(mail),
      salt(makeSalt()),
      passwordHash(hashPass(salt, pass)) {}

void User::setPassword(const std::string &pass) { passwordHash = hashPass(salt, pass); }

bool User::login(const std::string &uname, const std::string &pass) const {
	try {
		if ((uname == username) && (passwordHash == hashPass(salt, pass))) {
			std::cout << "Login is successful" << std::endl;
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

std::string Student::getName() const { return username; }
std::string Student::getFatherName() const { return fatherName; }
std::string Student::getMotherName() const { return motherName; }
std::string Student::getAddress() const { return address; }
std::string Student::getPhoneNumber() const { return phoneNumber; }

void Student::setName(const std::string &n) { username = n; }
void Student::setFatherName(const std::string &fn) { fatherName = fn; }
void Student::setMotherName(const std::string &mn) { motherName = mn; }
void Student::setAddress(const std::string &addr) { address = addr; }
void Student::setPhoneNumber(const std::string &pn) { phoneNumber = pn; }

void Student::getType() const { std::cout << "User is of a student-type" << std::endl; }

// ─── Student File_ops ─────────────────────────────────────────────────────────

Student::Student(const Student &other)
    : User(other),
      fatherName(other.fatherName),
      motherName(other.motherName),
      address(other.address),
      phoneNumber(other.phoneNumber) {}

Student::Student(Student &&other) noexcept
    : User(other),
      fatherName(std::move(other.fatherName)),
      motherName(std::move(other.motherName)),
      address(std::move(other.address)),
      phoneNumber(std::move(other.phoneNumber)) {}

Student &Student::operator=(const Student &other) {
	if (this != &other) {
		User::operator=(other);
		fatherName  = other.fatherName;
		motherName  = other.motherName;
		address     = other.address;
		phoneNumber = other.phoneNumber;
	}
	return *this;
}

// Format: ID|username|email|salt|passwordHash|fatherName|motherName|address|phoneNumber
std::string Student::serialize() const {
	std::ostringstream oss;
	oss << ID << '|' << username << '|' << email << '|' << salt << '|' << passwordHash << '|'
	    << fatherName << '|' << motherName << '|' << address << '|' << phoneNumber;

	return oss.str();
}

Student Student::deserialize(std::string &line) const {
	std::stringstream ss(line);
	Student           ret;
	std::string       hashStr;

	std::getline(ss, ret.ID, '|');
	std::getline(ss, ret.username, '|');
	std::getline(ss, ret.email, '|');
	std::getline(ss, ret.salt, '|');
	std::getline(ss, hashStr, '|');
	std::getline(ss, ret.fatherName, '|');
	std::getline(ss, ret.motherName, '|');
	std::getline(ss, ret.address, '|');
	std::getline(ss, ret.phoneNumber, '|');

	ret.passwordHash = std::stoull(hashStr);
	return ret;
}

void Student::save(std::ostream &f_out) const { f_out << serialize(); }

Student Student::load(std::istream &f_in) {
	std::string line;
	std::getline(f_in, line);
	return deserialize(line);
}

// ─── Admin ───────────────────────────────────────────────────────────────────

Admin::Admin() = default;
Admin::Admin(
    const std::string &id,
    const std::string &uname,
    const std::string &pass,
    const std::string &mail
)
    : User(id, uname, pass, mail),
      adminID(id) {}

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

void Admin::getType() const { std::cout << "User is of admin-type" << '\n'; }

// ─── Admin File_ops ───────────────────────────────────────────────────────────

Admin::Admin(const Admin &other)
    : User(other),
      adminID(other.adminID) {}

Admin::Admin(Admin &&other) noexcept
    : User(other),
      adminID(std::move(other.adminID)) {}

Admin &Admin::operator=(const Admin &other) {
	if (this != &other) {
		User::operator=(other);
		adminID = other.adminID;
	}
	return *this;
}

// Format: ID|username|email|salt|passwordHash|adminID
std::string Admin::serialize() const {
	std::ostringstream oss;
	oss << ID << '|' << username << '|' << email << '|' << salt << '|' << passwordHash << '|'
	    << adminID;

	return oss.str();
}

Admin Admin::deserialize(std::string &line) const {
	std::stringstream ss(line);
	Admin             ret("", "", "", "");
	std::string       hashStr;

	std::getline(ss, ret.ID, '|');
	std::getline(ss, ret.username, '|');
	std::getline(ss, ret.email, '|');
	std::getline(ss, ret.salt, '|');
	std::getline(ss, hashStr, '|');
	std::getline(ss, ret.adminID, '|');

	ret.passwordHash = std::stoull(hashStr);
	return ret;
}

void Admin::save(std::ostream &f_out) const { f_out << serialize(); }

Admin Admin::load(std::istream &f_in) {
	std::string line;
	std::getline(f_in, line);
	return deserialize(line);
}

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
      age(a),
      phone_number(p),
      course(c),
      salary(s) {}

void Teacher::displayInfo() const {
	// clang-format off
	std::cout << "Teacher ID: " << ID           << std::endl;
	std::cout << "Name: "       << username     << std::endl;
	std::cout << "Age: "        << age          << std::endl;
	std::cout << "Course: "     << course       << std::endl;
	std::cout << "Phone: "      << phone_number << std::endl;
	std::cout << "Salary: "     << salary       << std::endl;
	// clang-format on
}

void Teacher::setCourse(const std::string &c) { course = c; }
void Teacher::updateSalary(int newSalary) { salary = newSalary; }

void Teacher::contact() const {
	std::cout << "Calling " << username << " at " << phone_number << std::endl;
}

void Teacher::getType() const { std::cout << "User is of teacher-type" << std::endl; }

// ─── Teacher File_ops ─────────────────────────────────────────────────────────

Teacher::Teacher(const Teacher &other)
    : User(other),
      age(other.age),
      phone_number(other.phone_number),
      course(other.course),
      salary(other.salary) {}

Teacher::Teacher(Teacher &&other) noexcept
    : User(other),
      age(other.age),
      phone_number(std::move(other.phone_number)),
      course(std::move(other.course)),
      salary(other.salary) {}

Teacher &Teacher::operator=(const Teacher &other) {
	if (this != &other) {
		User::operator=(other);
		age          = other.age;
		phone_number = other.phone_number;
		course       = other.course;
		salary       = other.salary;
	}
	return *this;
}

// Format: ID|username|email|salt|passwordHash|age|phone_number|course|salary
std::string Teacher::serialize() const {
	std::ostringstream oss;
	oss << ID << '|' << username << '|' << email << '|' << salt << '|' << passwordHash << '|' << age
	    << '|' << phone_number << '|' << course << '|' << salary;

	return oss.str();
}

Teacher Teacher::deserialize(std::string &line) const {
	std::stringstream ss(line);
	Teacher           ret;
	std::string       hashStr, ageStr, salStr;

	std::getline(ss, ret.ID, '|');
	std::getline(ss, ret.username, '|');
	std::getline(ss, ret.email, '|');
	std::getline(ss, ret.salt, '|');
	std::getline(ss, hashStr, '|');
	std::getline(ss, ageStr, '|');
	std::getline(ss, ret.phone_number, '|');
	std::getline(ss, ret.course, '|');
	std::getline(ss, salStr, '|');

	ret.passwordHash = std::stoull(hashStr);
	ret.age          = std::stoi(ageStr);
	ret.salary       = std::stoi(salStr);
	return ret;
}

void Teacher::save(std::ostream &f_out) const { f_out << serialize(); }

Teacher Teacher::load(std::istream &f_in) {
	std::string line;
	std::getline(f_in, line);
	return deserialize(line);
}
