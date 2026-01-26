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

};

int main(){
}