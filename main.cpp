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

void Log(int logType, vector<vector<string>> logContent);

class Parent {
public:
    enum Sections { firstName = 0, lastName = 1 };
    int sectionSize = 3;

    string parentName[2];
    void ParentPrint(int index) {
        parentName[firstName] = content[index - 2][firstName];
        parentName[lastName] = content[index - 2][lastName];

        vector<vector<string>> logContent = {{content[index][firstName], content[index][lastName]}};
        Log(6, logContent);
    }

    bool ParentRead(bool admin, string subject) {
        //initialize input variables
        ReadFile(3);
        string myInput[2];

        // get parent name
        cout << "Enter Student Name: ";
        cin >> myInput[firstName] >> myInput[lastName];

        //clear line
        cout << "\033[A\r\33[2K\033[A\r\33[2K";

        //call print function
        int sec = 0;

        bool isStudent = false;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 2) { // name
                if(content[i][firstName] == myInput[firstName] && content[i][lastName] == myInput[lastName]) {
                    if(admin) {
                        isStudent = true;
                        ParentPrint(i);
                        return true;
                    } else {
                        if(content[i + 1][0] == subject || content[i + 2][0] == subject) {
                            isStudent = true;
                            ParentPrint(i);
                            return true;
                        }
                    }         
                }
            }

            if(content[i].size() == 0) {
                sec = i + 1;
            }
        }

        if(isStudent == false) {
            cout << endl << "Student Does Not Attend Your Class!" << endl;
            return false;
        }
    }
};
Parent parent;

class Student {
public:
    enum Sections { firstName = 0, lastName = 1, gender = 2, id = 3, date = 0, month = 1, year = 2, inputId = 0 };

    int sectionSize = 8;

    string name[2];
    string sex;
    int studentId = 0;

    string age[3];

    vector<vector<string>> schedule;

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

        for(int i = index + dayIndex; i < index + sectionSize - extra; i++) {
            schedule.push_back(content[i]);
        }

        for(int i = 0; i < schedule.size(); i++) {
            for(int j = 0; j < schedule[i].size(); j++) {
                cout << schedule[i][j] << " ";
            }
            cout << endl;
        }

        Log(1, schedule);
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

        Log(3, schedule);
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

        vector<vector<string>> logContent;
        vector<string> logRow;

        int sec = 0;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 3 || i - sec == 4) {
                if(content[i][reportSubject] == subject) {
                    logRow.clear();
                    logRow.push_back(content[i - (i - sec)][email]);
                    logContent.push_back(logRow);

                    logRow.clear();
                    logRow.push_back(content[i - (i - sec) + 1][email]);
                    logContent.push_back(logRow);
                    
                    cout << content[i - (i - sec)][email] << endl;
                    cout << content[i - (i - sec) + 1][email] << endl;
                }
            }

            if(content[i].size() == 0) {
                sec = i + 1;
            }
        }

        Log(4, logContent);
    }

    void Admin() {
        ReadFile(3);

        vector<vector<string>> logContent;
        vector<string> logRow;

        int sec = 0;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 0 || i - sec == 1) {
                logRow.clear();
                logRow.push_back(content[i][email]);
                logContent.push_back(logRow);

                cout << content[i][email] << endl;
            }

            if(content[i].size() == 0) {
                sec = i + 1;
            }
        }

        Log(4, logContent);
    }

    void Report(int index, int sec) {
        vector<vector<string>> reportContent;

        bool r = false;
        for(int i = index; i < content.size(); i++) {;
            if(i - sec == 3 || i - sec == 4) {
                reportContent.push_back(content[i]);

                for(int j = 0; j < content[i].size(); j++) {
                    cout << content[i][j] << " ";
                }

                cout << endl;

                if(i - sec == 4) {
                    r = true;
                    break;
                }
            }
        }

        Log(2, reportContent);
        if(r) {
            return;
        }
    }

    void Parent(string name[2]) {
        ReadFile(3);

        int sec = 0;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 0 || i - sec == 1) {
                if(name[firstName] == content[i][firstName] && name[lastName] == content[i][lastName]) {
                    Report(i, sec);
                    break;
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

        switch(userPermissionType) {
            case teachers:
                cout << "Teacher: ";
                break;
            case parents:
                cout << "Parent: ";
                break;
            case admin:
                cout << "Admin: ";
                break;
            default:
                break;
        }

        cout << name[firstName] << " " << name[lastName] << endl;

        if(userPermissionType != admin) {
            cout << "Email: " << userEmail << endl;
        }

        cout << endl;
    }

    void SchoolSystem() {
        PrintUser();

        Log(0, content);

        enum UserData { firstName = 0, lastName = 1, email = 2, password = 3, permissionType = 4 };
        enum PermissoionTypes { teachers = 2, parents = 3, admin = 4 };

        int input = 0;
        if(userPermissionType == teachers) { //Teacher Loged In
            cout << "1. Teachers" << endl;
            cout << "2. Report" << endl;
            cout << "3. Notifications" << endl;

            cin >> input;

            //clear line
            cout << "\033[A\r\33[2K\033[A\r\33[2K\033[A\r\33[2K\033[A\r\33[2K";
            if(input == 1) {
                //teachers
                cout << "    Teachers" << endl;
                cout << "----------------" << endl;
                teacher.TeacherRead();
            } else if(input == 2) {
                //Report
                string subject;

                ReadFile(2);
                int sec = 0;
                for(int i = 0; i < content.size(); i++) {
                    if(i - sec == 0) { //name
                        if(content[i][firstName] == name[firstName] && content[i][lastName] == name[lastName]) {
                            subject = content[i + 2][0];
                        }
                    }

                    if(content[i].size() == 0) {
                        sec = i + 1;
                    }
                }

                bool isStudent = parent.ParentRead(false, subject);

                if(isStudent) {
                    cout << "    Report" << endl;
                    cout << "--------------" << endl;
                    notification.Parent(parent.parentName);
                }
            } else if(input == 3) {
                //notifications
                cout << "    Notifications" << endl;
                cout << "---------------------" << endl;

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
        } else if(userPermissionType == parents) { //Parent Loged In
            cout << "1. Report" << endl;
            cout << "2. Students" << endl;

            cin >> input;

            //clear line
            cout << "\033[A\r\33[2K\033[A\r\33[2K\033[A\r\33[2K";
            if(input == 1) {
                //parents
                cout << "    Report" << endl;
                cout << "--------------" << endl;
                notification.Parent(name);
            } else if(input == 2) {
                //students
                cout << "    Students" << endl;
                cout << "----------------" << endl;
                student.StudentRead();
            }
        } else if(userPermissionType == admin) {
            cout << "1. Students" << endl;
            cout << "2. Teachers" << endl;
            cout << "3. Report" << endl;
            cout << "4. Notifications" << endl;

            cin >> input;

            //clear lines
            cout << "\033[A\r\33[2K\033[A\r\33[2K\033[A\r\33[2K\033[A\r\33[2K\033[A\r\33[2K";
            if(input == 1) {
                //Students
                cout << "    Students" << endl;
                cout << "----------------" << endl;
                student.StudentRead();
            } else if(input == 2) {
                //Teachers
                cout << "    Teachers" << endl;
                cout << "----------------" << endl;
                teacher.TeacherRead();
            } else if(input == 3) {
                //Report
                cout << "1. Student Name" << endl;
                cout << "2. Parent Name" << endl;
                int inp = 0;
                cin >> inp;

                //clear lines
                cout << "\033[A\r\33[2K\033[A\r\33[2K\033[A\r\33[2K";
                
                if(inp == 1) {
                    //Enter Student Name
                    parent.ParentRead(true, "");
                    cout << "    Report" << endl;
                    cout << "--------------" << endl;
                    notification.Parent(parent.parentName);
                } else {
                    //Enter Parent Name
                    cout << "Enter Parent Name: ";
                    string inputName[2];
                    cin >> inputName[firstName] >> inputName[lastName];

                    //clear lines
                    cout << "\033[A\r\33[2K\033[A\r\33[2K";

                    cout << "    Report" << endl;
                    cout << "--------------" << endl;

                    vector<vector<string>> logContent = {{inputName[firstName], inputName[lastName]}};

                    Log(5, logContent);
                    notification.Parent(inputName);
                }
            } else if(input == 4) {
                //Notifications
                cout << "    Notifications" << endl;
                cout << "---------------------" << endl;

                notification.Admin();
            }
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
        f << endl << name[0] << "," << name[1] << "," << email << "," << input << "," << permissionType;
    }

    int Register() {
        cout << "    Regester" << endl;
        cout << "----------------" << endl;

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
        cout << "    Login" << endl;
        cout << "-------------" << endl;

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
                    system("cls");

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
                cout << endl << "Incorrect! (" << runIndex - 1 << " Tries Left)" << endl;
                runIndex--;
            }
        }

        return 0;
    }
};
User user;

void Log(int logType, vector<vector<string>> logContent) {
    enum UserData { firstName = 0, lastName = 1, email = 2, password = 3, permissionType = 4 };
    enum Permissions { teachers = 2, parents = 3, admin = 4 };

    enum LogTypes { login = 0, students = 1, report = 2, roll = 3, notifications = 4, parentName = 5, studentReport = 6 };

    string p[3]{"Teacher", "Parent", "Admin"};

    fstream f("logs.csv", ios::app);

    if(logType == login) {
        f << p[user.userPermissionType - 2] << " Login: " << user.name[firstName] << " " << user.name[lastName] << endl;
    } else if(logType == students) {
        f << "    Schedule" << endl;
        f << "----------------" << endl;
        f << "Student: " << student.name[firstName] << " " << student.name[lastName] << ", " << student.studentId << endl;

        for(int i = 0; i < logContent.size(); i++) {
            for(int j = 0; j < logContent[i].size(); j++) {
                f << logContent[i][j] << " ";
            }
            f << endl;
        }

        f << endl;
    } else if(logType == report) {
        f << "    Report" << endl;
        f << "--------------" << endl;

        for(int i = 0; i < logContent.size(); i++) {
            for(int j = 0; j < logContent[i].size(); j++) {
                f << logContent[i][j] << " ";
            }
            f << endl;
        }

        f << endl;
    } else if(logType == roll) {
        f << "    Roll" << endl;
        f << "------------" << endl;
        f << "Teacher: " << teacher.name[firstName] << " " << teacher.name[lastName] << ", " << teacher.classSubject << endl;

        for(int i = 0; i < logContent.size(); i++) {
            for(int j = 0; j < logContent[i].size(); j++) {
                f << logContent[i][j] << " ";
            }
            f << endl;
        }

        f << endl;
    } else if(logType == notifications) {
        f << "    Notifications" << endl;
        f << "---------------------" << endl;

        for(int i = 0; i < logContent.size(); i++) {
            for(int j = 0; j < logContent[i].size(); j++) {
                f << logContent[i][j] << " ";
            }
            f << endl;
        }

        f << endl;
    } else if(logType == parentName) {
        f << "Parent: " << logContent[0][firstName] << " " << logContent[0][lastName] << endl;
    } else if(logType == studentReport) {
        f << "Student: ";
        for(int i = 0; i < logContent.size(); i++) {
            for(int j = 0; j < logContent[i].size(); j++) {
                f << logContent[i][j] << " ";
            }
            f << endl;
        }
    }
    
    f.close();
}

int main() {
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;

    int input;
    cin >> input;

    system("cls");
    if(input == 1) {
        user.Login();
    } else if(input == 2) {
        user.Register();
    }

    return 0;
}
