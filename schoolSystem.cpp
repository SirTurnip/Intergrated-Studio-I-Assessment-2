#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<string>> content;
vector<string> row;

int ReadFile(int fileType) {
    fstream f;
    f.close();

    content.clear();

    enum FileType { students = 1, teachers = 2, parents = 3, notifications = 3, users = 4 };

    int x = 0;
    if(fileType == students) {
        f.open("students.csv");
        x = students;
    } else if(fileType == teachers) {
        f.open("teachers.csv");
        x = teachers;
    } else if(fileType == parents) {
        f.open("parents.csv");
        x = parents;
    } else if(fileType == users) {
        f.open("users.csv");
        x = users;
    }

    string word;
    string line;

    while(getline(f, line)) {
        row.clear();
        stringstream s(line);

        while(getline(s, word, ',')) {
            row.push_back(word);
        }
        content.push_back(row);
    }

    return x;
}

class Student {
public:
    enum Sections { firstName = 0, lastName = 1, gender = 2, id = 3, date = 0, month = 1, year = 2, inputId = 0 };

    int sectionSize = 8;

    string name[2];
    string sex;
    int studentId = 0;

    string age[3];

    void StudentPrint(int index) {
        stringstream ss;

        name[firstName] = content[index][firstName];
        name[lastName] = content[index][lastName];
        sex = content[index][gender];
        ss << content[index][id];
        ss >> studentId;

        age[date] = content[index + 1][date];
        age[month] = content[index + 1][month];
        age[year] = content[index + 1][year];

        cout << name[firstName] << " " << name[lastName] << " " << sex << " " << studentId << endl;
        cout << age[date] << "/" << age[month] << "/" << age[year] << endl;

        string inp;
        cout << "'Monday' or 'Tuesday': ";
        cin >> inp;

        //clear line
        cout << "\033[A\r\33[2K";

        int dayIndex = 0;
        int extra = 0;
        cout << endl;
        if(inp == "Monday") {
            dayIndex = 2;
            extra = 3;
        } else if(inp == "Tuesday") {
            dayIndex = 5;
        }

        vector<vector<string>> schedule;

        for(int i = index + dayIndex; i < index + sectionSize - extra; i++) {
            schedule.push_back(content[i]);
        }

        for(int i = 0; i < schedule.size(); i++) {
            for(int j = 0; j < schedule[i].size(); j++) {
                cout << schedule[i][j] << " ";
            }
            cout << endl;
        }

        //log(name[firstName], name[lastName], studentId);
        //log(schedule);
    }

    void StudentRead() {
        ReadFile(1);

        //initialize input variables
        string myInput[2];

        //set input type
        string inp;
        cout << "Type 'name' or 'id': ";
        cin >> inp;

        //clear line
        cout << "\033[A\r\33[2K";

        //get input type
        if(inp == "name") {
            cout << "firstName lastName: ";
            cin >> myInput[firstName] >> myInput[lastName];
        } else if(inp == "id") {
            cout << "id: ";
            cin >> myInput[inputId];
        }

        //clear line
        cout << "\033[A\r\33[2K";

        //call print function
        int sec = 0;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 0) { //name
                if(content[i][firstName] == myInput[firstName] && content[i][lastName] == myInput[lastName]) {
                    StudentPrint(i);
                } else if(content[i][id] == myInput[inputId]) {
                    StudentPrint(i);
                }
            }

            if(content[i].size() == 0) {
                sec = i + 1;
            }
        }
    }
};
Student student;

class Teacher {
public:
    enum Sections { firstName = 0, lastName = 1, gender = 2, date = 0, month = 1, year = 2, subject = 0, room = 1, classTime = 0, period = 1 };

    int sectionSize = 17;

    string name[2];
    string sex;

    string classSubject;
    int roomNum = 0;

    string age[3];

    void TeacherPrint(int index) {
        stringstream ss;

        name[firstName] = content[index][firstName];
        name[lastName] = content[index][lastName];
        sex = content[index][gender];

        age[date] = content[index + 1][date];
        age[month] = content[index + 1][month];
        age[year] = content[index + 1][year];

        classSubject = content[index + 2][subject];

        ss << content[index + 2][room];
        ss >> roomNum;

        cout << name[firstName] << " " << name[lastName] << endl;
        cout << sex << endl;
        cout << age[date] << "/" << age[month] << "/" << age[year] << endl;
        cout << classSubject << " " << roomNum << endl;

        string inp;
        cout << "'Monday' or 'Tuesday': ";
        cin >> inp;

        //clear line
        cout << "\033[A\r\33[2K";

        int pos = 0;
        int extra = 0;
        cout << endl;
        if(inp == "Monday") {
            pos = 3;
            extra = 7;
        } else if(inp == "Tuesday") {
            pos = 10;
        }

        vector<vector<string>> schedule;

        for(int i = index + pos; i < index + sectionSize - extra; i++) {
            schedule.push_back(content[i]);
        }

        for(int i = 0; i < schedule.size(); i++) {
            for(int j = 0; j < schedule[i].size(); j++) {
                cout << schedule[i][j] << " ";
            }
            cout << endl;
        }

        //log(name[firstName], name[lastName], classSubject, roomNum);
        //log(schedule);
    }

    void TeacherRead() {
        ReadFile(2);

        string inp;
        cout << "Enter 'name' 'subject' or 'room': ";
        cin >> inp;

        //clear line
        cout << "\033[A\r\33[2K";

        //initialize input variable
        string myInput[2] = {";", ";"};

        if(inp == "name") {
            cout << "Enter Name: ";
            cin >> myInput[firstName] >> myInput[lastName];
        } else if(inp == "subject") {
            cout << "Enter Subject: ";
            cin >> myInput[subject];
        } else if(inp == "room") {
            cout << "Enter Room Number: ";
            cin >> myInput[room];
        }

        //clear line
        cout << "\033[A\r\33[2K";

        //call print function
        int sec = 0;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 0) { //name
                if(content[i][firstName] == myInput[firstName] && content[i][lastName] == myInput[lastName]) {
                    TeacherPrint(i);
                }
            } else if(i - sec == 2) { //subject || room
                if(content[i][subject] == myInput[subject]) { //subject
                    TeacherPrint(i - 2);
                } else if(content[i][room] == myInput[room]) { //room
                    TeacherPrint(i - 2);
                }
            }

            if(content[i].size() == 0) {
                sec = i + 1;
            }
        }
    }
};
Teacher teacher;

class Notification {
public:
    enum Sections { firstName = 0, lastName = 1, phone = 2, email = 3, id = 2, reportSubject = 0, grade = 1 };

    int size = 5;

    void Teacher(string subject) {
        ReadFile(3);

        int sec = 0;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 3 || i - sec == 4) {
                if(content[i][reportSubject] == subject) {
                    cout << content[i - (i - sec)][email] << endl;
                    cout << content[i - (i - sec) + 1][email] << endl;
                }
            }

            if(content[i].size() == 0) {
                sec = i + 1;
            }
        }
    }

    void Admin() {
        int sec = 0;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 0 || i - sec == 1) {
                cout << content[i][email] << endl;
            }

            if(content[i].size() == 0) {
                sec = i + 1;
            }
        }
    }

    void Report(int index, int sec) {
        for(int i = index; i < content.size(); i++) {
            if(i - sec == 3 || i - sec == 4) {
                for(int j = 0; j < content[i].size(); j++) {
                    cout << content[i][j] << " ";
                }
                cout << endl;
            }

            if(content[i].size() == 0) {
                return;
            }
        }
    }

    void Parent(string name[2]) {
        ReadFile(3);

        int sec = 0;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 0 || i - sec == 1) {
                if(name[firstName] == content[i][firstName] && name[lastName] == content[i][lastName]) {
                    Report(i, sec);
                }
            }

            if(content[i].size() == 0) {
                sec = i + 1;
            }
        }
    }
};
Notification notification;

class User {
public:
    string name[2];
    string userEmail;
    int userPermissionType = 0;

    void PrintUser() {
        enum UserData { firstName = 0, lastName = 1, email = 2, password = 3, permissionType = 4 };
        enum PermissoionTypes { teachers = 2, parents = 3, admin = 4 };

        cout << name[firstName] << " " << name[lastName] << endl;
        cout << userEmail << endl;

        switch(userPermissionType) {
            case teachers:
                cout << "Teacher" << endl;
                break;
            case parents:
                cout << "Parent" << endl;
                break;
            case admin:
                cout << "Admin" << endl;
                break;
            default:
                break;
        }
    }

    void SchoolSystem() {
        PrintUser();

        enum UserData { firstName = 0, lastName = 1, email = 2, password = 3, permissionType = 4 };
        enum PermissoionTypes { teachers = 2, parents = 3, admin = 4 };

        int input = 0;
        if(userPermissionType == teachers) {
            cout << "1. Teachers" << endl;
            cout << "2. Parents" << endl;
            cout << "3. Notifications" << endl;

            cin >> input;
            if(input == 1) {
                //teachers
                teacher.TeacherRead();
            } else if(input == 2) {
                //parents
            } else if(input == 3) {
                //notifications

                ReadFile(teachers);

                int sec = 0;
                for(int i = 0; i < content.size(); i++) {
                    if(i - sec == 0) {
                        if(content[i][firstName] == name[firstName] && content[i][lastName] == name[lastName]) {
                            notification.Teacher(content[i + 2][0]);
                            return;
                        }
                    }

                    if(content[i].size() == 0) {
                        sec = i + 1;
                    }
                }
            }
        } else if(userPermissionType == parents) {
            cout << "1. Parents" << endl;
            cout << "2. Students" << endl;

            cin >> input;
            if(input == 1) {
                //parents
                notification.Parent(name);
            } else if(input == 2) {
                //students
                student.StudentRead();
            }
        } else if(userPermissionType == admin) {
            cout << "1. Students" << endl;
            cout << "2. Teachers" << endl;
            cout << "3. Parents" << endl;
            cout << "4. Notifications" << endl;

            cin >> input;
        }
    }

    void AddUser(int permissionType, string name[2]) {
        cout << "Enter Email: ";
        string email;
        cin >> email;

        string input;
        cout << "Enter Password: ";
        cin >> input;

        fstream f("users.csv", ios::app);
        f << name[0] << "," << name[1] << "," << email << "," << input << "," << permissionType << endl;
    }

    int Regester() {
        enum FileType { teachers = 2, parents = 3 };

        bool findUser = true;
        int runIndex = teachers;

        string input[2];

        string userEmail;

        enum MyEnum { firstName = 0, lastName = 1, email = 3 };

        cout << "Enter Name: ";
        cin >> input[firstName] >> input[lastName];

        for(int i = teachers; i <= parents; i++) {
            int x = ReadFile(i);

            int sec = 0;
            bool success = false;

            for(int j = 0; j < content.size(); j++) {
                if(sec - j == 0 || sec - j == -1) {
                    if(content[j][firstName] == input[firstName] && content[j][lastName] == input[lastName]) {
                        cout << "User Verified!" << endl;
                        success = true;
                    }
                }

                if(content[j].size() == 0) {
                    sec = j + 1;
                }
            }

            if(success) {
                AddUser(runIndex, input);
                findUser = false;
            } else {
                if(runIndex == teachers) {
                    //first run
                    runIndex = parents;
                } else {
                    //second run
                    cout << "User Not Found!" << endl;
                    return 0;
                }
            }
        }
        return 0;
    }

    int Login() {
        int x = ReadFile(4);

        int sec = 0;
        bool success = false;

        enum UserData { firstName = 0, lastName = 1, email = 2, password = 3, permissionType = 4 };

        string input[2];

        int runIndex = 3;
        while(runIndex > 0) {
            cout << "Enter Email: ";
            cin >> input[0];

            cout << "Enter Password: ";
            cin >> input[1];

            for(int i = 0; i < content.size(); i++) {
                if(content[i][email] == input[0] && content[i][password] == input[1]) {
                    cout << "Loged In!" << endl;
                    success = true;
                    runIndex = 0;

                    name[firstName] = content[i][firstName];
                    name[lastName] = content[i][lastName];
                    userEmail = content[i][email];

                    stringstream ss;
                    ss << content[i][permissionType];
                    ss >> userPermissionType;

                    SchoolSystem();
                    break;
                }
            }

            if(success == false) {
                cout << "Incorrect! (" << runIndex - 1 << " Tries Left)" << endl;
                runIndex--;
            }
        }

        return 0;
    }
};
User user;

int main() {
    int inp;
    cout << "1. Login" << endl;
    cout << "2. Regester" << endl;
    cin >> inp;

    if(inp == 1) {
        user.Login();
    } else {
        user.Regester();
    }
}