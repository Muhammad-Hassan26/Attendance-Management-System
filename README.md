# C++ Attendance Management System 

# 📦 Project Overview
This project is a console-based Attendance Management System built with Object-Oriented Programming in C++. It allows teachers to manage classes and student attendance effectively through a secure login system.

# ✅ Features
**Teachers can**
- Log in securely
- Create and manage multiple classes
- Add students to each class
- Mark attendance (Present, Absent, Late) with optional reasons
- View attendance by date, student, or class
- Export attendance summaries

 **Students can**
- Log in using their registration number
- View their attendance record and percentage

# 🧱 Project Structure
The system is organized into modular files:
- **main.cpp** – Contains the main logic and teacher login
- **student.h / student.cpp** – Handles student class structure and behavior
- **teacher.h / teacher.cpp** – Manages teacher login and attendance operations
- **teachers.txt** – Stores teacher credentials
- **classes.txt** – Tracks created classes and their associated teachers
- **<class>_data.txt** – Stores data for each class including student info
- **<class>_attendance.txt** – Detailed attendance logs saved by date
- **<class>_attendance_summary.txt** – Contains percentage summary for all students
- **README.md** – Project documentation (this file)


# 🧑‍🏫 Class Descriptions
 **Student Class**
- Handles student information such as name, registration number, attendance records, and percentage calculations. It supports file reading/writing for data persistence.
  
 **Teacher Class**
- Handles teacher authentication, student addition, attendance marking, data saving, and summary exporting. It maintains separate files per class.


# 🧪 Compilation and Execution
 To compile the project:
- g++ main.cpp student.cpp teacher.cpp -o attendance

 To run the program:
- ./attendance.exe

# 🔑 Credentials Format
 Before running, make sure the teachers.txt file contains teacher credentials in this format:  teacherID password
 
 **Example**
 hassan12 hassi24

# 🗓️ Attendance Record Format
 - Each class will have its own attendance file (e.g., CS101_attendance.txt). 
 - Attendance is saved by date along with student name, registration number, and status (Yes/No/Late).

# 📤 Export Summary Format
The system exports attendance percentage summaries into files like CS101_attendance_summary.txt.

# ⚠️ Important Notes
- Registration numbers follow the format QAU-<id> (e.g., QAU-0410)
- Attendance records include optional reasons for absence or lateness
- Every entry is stored with a specific date for accurate tracking
- Class names must not contain spaces or special characters

-**This project demonstrates file handling, object-oriented design, and modular programming in C++ — ideal for educational use and future enhancements like GUI or database support.**
