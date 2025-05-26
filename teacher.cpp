#include "teacher.h"   // Includes Teacher class definition and dependencies
#include <iostream>    // For input/output
#include <fstream>    //  To read/write file
#include <iomanip>    // For formatted output
#include <algorithm>  // for std::sort
using namespace std;

void Teacher::login() {
    while (true) {
        int choice;
        cout << "======= Welcome to Attendance Management Portal =======\n";
        cout << "Login as:\n1. Teacher\n2. Student\n3. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) { //Teacher choice
            //Take credentials of teacher.
            string Teacher_Id, password;
            cout << "Enter Teacher Id: ";
            cin >> Teacher_Id;
            cout << "Enter Teacher Password: ";
            cin >> password;
            //Open teacher file (teacher.txt) and check credentials.
            bool authenticated = false;
            ifstream fin("teachers.txt");
            string id, pass;
            while (fin >> id >> pass) {
                if (Teacher_Id == id && password == pass) {
                    authenticated = true;
                    break;
                }
            }
            fin.close();
            //If valid teacher id and password matched.
            if (authenticated) {
                cout << "Teacher login successful.\n";
                teacherName = Teacher_Id;
                loadData();
            //Then show menu for teacher. 
                int option;
                do {
                    cout << "\n========= Teacher Menu =========\n";
                    cout << "\n1. Add Students To Class\n2. Mark The Attendance\n3. View All Students Attendance\n4. View Specific Student Records\n5. Edit Student Name\n6. Logout & Save\n7. Export Attendance Summary\nEnter choice: ";
                    cin >> option;
                    switch (option) {
                        case 1: addStudents(); break;
                        case 2: markAttendanceForAll(); break;
                        case 3: viewAttendance(); break;
                        case 4: viewStudentAttendance(); break;
                        case 5: editStudentName(); break;
                        case 6: saveData(); cout << "Logged out.\n"; break;
                        case 7: exportAttendanceSummary(); break;
                        default: cout << "Invalid option.\n";
                    }
                } while (option != 6);
            } else {
                cout << "Invalid credentials!\n";
            }

        } else if (choice == 2) {//Student choice
            string className;
            string regNo;
            cout << "Enter Class Name: ";
            cin >> className;
            cout << "Enter Registration Number: ";
            cin >> regNo;
            //Search for student and display attendance
            auto &students = classStudents[className];
            bool found = false;
            for (auto &student : students) {
                if (student.getRegistration_No() == regNo) {
                    cout << "Welcome, " << student.getName() << "!\n";
                    student.viewAttendance();
                    cout << "Attendance %: " << student.getAttendancePercentage() << "%\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Student not found.\n";
        } else {
            break;
        }
    }
}

//Add students to the class.
void Teacher::addStudents() {
    string className;
    cout << "Enter class name: ";
    cin >> className;
    int n;
    cout << "How many students to add in class " << className << "? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        string Name;
        int id;  // Using id instead of reg number input
        cout << "Enter name of student " << (i + 1) << ": ";
        cin >> Name;
        cout << "Enter id (e.g. 0410): ";
        cin >> id;
        classStudents[className].emplace_back(Name, id);  // Use id to generate the registration number
    }
    cout << "Added " << n << " students to class " << className << ".\n";
    //Record class-teacher mapping.
    ofstream out("classes.txt", ios::app);
    out << className << " " << teacherName << '\n';
    out.close();

}

//Mark the attendance of students added in respective class.
void Teacher::markAttendanceForAll() {
    char more;
    do {
        string className;
        cout << "Enter class name to mark attendance: ";
        cin >> className;

        auto &students = classStudents[className];
        if (students.empty()) {
            cout << "No students found in this class.\n";
        } else {
            string date;
            cout << "Enter date (dd-mm-yyyy): ";
            cin >> date;
         //Check if there is holiday or not.
            char holidayChoice;
            cout << "Is today a holiday? (Y/N): ";
            cin >> holidayChoice;
            if (holidayChoice == 'Y' || holidayChoice == 'y') {
                cout << "Attendance marked as holiday for all students.\n";
                break;
            }
            //mark attendance of each student.
            for (auto &student : students) {
                char status;
                cout << "Is " << student.getName() << " (" << student.getRegistration_No() << ") present, absent, or late? (P/A/L): ";
                cin >> status;
                bool isPresent = (status == 'P' || status == 'p');
                bool isLate = (status == 'L' || status == 'l');

                if (!isPresent) {
                    string reason;
                    cout << "Enter reason for absence: ";
                    cin.ignore();
                    getline(cin, reason);
                    cout << "Reason recorded: " << reason << endl;
                }
                student.markAttendance(date, isPresent);
            }
        }
        //mark attendance of some other classes, that are added.
        cout << "Mark another class? (Y/N): ";
        cin >> more;
    } while (more == 'y' || more == 'Y');
}

//View the attendance of all students.
void Teacher::viewAttendance() {
    string className;
    cout << "Enter class name to view attendance: ";
    cin >> className;
    auto &students = classStudents[className];

    cout << left << setw(20) << "Name" << setw(15) << "Reg No" << "Attendance %"<< "\n";
    cout << string(50, '-') << endl;
    for (auto &student : students) {
        cout << left << setw(20) << student.getName()
             << setw(15) << student.getRegistration_No()
             << fixed << setprecision(2) << student.getAttendancePercentage() << "%\n";
        student.viewAttendance();
        cout << endl;
    }
}

//View each student attendance records.
void Teacher::viewStudentAttendance() {
    string className;
    cout << "Enter class name: ";
    cin >> className;
    string regNo;
    cout << "Enter registration number: ";
    cin >> regNo;
    auto &students = classStudents[className];

    for (auto &student : students) {
        if (student.getRegistration_No() == regNo) {
            student.viewAttendance();
            break;
        }
    }
}

//Edit/ change student name using their registration number.
void Teacher::editStudentName() {
    string className;
    cout << "Enter class name: ";
    cin >> className;
    string regNo;
    cout << "Enter registration number: ";
    cin >> regNo;
    auto &students = classStudents[className];

    for (auto &student : students) {
        if (student.getRegistration_No() == regNo) {
            string newName;
            cout << "Enter new name: ";
            cin >> newName;
            student.setName(newName);
            cout << "Student name updated.\n";
            break;
        }
    }
}

//save attendance data to file per class.
void Teacher::saveData() {
    for (const auto &classEntry : classStudents) {
        string className = classEntry.first;
        const auto &students = classEntry.second;

        // Open class-specific attendance file in append mode
        ofstream out(className + "_attendance.txt", ios::app);
        if (!out) {
            cerr << "Error: Could not open file for class " << className << "\n";
            continue;
        }

        // Group attendance by date for this class
        map<string, vector<pair<Student, bool>>> dateWiseRecords;
        for (const auto &student : students) {
            for (const auto &record : student.getAttendanceRecords()) {
                dateWiseRecords[record.first].emplace_back(student, record.second);
            }
        }

        // Header for this teacher and class
        out << "\n=========================================\n";
        out << "=== CLASS: " << className << " ===\n";
        out << "=== TEACHER: " << teacherName << " ===\n";
        out << "=========================================\n";

        for (const auto &entry : dateWiseRecords) {
            const string &date = entry.first;
            const auto &records = entry.second;

            // Sort students by name
            vector<pair<Student, bool>> sortedRecords = records;
            sort(sortedRecords.begin(), sortedRecords.end(), [](const pair<Student, bool> &a, const pair<Student, bool> &b) {
                return a.first.getName() < b.first.getName();
            });

            out << "\nDate: " << date << "\n";
            out << left << setw(15) << "Name"
                << setw(10) << "RegNo"
                << setw(15) << "Date"
                << "Attendance" << '\n';
            out << string(50, '-') << '\n';

            for (const auto &rec : sortedRecords) {
                out << left << setw(15) << rec.first.getName()
                    << setw(10) << rec.first.getRegistration_No()
                    << setw(15) << date
                    << (rec.second ? "Yes" : "No") << '\n';
            }
        }

        out.close();
    }

    cout << "Attendance saved in class-specific files successfully.\n";
}


//Loads student data from text files.
void Teacher::loadData() {
    vector<string> classesToLoad;

    ifstream classFile("classes.txt");
    if (classFile.is_open()) {
        string className;
        while (getline(classFile, className)) {
            classesToLoad.push_back(className);
        }
        classFile.close();
    }

    for (const string &className : classesToLoad) {
        ifstream in(className + "_data.txt");
        if (!in.is_open()) continue;

        size_t studentCount;
        in >> studentCount;
        in.ignore();

        vector<Student> students;
        for (size_t i = 0; i < studentCount; i++) {
            Student student;
            student.deserialize(in);
            students.push_back(student);
        }

        classStudents[className] = students;
        in.close();
    }
}

//Creates a summary file with student attendance percentages.
void Teacher::exportAttendanceSummary() {
    string className;
    cout << "Enter class name to export summary: ";
    cin >> className;

    auto &students = classStudents[className];
    ofstream out(className + "_attendance_summary.txt");
    out << "Attendance Summary for Class: " << className << "\n";
    out << "=====================================\n";
    for (auto &student : students) {
        out << student.getName() << " (Reg No: " << student.getRegistration_No() << "): "
            << fixed << setprecision(2) << student.getAttendancePercentage() << "% Attendance\n";
    }
    out.close();
    cout << "Attendance summary exported to " << className + "_attendance_summary.txt" << endl;
}

