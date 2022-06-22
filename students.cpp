#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<string>> content;
vector<string> row;

enum Sections { firstName = 0, lastName = 1, gender = 2, id = 3, date = 0, month = 1, year = 2, inputId = 0 };

class Student {
public:
    int sectionSize = 8;

    string name[2];
    string sex;
    int studentId = 0;

    string age[3];

    void MyFunction(int index) {
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
};
Student student;

int main() {
    fstream studentsFile;
    studentsFile.open("C:/Users/Auren/Documents/Assessment 2/students/students.csv");

    string word;
    string line;

    while(getline(studentsFile, line)) {
        row.clear();
        stringstream s(line);

        while(getline(s, word, ',')) {
            row.push_back(word);
        }
        content.push_back(row);
    }

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
                student.MyFunction(i);
            } else if(content[i][id] == myInput[inputId]) {
                student.MyFunction(i);
            }
        }

        if(content[i].size() == 0) {
            sec = i + 1;
        }
    }
}
