#ifndef TEACHER_H
#define TEACHER_H

#include "student.h"
#include <vector>
#include <map>
using namespace std;

class Teacher {
private:
    string teacherName;
    map<string, vector<Student>> classStudents;

public:
    void login();
    void addStudents();
    void markAttendanceForAll();
    void viewAttendance();
    void viewStudentAttendance();
    void editStudentName();
    void saveData();
    void loadData();
    void exportAttendanceSummary();
};

#endif
