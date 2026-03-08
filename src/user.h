#ifndef USER_H
#define USER_H

#include <cstdlib>
#include <iostream>
#include "file_ops.h"

//--------------------------------  USER ----------------------------------------

class User {
	std::string ID;
	std::string username;
	std::string email;
	std::string address;	 //WARNING: Moved from Student
	std::string phoneNumber; //WARNING: Moved from Student
	
//WARNING: What is salt? give proper names
	std::string salt;
	size_t passwordHash;

	static std::string makeSalt() ;
	static size_t hashPass(const std::string& salt, const std::string& pass) ;

public:
	User() = default;
	
	User( std::string n, std::string addr, 
		std::string pn, std::string mail, 
		std::string password, std::string ID
	);

	//WARNING: ------------- Moved from Student -------------------
	std::string getName() const ;		
	std::string getID() const ;		
	std::string getAddress() const ;	
	std::string getPhoneNumber() const ;	
	
	void setName(const std::string& n) ;
	void setID(const std::string& id) ;
	void setAddress(const std::string& addr) ;
	void setPhoneNumber(const std::string& pn) ;
	//WARNING: ----------------------------------------------------

	void setPassword(const std::string& pass);
	bool login(std::string uname, std::string pass) const ;
	void forgotPass() ;
};


//--------------------------------  STUDENT ----------------------------------------

class Student : public User, public File_ops<Student> {

//BUG: REDUNDENT_NAME_FIELD
//	std::string name;
	std::string fatherName;
	std::string motherName;
//BUG:: REDUNDENT_ID_FIELD
//	std::string ID;

//WARNING: address is something that all Users contain
//	std::string address;
//WARNING: Phone number is something that all Users contain
//	std::string phoneNumber;
//BUG:: REDUNDENT_EMAIL_FIELD
//	std::string email;


public:
	Student(std::string n, std::string fn, std::string mn, std::string addr, std::string pn, std::string mail, std::string password, std::string ID);
	Student() = default;
	~Student();

	std::string getFatherName() const ;
	std::string getMotherName() const ;
	void setFatherName(const std::string& fn) ;
	void setMotherName(const std::string& mn) ;

//NOTE: ----- Serialization/Deserialization -----
// Format: studentID|courseCode|date|isPresent(0/1)
	std::string serialize() const;
	Student desirialize(std::string &line) const;

//NOTE: ----- File Ops -----

	void save(std::ostream &f_out) const override;
	Student load(std::istream &f_in) override;


};

//WARNING: It represents student_count, yet its just named students
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
