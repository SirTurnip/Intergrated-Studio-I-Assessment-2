

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string permissionType;

class TLogin {
public:
	string permissionType;
};


struct User {
	string firstName;
	string lastName;
	string permissionType;
	string email;
	string password;

	//constructor
	User(string fN = "Adam", string lN = "Smith", string pT = "parent", string em = "abcd@gmail.com", string pW = "Abcd1234!") {
		firstName = fN;
		lastName = lN;
		permissionType = pT;
		email = em;
		password = pW;
	}
};

string adminID = "admin";
string adminPw = "SchoolM"

void LoginMenu();
void AdminLogin();
void TeacherLogin();
void ParentLogin();
void RegisterLogin();
void Login();
void TLogin();
void Notification();
void ManageStudent();
void ManageReport();

int main()
{
	
	LoginMenu();




}

void LoginMenu() {
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
		AdminLogin();
		break;
	case 2:
		TeacherLogin();
		break;
	case 3:
		ParentLogin();
		break;
	case 4:
		RegisterLogin();
		break;
	case 5:
		exit;
		break;

	}

}

void AdminLogin() {
	system("cls");
	cout << "----------Admin Login----------" << endl << endl;

	
	//display menu options

	/*int select;

	cout << endl<<endl<<"*****Select from the following*****" << endl;
	cout << "1. Notification" << endl;
	cout << "2. Manage student details" << endl;
	cout << "3. Manage report/marks" << endl;
	cout << "4. Back to main menu" << endl;
	cout << "Enter the number from the menu : " << endl;
	cin >> select;//choose what you want from the menu

	switch (select) {
	case 1:
		Notification();
		break;
	case 2:
		ManageStudent();
		break;
	case 3:
		ManageReport();
		break;
	case 4:
		main();
		break;

	}*/

}
void TeacherLogin() {
	system("cls");
	cout << "----------Teacher Login----------" << endl << endl;

	TLogin();
	



}


void ParentLogin() {
	system("cls");
	cout << "----------Parent Login----------" << endl << endl;

	//check if in correct permission type
	bool success = false;
	int fail = 2;
	string email, password, line, em, pw, pm;
	while (!success && fail >= 0) {
		cout << "Enter email :";
		cin >> email;
		cout << "Enter password : ";
		cin >> password;

		//open file to match first name and last name 
		fstream user("logs.csv");

		while (user >> em) {

			//login successful
			if (em.find("," + email + ",") != string::npos && em.find("," + password + ",") != string::npos) {
				success = true;
			}

		}

		if (!success) { //did not find match in file
			cout << endl << "Invalid login.. Please try again" << endl;
			cout << "You have " << fail << " tries left." << endl << endl;
			fail--;

		}

	}
	if (!success) {
		cout << endl << "Login NOT successful" << endl;

	}
	else {
		fstream check("logs.csv");
		while (check >> em ) {

			if (em.find(","+ "parent"+ ", " +em + ", ") != string::npos) {
				success = true;
			}

		}


		if (success) {
			cout << endl << "You are now logged in as PARENT." << endl;

		}

		else {
			cout << "Does not match user. Go back to main menu and start over. " << endl;
			
		}

	}



}

void PLogin() {
	


}

void TLogin() {
	//check if in correct permission type
	bool success = false;
	int fail = 2;
	string email, password, teacher, line, em, pw, pm;
	while (!success && fail >= 0) {
		cout << "Enter email :";
		cin >> email;
		cout << "Enter password : ";
		cin >> password;

		//open file to match first name and last name 
		fstream user("logs.csv");

		while (user >> em) {

			//login successful
			if (em.find("," + email + ",") != string::npos && em.find("," + password) != string::npos) {
				success = true;
			}

		}

		if (!success) { //did not find match in file
			cout << endl << "Invalid login.. Please try again" << endl;
			cout << "You have " << fail << " tries left." << endl << endl;
			fail--;

		}

	}
	if (!success) {
		cout << endl << "Login NOT successful and program has ended." << endl;

	}
	else {
		fstream check("logs.csv");
		while (check >> em >> line) {

			if (line.find("," + em + "," + "teacher" + ",") != string::npos) {
				success = true;
			}

		}


		if (success) {
			cout << endl << "You are now logged in as TEACHER." << endl;

		}

		else {
			cout << "Does not match user. Go back to main menu and start over. " << endl;
			main();
		}

	}


}




void RegisterLogin() {
	system("cls");

	cout << "----------Register Login----------" << endl << endl;


	//check if first name and last name match existing record 
		//check if register details match with current parent in parents.csv
	bool success = false;
	string firstName, lastName, permissionType, fn, ln, pm;
	string teacher, parent;


	cout << "Enter your first name : ";
	cin >> firstName;
	cout << "Enter your last name : ";
	cin >> lastName;


	fstream check("parents.csv");


	while (check >> fn) {

		if (fn.find(firstName + ",") != string::npos && fn.find("," + lastName) != string::npos) {
			success = true;
		}


	}

	if (success) {
		cout << endl << "Your details match our system record. You can now register as PARENT user." << endl;
		permissionType = "parent";

	}

	else {
		fstream check("teachers.csv");
		while (check >> fn) {

			if (fn.find(firstName + ",") != string::npos && fn.find("," + lastName) != string::npos) {
				success = true;
			}


		}

		if (success) {
			cout << endl << "Your details match our system record. You can now register as TEACHER user." << endl;
			permissionType = "teacher";

		}

		else {
			cout << "Invalid user. Please check first name and last name." << endl;
			
			RegisterLogin();
		}


	}
	check.close();

	//username
	cout << endl << "----Set login details----" << endl << endl;
	string email;
	int flag = 0;
	do {
		cout << "Enter valid email address : ";
		cin >> email;

		int i;
		for (i = 0; i < email.size(); i++) {


			if (email[i] == '@')
				flag = 1;


		}

	} while (!(flag == 1));
	cout << "This is a valid email" << endl << endl;



	//password 
	int l_case = 0, u_case = 0, digit = 0, special = 0;
	string password;
	size_t l;
	do {
		cout << endl << "*Password MUST contain atleast 8 characters, 1 Uppercase, 1 Lowercase, 1 number AND 1 special character" << endl;
		cout << "Enter Password" << endl;
		cin >> password;
		l = password.length();
		size_t i;
		for (i = 0; i < l; i++) {
			if (islower(password[i]))
				l_case = 1;
			if (isupper(password[i]))
				u_case = 1;
			if (isdigit(password[i]))
				digit = 1;
			if (!isalpha(password[i]) && !isdigit(password[i]))
				special = 1;
		}
	} while (!(l_case && u_case && digit && special && l >= 8));
	cout << "Registration successful" << endl;


	fstream user("logs.csv", ios::app);
	user << firstName << "," << lastName << "," << permissionType << "," << email << "," << password << endl;
	user.close();


	system("cls");
	main();

}

void Notification() {

}

void ManageStudent() {

}

void ManageReport() {

}
