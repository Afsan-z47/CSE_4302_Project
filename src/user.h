#ifndef USER_H
#define USER_H

#include <cstdlib>
#include <iostream>

//--------------------------------  USER ----------------------------------------

class User {
	std::string ID;
	std::string username;
	std::string email;
	std::string salt;
	size_t passwordHash;

	static std::string makeSalt() ;
	static size_t hashPass(const std::string& salt, const std::string& pass) ;

public:

	User(std::string id, std::string uname, std::string pass, std::string mail);

	void setPassword(const std::string& pass);
	bool login(std::string uname, std::string pass) const ;
	void forgotPass() ;
};


//--------------------------------  STUDENT ----------------------------------------

class Student : public User {

	std::string name;
	std::string fatherName;
	std::string motherName;
	std::string ID;
	std::string address;
	std::string phoneNumber;
	std::string email;


public:
	Student(std::string n, std::string fn, std::string mn, std::string addr, std::string pn, std::string mail, std::string password, std::string ID);

	~Student();

	std::string getName() const ;
	std::string getFatherName() const ;
	std::string getMotherName() const ;
	std::string getID() const ;
	std::string getAddress() const ;
	std::string getPhoneNumber() const ;
	void setName(const std::string& n) ;
	void setFatherName(const std::string& fn) ;
	void setMotherName(const std::string& mn) ;
	void setID(const std::string& id) ;
	void setAddress(const std::string& addr) ;
	void setPhoneNumber(const std::string& pn) ;
};


extern int students;

//--------------------------------  ADMIN ----------------------------------------

class Admin : public User{

	std::string adminID;
	std::string name;

public:

	std::string generatePass(std::string phn);
	std::string generateSID() ;
	void addStudent(std::string nm, std::string fn, std::string mn, std::string addr, std::string phone, std::string mail);

};


#endif
