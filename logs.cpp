//log(name[firstName], name[lastName], studentId);
//log(schedule);

//log(name[firstName], name[lastName], classSubject, roomNum);
//log(schedule);

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void log(string firstName, string lastName, string permType, string fileName, string action) {
	ofstream logFile;
	logFile.open("logs.csv", std::ios_base::app);
	logFile << "\n\n" << firstName << "," << lastName << "," << permType << "\n" << fileName << "," << action;
	logFile.close();
}

int main() {


}
