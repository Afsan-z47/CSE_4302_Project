#include<iostream>
#include<iomanip>
#include<sstream>
#include <cstdlib>
#include <ctime>
#include <functional>
using namespace std;

class User {
    string ID;
    string username;
    string email;
    string salt;
    size_t passwordHash;

    static string makeSalt() {
        return to_string(rand()) + to_string(rand());
    }

    static size_t hashPass(const string& salt, const string& pass) {
        return hash<string>{}(salt + pass);
    }

public:

    User(string id, string uname, string pass, string mail)
        : ID(id), username(uname), email(mail) {
        salt = makeSalt();
        passwordHash = hashPass(salt, pass);
    }

    void setPassword(const string& pass) {
        passwordHash = hashPass(salt, pass);
    }

    bool login(string uname, string pass) const {
        return (uname == username) && (passwordHash == hashPass(salt, pass));
    }

    void forgotPass() {
        string mail;
        cin >> mail;
        if (mail == email) {
            string newPass = "Tmp@" + to_string(rand() % 10000);
            setPassword(newPass);
            cout << "Password reset. Temporary password: " << newPass << endl;
        } else {
            cout << "Email not found.\n";
        }
    }
};



class Student : public User{

    string name;
    string fatherName;
    string motherName;
    string ID;
    string address;
    string phoneNumber;
    string email;


public:
    Student(string n, string fn, string mn, string addr, string pn, string mail, string password, string ID) : name(n), fatherName(fn), motherName(mn), address(addr), phoneNumber(pn), email(mail), User (ID, n, password, mail){
        cout << "Welcome to our school" << endl;
    };

    ~Student(){
        cout << "Thank you for studying in our school. Hope you shine bright in your future." << endl;
    };
    string getName() const {
        return name;
    }

    string getFatherName() const {
        return fatherName;
    }

    string getMotherName() const {
        return motherName;
    }

    string getID() const {
        return ID;
    }

    string getAddress() const {
        return address;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    void setName(const string& n) {
        name = n;
    }

    void setFatherName(const string& fn) {
        fatherName = fn;
    }

    void setMotherName(const string& mn) {
        motherName = mn;
    }

    void setID(const string& id) {
        ID = id;
    }

    void setAddress(const string& addr) {
        address = addr;
    }

    void setPhoneNumber(const string& pn) {
        phoneNumber = pn;
    }
};

static int students = 0; 


class admin : public User{

    string adminID;
    string name;

public:

    string generatePass(string phn){
        string demo = phn;
        for(int i = 0; i < demo.length() / 2; i++){
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
        ss << "123000" 
           << setw(4) << setfill('0') << students;
    
        return ss.str();
    }
    
    void addStudent(string nm, string fn, string mn, string addr, string phone, string mail){
        string id = generateSID();
        string pass = generatePass(phone);
        Student s(nm, fn, mn, addr, phone, mail, pass, id);
    }

};



