#include "teacher.h"
#include <iostream>
using namespace std;

int main() {
    Teacher teacher;

    while (true) {
        teacher.login();

        int choice;
        do {
            cout << "\n========= Teacher Menu =========\n";
            cout << "1. Add Students\n";
            cout << "2. Mark Attendance\n";
            cout << "3. View All Attendance\n";
            cout << "4. View Specific Student Attendance\n";
            cout << "5. Edit Student Name\n";
            cout << "6. Logout\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: teacher.addStudents(); break;
                case 2: teacher.markAttendanceForAll(); break;
                case 3: teacher.viewAttendance(); break;
                case 4: teacher.viewStudentAttendance(); break;
                case 5: teacher.editStudentName(); break;
                case 6: cout << "\nLogging out...\n"; break;
                case 7: cout << "Exiting...\n"; return 0;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 6);
    }
    return 0;
}