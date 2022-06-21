#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

enum Sections { firstName = 0, lastName = 1, phone = 2, email = 3, id = 2, reportSubject = 0, grade = 1 };
enum Permissions { teacher = 1, admin = 2, parent = 3 };

vector<vector<string>> content;
vector<string> row;

class Parents {
public:
    enum ParentNames { Errol = 0, Maye = 1, Marco = 6, Rebekah = 7, John = 12, Jane = 13, Dany = 18, Emelia = 19 };

    string name[2];
    string number;

    void MyFunction() {
        //first & last name
        name[firstName] = content[John][firstName];
        name[lastName] = content[John][lastName];

        //phone number
        number = content[John][phone];
    }
};
Parents parents;

void ReadFile() {
    fstream f;
    f.open("C:/Users/Auren/Documents/Assessment 2/notifications/parents.csv");

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
}

class Notification {
public:
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

    void Parent() {
        int sec = 0;
        for(int i = 0; i < content.size(); i++) {
            if(i - sec == 0 || i - sec == 1) {
                if(parents.name[firstName] == content[i][firstName] && parents.name[lastName] == content[i][lastName]) {
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

int main() {
    ReadFile();
    parents.MyFunction();

    string input;
    cout << "Enter Permission Type" << endl;
    cout << "1. Teacher" << endl;
    cout << "2. Admin" << endl;
    cout << "3. Parent" << endl;
    cout << "Input: ";
    cin >> input;

    int permissionType = 0;

    stringstream ss;
    ss << input;
    ss >> permissionType;

    if(permissionType == teacher) {
        string subject = "English";
        notification.Teacher(subject);
    } else if(permissionType == admin) {
        notification.Admin();
    } else if(permissionType == parent) {
        notification.Parent();
    }
}
