#include "user.cpp"
#include "aahil.cpp"
int main(){
    srand((unsigned)time(nullptr));
	User new_user("001", "Azizul", "123", "haki@iut-dhaka.edu");
	cout << "Running main.cpp\n";
	solution s1;
	if(s1.isvalid("Aahil"))
	cout<<"YES\n";
	else cout<<"NO\n";
}
