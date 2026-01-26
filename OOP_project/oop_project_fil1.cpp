#include<iostream>
using namespace std;
class User{
    string ID;
    string username;
    string password;
    string email;

string getPassword() const{
    return password;
}
    
public:
    User(string id, string uname, string pass, string mail) : ID(id), username(uname), password(pass), email(mail) {
        cout << "Welcome " << uname  << endl;
    }

    void setPassword(string pass){
        password = pass;
    }

    ~User(){
        cout << "User is deleted, all records are now gone." << endl;
    }

    bool login(string uname, string pass) const{
        return (uname == username) && (password == pass);
    }


    void logout(){
        cout << "Logging out..." << endl;
    }

    void forgotPass(){
        string mail;
        cout << "Please enter your e-mail: " << endl;
        cin >> mail;
        if(mail == email){
            cout << "Your password is : " << getPassword() << endl;
        }
        else{
            cout << "User with email " << mail << " does not exist" << endl;
        }
        return;
    }

};


class Student{

    string name;
    string fatherName;
    string motherName;
    string ID;
    string address;
    string phoneNumber;

public:
    Student(string n, string fn, string mn, string id, string addr, string pn) : name(n), fatherName(fn), motherName(mn), ID(id), address(addr), phoneNumber(pn) {
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

int main(){

}