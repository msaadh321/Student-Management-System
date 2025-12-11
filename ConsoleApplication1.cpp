#include <iostream>
#include <fstream>
using namespace std;
// global arrays
const int MAX_STUDENTS = 50;
const int MAX_DAYS = 30;
int rollNumbers[MAX_STUDENTS];
string names[MAX_STUDENTS];
int marks[MAX_STUDENTS][3];
float averages[MAX_STUDENTS];
char grades[MAX_STUDENTS];
float gpa[MAX_STUDENTS];
bool attendance[MAX_STUDENTS][MAX_DAYS];
bool dayMarked[MAX_DAYS];
int studentCount = 0;
// login system
bool teacherLogin() {
    string user, pass;
    cout << "LOGIN PAGE" << endl;
    cout << "Enter Username: ";
    cin >> user;
    cout << "Enter Password: ";
    cin >> pass;
    if (user == "teacher" && pass == "0000") {
        cout << "Login Successful! Access Granted." << endl;
        return true;
    }
    cout << "Invalid Credentials! Access Denied." << endl;
    return false;
}
// calculate grade
void calculateGrade(int index) {
    averages[index] = (marks[index][0] + marks[index][1] + marks[index][2]) / 3.0;
    if (averages[index] >= 90) grades[index] = 'A';
    else if (averages[index] >= 80) grades[index] = 'B';
    else if (averages[index] >= 70) grades[index] = 'C';
    else if (averages[index] >= 60) grades[index] = 'D';
    else grades[index] = 'F';
}
// calculate gpa
void calculateGPA(int index) {
    if (grades[index] == 'A') gpa[index] = 4.0;
    else if (grades[index] == 'B') gpa[index] = 3.0;
    else if (grades[index] == 'C') gpa[index] = 2.0;
    else if (grades[index] == 'D') gpa[index] = 1.0;
    else gpa[index] = 0.0;
}
// gpa summary
void gpaSummary() {
    cout << " GPA SUMMARY " << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << names[i] << " (" << rollNumbers[i] << ") = GPA: " << gpa[i] << "\n";
    }
}
// add a student
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Maximum limit reached!" << endl;
        return;
    }
    cout << "Enter Roll Number: ";
    cin >> rollNumbers[studentCount];
    cout << "Enter Name (single word): ";
    cin >> names[studentCount];
    cout << "Enter Marks of 3 Subjects: ";
    cin >> marks[studentCount][0] >> marks[studentCount][1] >> marks[studentCount][2];
    calculateGrade(studentCount);
    calculateGPA(studentCount);
    studentCount++;
    cout << "Student Added Successfully!" << endl;
}
// display all students
void displayAll() {
    if (studentCount == 0) {
        cout << "No Students Available!" << endl;
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        cout << "\nRoll: " << rollNumbers[i]
            << ", Name: " << names[i]
            << ", Avg: " << averages[i]
            << ", GPA: " << gpa[i]
            << ", Grade: " << grades[i] << endl;
    }
}
// search a student
void searchStudent() {
    int roll;
    cout << "Enter Roll Number to Search: ";
    cin >> roll;
    for (int i = 0; i < studentCount; i++) {
        if (rollNumbers[i] == roll) {
            cout << "Student Found!" << endl;
            cout << "Name: " << names[i] << "\nAverage: " << averages[i] << "\nGrade: " << grades[i] << endl;
            return;
        }
    }
    cout << "Student Not Found!" << endl;
}
// update marks
void updateMarks() {
    int roll;
    cout << "Enter Roll Number to Update Marks: ";
    cin >> roll;
    for (int i = 0; i < studentCount; i++) {
        if (rollNumbers[i] == roll) {
            cout << "Enter New Marks of 3 Subjects: ";
            cin >> marks[i][0] >> marks[i][1] >> marks[i][2];
            calculateGrade(i);
            calculateGPA(i);
            cout << "Marks Updated Successfully!" << endl;
            return;
        }
    }
    cout << "Student Not Found!" << endl;
}
// delete students
void deleteStudent() {
    int roll;
    cout << "Enter Roll Number to Delete: ";
    cin >> roll;
    for (int i = 0; i < studentCount; i++) {
        if (rollNumbers[i] == roll) {
            for (int j = i; j < studentCount - 1; j++) {
                rollNumbers[j] = rollNumbers[j + 1];
                names[j] = names[j + 1];
                averages[j] = averages[j + 1];
                grades[j] = grades[j + 1];
                gpa[j] = gpa[j + 1];
                for (int k = 0; k < 3; k++)
                    marks[j][k] = marks[j + 1][k];
                for (int d = 0; d < MAX_DAYS; d++)
                    attendance[j][d] = attendance[j + 1][d];
            }
            studentCount--;
            cout << "Student Deleted!" << endl;
            return;
        }
    }
    cout << "Student Not Found!" << endl;
}
// top 3 students
void top3() {
    if (studentCount == 0) {
        cout << "No Students Available!" << endl;
        return;
    }
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (averages[j] > averages[i]) {
                swap(rollNumbers[i], rollNumbers[j]);
                swap(names[i], names[j]);
                swap(averages[i], averages[j]);
                swap(grades[i], grades[j]);
                swap(gpa[i], gpa[j]);
                for (int k = 0; k < 3; k++)
                    swap(marks[i][k], marks[j][k]);
            }
        }
    }
    cout << "\nTop 3 Students:" << endl;
    for (int i = 0; i < min(3, studentCount); i++) {
        cout << names[i] << " - Avg: " << averages[i] << endl;
    }
}
// grade summary
void gradeSummary() {
    int A = 0, B = 0, C = 0, D = 0, F = 0;
    for (int i = 0; i < studentCount; i++) {
        if (grades[i] == 'A') A++;
        else if (grades[i] == 'B') B++;
        else if (grades[i] == 'C') C++;
        else if (grades[i] == 'D') D++;
        else F++;
    }
    cout << " Grade Summary " << endl;
    cout << "A: " << A << "\nB: " << B << "\nC: " << C << "\nD: " << D << "\nF: " << F << endl;
}
// mark attendance
void markAttendance() {
    int day;
    cout << "Enter day number (1-30): ";
    cin >> day;
    if (day < 1 || day > 30) {
        cout << "Invalid Day!" << endl;
        return;
    }
    day--;
    if (dayMarked[day]) {
        cout << "Attendance already marked for this day!" << endl;
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        char ch;
        cout << "Is " << names[i] << " Present? (P/A): ";
        cin >> ch;
        attendance[i][day] = (ch == 'P' || ch == 'p');
    }
    dayMarked[day] = true;
    cout << "Attendance Marked Successfully!" << endl;
}
// show attendance
void showAttendance() {
    int roll;
    cout << "Enter Roll Number: ";
    cin >> roll;
    for (int i = 0; i < studentCount; i++) {
        if (rollNumbers[i] == roll) {
            cout << "\nAttendance Record for " << names[i] << ":" << endl;
            for (int d = 0; d < MAX_DAYS; d++) {
                if (dayMarked[d])
                    cout << "Day " << (d + 1) << ": " << (attendance[i][d] ? "P" : "A") << endl;
            }
            return;
        }
    }
    cout << "Student Not Found!" << endl;
}
// attendance report
void attendanceReport() {
    cout << " Attendance Percentages " << endl;
    for (int i = 0; i < studentCount; i++) {
        int present = 0, total = 0;
        for (int d = 0; d < MAX_DAYS; d++) {
            if (dayMarked[d]) {
                total++;
                if (attendance[i][d]) present++;
            }
        }
        float percentage = (total == 0 ? 0 : (present * 100.0) / total);
        cout << names[i] << ": " << percentage << "%" << endl;
    }
}
// export file
void exportFile() {
    ofstream file("report.txt");
    if (!file) {
        cout << "Error creating file!\n";
        return;
    }
    file << "Student Record Report\n\n";
    for (int i = 0; i < studentCount; i++) {
        file << "Roll: " << rollNumbers[i]
            << ", Name: " << names[i]
            << ", Avg: " << averages[i]
            << ", Grade: " << grades[i] << "\n";
    }
    file.close();
    cout << "Data exported to report.txt!\n";
}
// main menu
int main() {
    for (int i = 0; i < MAX_DAYS; i++)
        dayMarked[i] = false;
    cout << "\nSTUDENT MANAGEMENT SYSTEM \n";
    if (!teacherLogin()) {
        return 0;
    }
    int choice;
    do {
        cout << "\nMAIN MENU " << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Marks" << endl;
        cout << "5. Delete Student" << endl;
        cout << "6. Top 3 Students" << endl;
        cout << "7. Grade Summary" << endl;
        cout << "8. Mark Attendance" << endl;
        cout << "9. Show Attendance" << endl;
        cout << "10.Attendance Report" << endl;
        cout << "11.Export to File" << endl;
        cout << "12.GPA Summary" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayAll(); break;
        case 3: searchStudent(); break;
        case 4: updateMarks(); break;
        case 5: deleteStudent(); break;
        case 6: top3(); break;
        case 7: gradeSummary(); break;
        case 8: markAttendance(); break;
        case 9: showAttendance(); break;
        case 10: attendanceReport(); break;
        case 11: exportFile(); break;
        case 12: gpaSummary(); break;
        case 0: cout << "Exiting Program..." << endl; break;
        default: cout << "Invalid Choice!" << endl;
        }

    } while (choice != 0);
}