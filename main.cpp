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

    enum FileType { students = 1, teachers = 2, notifications = 3 };

    int x = 0;
    if(fileType == students) {
        f.open("C:/Users/Auren/Documents/Assessment 2/Assessment 2/students.csv");
        x = students;
    } else if(fileType == teachers) {
        f.open("C:/Users/Auren/Documents/Assessment 2/Assessment 2/teachers.csv");
        x = teachers;
    } else if(fileType == notifications) {
        f.open("C:/Users/Auren/Documents/Assessment 2/Assessment 2/parents.csv");
        x = notifications;
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
    enum UserSections { firstName = 0, lastName = 1, phone = 2 };

    enum ParentNames { Errol = 0, Maye = 1, Marco = 6, Rebekah = 7, John = 12, Jane = 13, Dany = 18, Emelia = 19 };
    enum Permissions { teacher = 1, admin = 2, parent = 3 };

    int permissionType = teacher;

    string name[2];
    string number;

    string subject = "English";

    void Login() {
        //first & last name
        name[firstName] = content[John][firstName];
        name[lastName] = content[John][lastName];

        //phone number
        number = content[John][phone];

        if(permissionType == teacher) {
            notification.Teacher(subject);
        } else if(permissionType == admin) {
            notification.Admin();
        } else if(permissionType == parent) {
            notification.Parent(name);
        }
    }
};
User user;

int main() {
    enum FileType { students = 1, teachers = 2, notifications = 3 };

    cout << "1. Students" << endl;
    cout << "2. Teachers" << endl;
    cout << "3. Notifications" << endl;
    int input;
    cin >> input;

    //clear 4 lines
    cout << "\033[A\r\33[2K\033[A\r\33[2K\033[A\r\33[2K\033[A\r\33[2K";

    int fileType = input;

    int x = ReadFile(fileType);
  
    if(x == students) {
        student.StudentRead();
    } else if(x == teachers) {
        teacher.TeacherRead();
    } else if(x == notifications) {
        user.Login();
    }   

	return 0;
}