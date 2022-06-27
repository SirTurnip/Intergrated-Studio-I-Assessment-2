

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


string adminPassword = "SchoolAdmin123!";

void LoginMenu();
void AdminLogin();
void TeacherLogin();
void ParentLogin();
void RegisterLogin();
void Login();
void AdminMenu();
void TeacherMenu();
void Notification();
void ManageStudent();
void ManageReport();

bool __exit = false;

int main()
{

	while (!__exit) {
		LoginMenu();
	}
	
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
		__exit = true;
		break;

	}

}

void AdminLogin() {
	system("cls");
	cout << "----------Admin Login----------" << endl << endl;

	bool success = false;
	int guessCount = 2;
	string firstName, lastName, password;
	while (!success && guessCount >= 0) {
		cout << "Enter first and last name :";
		cin >> firstName >> lastName;
		cout << "Enter password : ";
		cin >> password;


		if (password == adminPassword) {
			success = true;
		}


		if (!success) {

			cout << "Invalid password. Please try again." << endl;
			cout << "You have " << guessCount << " tries left." << endl << endl;
			guessCount--;

		}

		else {
			cout << "Login success. You are now logged in as admin." << endl;

		}

	}
	AdminMenu();
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

	//check if in correct permission type
	bool success = false;
	int fail = 2;//3 tries to login
	string email, password, line, word, em, pw;
	int backMain;
	bool emailok = false;
	bool passwordok = false;
	bool roleok = false;
	bool role_not_match = false;
	while (!success && fail >= 0) {
		cout << "Enter email :";
		cin >> email;
		cout << "Enter password : ";
		cin >> password;

		//open file to match email and password
		fstream user;
		user.open("logs.csv");

		while (getline(user, line)) {
			stringstream s(line);
			emailok = false;
			passwordok = false;
			roleok = false;
			while (getline(s, word, ',')) {
				if (word == email) {
					emailok = true;
				}
				if (word == password) {
					passwordok = true;
				}
				if (word == "teacher") {
					roleok = true;
				}
			}
			if (emailok && passwordok && roleok) {
				success = true;
				role_not_match = false;
				break;
			}
			else if (emailok && passwordok && !roleok) {
				role_not_match = true;
			}
		}
		user.close(); //close file

		if (!success) { //email and passworld did not match 
			if (role_not_match) {
				cout << "Invalid user. This is for teaher login. Press 0 to return to main page." << endl << endl;
				cin >> backMain;
				if (backMain == 0) {
					system("cls");
					/*LoginMenu();*/
					fail = -1;
				}
			}
			else {
				cout << endl << "Invalid login.. Please try again" << endl;
				cout << "You have " << fail << " tries left." << endl << endl;
				fail--;
			}

		}
		else {
			cout << endl << "You are now logged in as TEACHER." << endl;
		}
	}


}


void ParentLogin() {
	system("cls");
	cout << "----------Parent Login----------" << endl << endl;

	//check if in correct permission type
	bool success = false;
	int fail = 2;//3 tries to login
	string email, password, line, word, em, pw;
	int backMain;
	bool emailok = false;
	bool passwordok = false;
	bool roleok = false;
	bool role_not_match = false;
	while (!success && fail >= 0) {
		cout << "Enter email :";
		cin >> email;
		cout << "Enter password : ";
		cin >> password;

		//open file to match email and password
		fstream user;
		user.open("logs.csv");

		while (getline(user, line)) {
			stringstream s(line);
			emailok = false;
			passwordok = false;
			roleok = false;
			while (getline(s, word, ',')) {
				if (word == email) {
					emailok = true;
				}
				if (word == password) {
					passwordok = true;
				}
				if (word == "parent") {
					roleok = true;
				}
			}
			if (emailok && passwordok && roleok) {
				success = true;
				role_not_match = false;
				break;
			}
			else if (emailok && passwordok && !roleok) {
				role_not_match = true;
			}
		}
		user.close(); //close file

		if (!success) { //email and passworld did not match 
			if (role_not_match) {
				cout << "Invalid user. This is for parent login. Press 0 to return to main page." << endl << endl;
				cin >> backMain;
				if (backMain == 0) {
					system("cls");
					/*LoginMenu();*/
					fail = -1;
				}
			}
			else {
				cout << endl << "Invalid login.. Please try again" << endl;
				cout << "You have " << fail << " tries left." << endl << endl;
				fail--;
			}

		}
		else {
			cout << endl << "You are now logged in as PARENT." << endl;
		}
	}

}


void RegisterLogin() {
	system("cls");

	cout << "----------Register Login----------" << endl << endl;


	//check if first name and last name match existing record 

	bool success = false;
	string firstName, lastName, permissionType, fn, ln, pm, line, word;
	string teacher, parent;
	bool fnameok = false;
	bool lnameok = false;
	while (!success) {
		cout << "Enter your first name : ";
		cin >> firstName;
		cout << "Enter your last name : ";
		cin >> lastName;

		fstream check;	//check if register details match with current parent in parents.csv
		check.open("parents.csv");

		while (getline(check, line)) {
			stringstream s(line);
			fnameok = false;
			lnameok = false;
			while (getline(s, word, ',')) {
				if (word == firstName) {
					fnameok = true;
				}
				if (word == lastName) {
					lnameok = true;
				}
			}
			if (fnameok && lnameok) {
				success = true;
				break;
			}
		}
		check.close();
		if (success) {
			cout << endl << "Your details match our system record. You can now register as PARENT user." << endl;
			permissionType = "parent";
			break;
		}

		else {
			//check if register details match with current teacher in teachers.csv
			check.open("teachers.csv");
			while (getline(check, line)) {
				stringstream s(line);
				fnameok = false;
				lnameok = false;
				while (getline(s, word, ',')) {
					if (word == firstName) {
						fnameok = true;
					}
					if (word == lastName) {
						lnameok = true;
					}
				}
				if (fnameok && lnameok) {
					success = true;
					break;
				}
			}
		}
		if (success) {
			cout << endl << "Your details match our system record. You can now register as TEACHER user." << endl;
			permissionType = "teacher";



		}

		else {
			cout << endl << "Invalid user. Please check first name and last name." << endl;

		}
		check.close();
	}



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

}

void AdminMenu() {
	cout << endl << "Select from following";


}

