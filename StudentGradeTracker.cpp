#include <iostream>   // Include iostream for input/output
#include <vector>     // Include vector for dynamic array management
#include <algorithm>  // Include algorithm for sorting
#include <iomanip>    // Include iomanip for formatting output

using namespace std;

// Define a structure to store student information and grades
struct Student {
    string name;
    int id;
    double assignmentGrade;
    double examGrade;
    double overallGrade;
};

// Function prototypes
void inputStudentData(vector<Student>& students);
void calculateOverallGrades(vector<Student>& students);
void displayGrades(const vector<Student>& students);
void calculateStatistics(const vector<Student>& students);
void displayTopStudents(const vector<Student>& students);

int main() {
    vector<Student> students;  // Vector to store students' data

    // Input student data
    inputStudentData(students);

    // Calculate overall grades for all students
    calculateOverallGrades(students);

    // Display all students' grades
    displayGrades(students);

    // Calculate and display class statistics
    calculateStatistics(students);

    // Display top 3 students
    displayTopStudents(students);

    return 0;
}

// Function to input student data
void inputStudentData(vector<Student>& students) {
    int numberOfStudents;
    cout << "Enter the number of students: ";
    cin >> numberOfStudents;

    for (int i = 0; i < numberOfStudents; ++i) {
        Student student;
        cout << "\nEnter data for student " << (i + 1) << ":\n";
        cout << "Name: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, student.name);
        cout << "ID: ";
        cin >> student.id;
        cout << "Assignment Grade: ";
        cin >> student.assignmentGrade;
        cout << "Exam Grade: ";
        cin >> student.examGrade;

        students.push_back(student); // Add student to the list
    }
}

// Function to calculate overall grades
void calculateOverallGrades(vector<Student>& students) {
    for (auto& student : students) {
        student.overallGrade = (student.assignmentGrade * 0.4) + (student.examGrade * 0.6);
    }
}

// Function to display students' grades
void displayGrades(const vector<Student>& students) {
    cout << "\nStudent Grades:\n";
    cout << left << setw(15) << "Name" << setw(10) << "ID" 
         << setw(20) << "Assignment Grade" << setw(15) << "Exam Grade" 
         << setw(15) << "Overall Grade" << endl;
    cout << string(75, '-') << endl;

    for (const auto& student : students) {
        cout << left << setw(15) << student.name << setw(10) << student.id 
             << setw(20) << student.assignmentGrade << setw(15) << student.examGrade 
             << setw(15) << student.overallGrade << endl;
    }
}

// Function to calculate and display class statistics
void calculateStatistics(const vector<Student>& students) {
    double sumOverall = 0.0;
    double sumAssignment = 0.0;
    double sumExam = 0.0;
    double maxOverall = students.front().overallGrade;
    double minOverall = students.front().overallGrade;

    for (const auto& student : students) {
        sumOverall += student.overallGrade;
        sumAssignment += student.assignmentGrade;
        sumExam += student.examGrade;
        if (student.overallGrade > maxOverall) maxOverall = student.overallGrade;
        if (student.overallGrade < minOverall) minOverall = student.overallGrade;
    }

    double averageOverall = sumOverall / students.size();
    double averageAssignment = sumAssignment / students.size();
    double averageExam = sumExam / students.size();

    cout << "\nClass Statistics:\n";
    cout << "Average Assignment Grade: " << averageAssignment << endl;
    cout << "Average Exam Grade: " << averageExam << endl;
    cout << "Average Overall Grade: " << averageOverall << endl;
    cout << "Highest Overall Grade: " << maxOverall << endl;
    cout << "Lowest Overall Grade: " << minOverall << endl;
}

// Function to display top 3 students
void displayTopStudents(const vector<Student>& students) {
    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end(), [](const Student& a, const Student& b) {
        return a.overallGrade > b.overallGrade; // Sort in descending order of overall grade
    });

    cout << "\nTop 3 Students:\n";
    for (int i = 0; i < 3 && i < sortedStudents.size(); ++i) {
        cout << (i + 1) << ". " << sortedStudents[i].name 
             << " (ID: " << sortedStudents[i].id 
             << ", Overall Grade: " << sortedStudents[i].overallGrade << ")\n";
    }
}