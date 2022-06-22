#include <iostream>

using namespace std;
// School Managment App

void parent();

void teacher();

void admin();

int login();

int main() {

	return 0;
}

int login()
{

	int login_option;
	// welcome user to app
	cout << "Welcome to the School Management App" << endl;
	cout << "Who are you: " << endl;

	cout << "1. Admin" << endl;
	cout << "2. Teacher" << endl;
	cout << "3. Parent" << endl;

	cin >> login_option;

	// switch for each option
	switch (login_option) {
	case 1:
		admin();
		break;
	case 2:
		teacher();
		break;
	case 3:
		parent();
		break;
	default:
		cout << "Invalid option" << endl;
		break;
	}
	
	int login_or_register;

	
	// do while loop to keep asking for login or register
	do {
		cout << "1. Login" << endl;
		cout << "2. Register" << endl;
		cin >> login_or_register;
		if (std::cin.fail() || login_or_register != 1 || login_or_register != 2)
		{
			std::cout << "\n\nPlease enter a number";
		}
		
	} while (login_or_register != 1 && login_or_register != 2);
	

	cout << "Would you like to login or register?" << endl;

	
	return login_or_register;
}

void parent()
{
	
}

void teacher()
{
}

void admin()
{
}
