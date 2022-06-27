#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<string>> content;
vector<string> row;

class Parent {
public:
    enum Sections { firstName = 0, lastName = 1 };
    int sectionSize = 3;

    string parentName[2];
    void ParentPrint(int index) {

        parentName[firstName] = content[index][firstName];
        parentName[lastName] = content[index][lastName];


        //log(name[firstName], name[lastName]);
        //log(schedule);
    }

    void ParentRead() {
        //initialize input variables
        ReadFile(3);
        string myInput[2];

        // get parent name
        cout << "firstName lastName: ";
        cin >> myInput[firstName] >> myInput[lastName];


        //clear line
        cout << "\033[A\r\33[2K";

        //call print function
        int sec = 0;
        for (int i = 0; i < content.size(); i++) {
            if (i - sec == 0) { // name
                if (content[i][firstName] == myInput[firstName] && content[i][lastName] == myInput[lastName]) {
                    ParentPrint(i);
                }
            }
        }
    }
};
Parent parent;

int main() {

}
