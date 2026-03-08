#ifndef USER_H
#define USER_H

#include <cstdlib>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

extern int students;
extern int teachers;

class failure {
	// empty class to handle login error
};

class User {
protected:
	std::string ID;
	std::string username;
	std::string email;
	std::string salt;
	std::size_t passwordHash;

private:
	static std::string makeSalt();
	static std::size_t hashPass(const std::string &salt, const std::string &pass);

public:
	User();
	User(
	    const std::string &id,
	    const std::string &uname,
	    const std::string &pass,
	    const std::string &mail
	);

	void setPassword(const std::string &pass);
	bool login(const std::string &uname, const std::string &pass) const;
	void forgotPass();

	std::string getID() const;
	std::string getUsername() const;
	std::string getEmail() const;

	virtual void getType() const = 0;
	virtual ~User() {}
};

class Student : public User {
	std::string name;
	std::string fatherName;
	std::string motherName;
	std::string address;
	std::string phoneNumber;

public:
	Student();
	Student(
	    const std::string &n,
	    const std::string &fn,
	    const std::string &mn,
	    const std::string &addr,
	    const std::string &pn,
	    const std::string &mail,
	    const std::string &password,
	    const std::string &id
	);
	~Student();

	std::string getName() const;
	std::string getFatherName() const;
	std::string getMotherName() const;
	std::string getAddress() const;
	std::string getPhoneNumber() const;

	void setName(const std::string &n);
	void setFatherName(const std::string &fn);
	void setMotherName(const std::string &mn);
	void setAddress(const std::string &addr);
	void setPhoneNumber(const std::string &pn);

	void getType() const override;
};

class Teacher : public User {
	std::string name;
	int         age;
	std::string phone_number;
	std::string course;
	int         salary;

public:
	Teacher();
	Teacher(
	    const std::string &id,
	    const std::string &n,
	    int                a,
	    const std::string &p,
	    const std::string &ps,
	    int                s,
	    const std::string &mail,
	    const std::string &c
	);

	void displayInfo() const;
	void setCourse(const std::string &c);
	void updateSalary(int newSalary);
	void contact() const;

	void getType() const override;
};

class Admin : public User {
	std::string adminID;
	std::string name;

public:
	Admin(
	    const std::string &id,
	    const std::string &uname,
	    const std::string &pass,
	    const std::string &mail
	);

	std::string generatePass(const std::string &phn);
	std::string generateSID();
	std::string generateTID();

	void addStudent(
	    const std::string &nm,
	    const std::string &fn,
	    const std::string &mn,
	    const std::string &addr,
	    const std::string &phone,
	    const std::string &mail
	);
	std::string addTeacher(
	    const std::string &nm,
	    int                a,
	    const std::string &pn,
	    const std::string &c,
	    int                sal  = 20000,
	    const std::string &mail = ""
	);

	void getType() const override;
};

#endif // USER_H
