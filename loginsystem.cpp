// login.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Register {
public:
	string firstName, lastName;
};

class Login {
public:
	string inFirstName, inLastName;
};


void loginMenu();
void adminLogin();
void teacherLogin();
void parentLogin();
void registerLogin();
void login();
void notification();
void manageStudent();
void manageReport();

int main()
{
	loginMenu();




}

void loginMenu() {
	int select;

	cout << "---------Login/Register---------" << endl;
	cout << "Select from the following" << endl;
	cout << "1. Admin login" << endl;
	cout << "2. Teacher login" << endl;
	cout << "3. Parent login" << endl;
	cout << "4. Register" << endl;
	cout << "5. Exit the program" << endl;
	cout << "Enter the number from the menu : " << endl;
	cin >> select;//choose what you want from the menu

	switch (select) {
	case 1:
		adminLogin();
		break;
	case 2:
		teacherLogin();
		break;
	case 3:
		parentLogin();
		break;
	case 4:
		registerLogin();
		break;
	case 5:
		exit;
		break;

	}

}

void adminLogin() {
	system("cls");
	cout << "----------Admin Login----------" << endl << endl;

	login();

	int select;

	cout << "Select from the following" << endl;
	cout << "1. Notification" << endl;
	cout << "2. Manage student details" << endl;
	cout << "3. Manage report/marks" << endl;
	cout << "4. Back to main menu" << endl;
	cout << "Enter the number from the menu : " << endl;
	cin >> select;//choose what you want from the menu

	switch (select) {
	case 1:
		notification();
		break;
	case 2:
		manageStudent();
		break;
	case 3:
		manageReport();
		break;
	case 4:
		main();
		break;

	}

}
void teacherLogin() {
	system("cls");
	cout << "----------Teacher Login----------" << endl << endl;

	login();




}


void parentLogin() {
	system("cls");
	cout << "----------Parent Login----------" << endl << endl;

	login();



}

void login() {
	bool success = false;
	int fail = 2;
	string logFirst, logLast, firstName, lastName;
	string line = " ";
	while (!success && fail >= 0) {
		cout << "Enter first name :";
		cin >> logFirst;
		cout << endl << "Enter last name : ";
		cin >> logLast;


		//open file to match first name and last name 
		fstream f("logs.csv");
		while (getline(f,line)) {
			stringstream iss(line);
			iss >> firstName >> lastName;
			//login successful
			if (logFirst == firstName && logLast == lastName) {
				success = true;
			}

		}
		if (!success) { //did not find match in file
			cout << endl<< "Invalid first name and last name. Please try again" << endl;
			cout << "You have " << fail << " tries left." << endl<<endl;
			fail--;

		}
	}

	if (success) {
		cout << "Login successful" << endl;
		cout << "You are now logged in as ";
	}
	else {
		cout << "Maximum login attempt. Try again later"<<endl;
		system("cls");
		main();

	}
}

void registerLogin() {
	system("cls");

	string firstName, lastName, permissionType;
	cout << "----------Register Login----------" << endl << endl;
	cout << "Enter your first name : ";
	cin >> firstName;
	cout << endl << "Enter your last name : ";
	cin >> lastName;
	cout << endl << "Choose from the following role: Admin, Teacher or Parent : ";
	cin >> permissionType;

	fstream f("logs.csv", ios::app);
	f << firstName << "," << lastName << "," << permissionType << "," << endl;
	
	int k;
	cout << "Registration successful" << endl;
	
	system("cls");
	main();

}

void notification() {

}

void manageStudent() {

}

void manageReport() {

}