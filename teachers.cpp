#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<string>> content;
vector<string> row;

enum Sections { firstName = 0, lastName = 1, gender = 2, date = 0, month = 1, year = 2, subject = 0, room = 1, classTime = 0, period = 1 };

class Teacher {
    public:
        int sectionSize = 17;

        string name[2];
        string sex;

        string classSubject;
        int roomNum = 0;

        string age[3];

        void MyFunction(int index) {
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

            cout << name[firstName] << " " << name[lastName] << " " << sex << endl;
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
};
Teacher teacher;

int main() {
    fstream f;
    f.open("C:/Users/Auren/Documents/Assessment 2/teachers/teachers.csv");

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
                teacher.MyFunction(i);
            }
        } else if(i - sec == 2) { //subject || room
            if(content[i][subject] == myInput[subject]) { //subject
                teacher.MyFunction(i - 2);
            } else if(content[i][room] == myInput[room]) { //room
                teacher.MyFunction(i - 2);
            }
        }

        if(content[i].size() == 0) {
            sec = i + 1;
        }
    }
}
