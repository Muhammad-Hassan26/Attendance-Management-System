#include "student.h"
#include <iostream>
#include <iomanip>
#include <map>
using namespace std;

//Default constructor of class.
Student::Student() {
    Name = "";
    Registration_No = "";
}
//Parametric constructor of class.
Student::Student(string n, int id) {
    Name = n;
    Registration_No = "QAU-" + to_string(id); // Format the registration number as "QAU-<year>"
}
//Destructor of class.
Student::~Student() {}

string Student::getName() const {
    return Name;
}

string Student::getRegistration_No() const {
    return Registration_No;
}

void Student::setName(string n) {
    Name = n;
}

void Student::markAttendance(string date, bool isPresent) {
    Attendance_Dates.push_back(date);
    present.push_back(isPresent);
}

void Student::viewAttendance() {
    cout << left << setw(15) << "Date" << setw(10) << "Status" << endl;
    cout << string(50, '-') << endl;
    for (size_t i = 0; i < Attendance_Dates.size(); i++) {
        cout << left << setw(15) << Attendance_Dates[i]
             << setw(10) << (present[i] ? "Present" : "Absent") << endl;
    }
}

float Student::getAttendancePercentage() {
    if (Attendance_Dates.empty()) return 0;
    int presentCount = 0;
    for (bool p : present) {
        if (p) presentCount++;
    }
    return (presentCount * 100.0f) / Attendance_Dates.size();
}

// Save student data to file
void Student::serialize(ofstream& out) const {
    out << Name << '\n'
        << Registration_No << '\n'
        << Attendance_Dates.size() << '\n';
    for (size_t i = 0; i < Attendance_Dates.size(); ++i) {
        out << Attendance_Dates[i] << '\n'
            << present[i] << '\n';
    }
}

// Load student data from file
void Student::deserialize(ifstream& in) {
    getline(in, Name);
    getline(in, Registration_No);  // Adjusted to read the formatted registration number
    size_t count;
    in >> count;
    in.ignore(); // skip newline

    Attendance_Dates.clear();
    present.clear();

    for (size_t i = 0; i < count; ++i) {
        string date;
        bool status;
        getline(in, date);
        in >> status;
        in.ignore(); // skip newline
        Attendance_Dates.push_back(date);
        present.push_back(status);
    }
}

// Get attendance as date-status map
map<string, bool> Student::getAttendanceRecords() const {
    map<string, bool> records;
    for (size_t i = 0; i < Attendance_Dates.size(); ++i) {
        records[Attendance_Dates[i]] = present[i];
    }
    return records;
}
