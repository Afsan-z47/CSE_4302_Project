#include "user.h"

#include<ctime>
#include <functional>
#include <iomanip>
#include<sstream>

//--------------------------------  USER ----------------------------------------


size_t User::hashPass(const std::string& salt, const std::string& pass) {
	return std::hash<std::string>{}(salt + pass);
}


std::string User::makeSalt() {
	return std::to_string(rand()) + std::to_string(rand());
}

void User::setPassword(const std::string& pass) {
	passwordHash = hashPass(salt, pass);
}

bool User::login(std::string uname, std::string pass) const {
	return (uname == username) && (passwordHash == hashPass(salt, pass));
}



User::User(std::string id, std::string uname, std::string pass, std::string mail)
	: ID(std::move(id)), 
	username(std::move(uname)), 
	email(std::move(mail)), 
	salt(makeSalt()),
	passwordHash(hashPass(salt, pass))
{

}

void User::forgotPass() {
	std::string mail;
	std::cin >> mail;
	if (mail == email) {
		std::string newPass = "Tmp@" + std::to_string(rand() % 10000);
		setPassword(newPass);
		std::cout << "Password reset. Temporary password: " << newPass << std::endl;
	} else {
		std::cout << "Email not found.\n";
	}
}


//--------------------------------  STUDENT ----------------------------------------

Student::Student(std::string n, std::string fn, std::string mn, std::string addr, std::string pn, std::string mail, std::string password, std::string ID) 
	: name(n), 
	fatherName(fn), 
	motherName(mn), 
	address(addr), 
	phoneNumber(pn), 
	email(mail), 
	User (ID, n, password, mail)
{
	std::cout << "Welcome to our school" << std::endl;
};

Student::~Student(){
	std::cout << "Thank you for studying in our school. Hope you shine bright in your future." << std::endl;
};


std::string Student::getName() const { return name; }
std::string Student::getFatherName() const { return fatherName; }
std::string Student::getMotherName() const { return motherName; }
std::string Student::getID() const { return ID; }
std::string Student::getAddress() const { return address; }
std::string Student::getPhoneNumber() const { return phoneNumber; }

void Student::setName(const std::string& n) { name = n; }
void Student::setFatherName(const std::string& fn) { fatherName = fn; }
void Student::setMotherName(const std::string& mn) { motherName = mn; }
void Student::setID(const std::string& id) { ID = id; }
void Student::setAddress(const std::string& addr) { address = addr; }
void Student::setPhoneNumber(const std::string& pn) { phoneNumber = pn; }


int students = 0; 

//--------------------------------  ADMIN ----------------------------------------

std::string Admin::generatePass(std::string phn){
	std::string demo = phn;
	for(int i = 0; i < demo.length() / 2; i++){
		char temp = demo[i];
		demo[i] = demo[demo.length() - i - 1];
		demo[demo.length() - i - 1] = temp;
	}

	int r = rand() % 1000;
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

void Admin::addStudent(std::string nm, std::string fn, std::string mn, std::string addr, std::string phone, std::string mail) {
	std::string id = generateSID();
	std::string pass = generatePass(phone);
	Student s(nm, fn, mn, addr, phone, mail, pass, id);
}
