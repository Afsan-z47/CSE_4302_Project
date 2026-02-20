#include "user.cpp"
#include "sami.cpp"
int main(){
    srand((unsigned)time(nullptr));
	User new_user("001", "Azizul", "123", "haki@iut-dhaka.edu");
	cout << "Running main";


	Sami obj1;
	obj1.display();
}
