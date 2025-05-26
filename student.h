#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Student {
private:
    string Name;
    string Registration_No;  // Change to string to store formatted ID
    vector<string> Attendance_Dates;
    vector<bool> present;

public:
    Student();
    Student(string Name, int id);  
    ~Student();

    string getName() const;
    string getRegistration_No() const;  
    void setName(string name);

    void markAttendance(string date, bool isPresent);
    void viewAttendance();
    float getAttendancePercentage();

    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);

    map<string, bool> getAttendanceRecords() const; // Added for table export
};

#endif

