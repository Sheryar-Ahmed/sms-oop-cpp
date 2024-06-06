#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Student {
public:
    int rollNumber;
    string name;
    float marks;

    Student() : rollNumber(0), marks(0.0) {}

    Student(int roll, const string& studentName, float studentMarks)
        : rollNumber(roll), name(studentName), marks(studentMarks) {}

    void display() const {
        cout << setw(15) << rollNumber << setw(25) << name << setw(10) << marks << endl;
    }
};

class StudentManagementSystem {
public:
    void addNewStudent();
    void displayAllStudents();
    void searchStudent();
    void updateStudent();
    void deleteStudent();
    void saveToFile();
    void loadFromFile();
    void menu();

private:
    static const int MAX_STUDENTS = 100;
    Student students[MAX_STUDENTS];
    int numStudents = 0;
    const string FILE_NAME = "students.txt";
};

void StudentManagementSystem::addNewStudent() {
    int roll;
    string name;
    float marks;

    cout << "Enter Roll Number: ";
    cin >> roll;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Marks: ";
    cin >> marks;

    students[numStudents] = Student(roll, name, marks);
    numStudents++;

    cout << "Student added successfully!\n";
}

void StudentManagementSystem::displayAllStudents() {
    if (numStudents == 0) {
        cout << "No students to display.\n";
        return;
    }

    cout << setw(15) << "Roll Number" << setw(25) << "Name" << setw(10) << "Marks" << endl;
    for (int i = 0; i < numStudents; ++i) {
        students[i].display();
    }
}

void StudentManagementSystem::searchStudent() {
    if (numStudents == 0) {
        cout << "No students to search.\n";
        return;
    }

    int roll;
    cout << "Enter Roll Number to search: ";
    cin >> roll;

    bool found = false;
    cout << setw(15) << "Roll Number" << setw(25) << "Name" << setw(10) << "Marks" << endl;
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].rollNumber == roll) {
            students[i].display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student not found!\n";
    }
}

void StudentManagementSystem::updateStudent() {
    if (numStudents == 0) {
        cout << "No students to update.\n";
        return;
    }

    int roll;
    cout << "Enter Roll Number to update: ";
    cin >> roll;

    bool found = false;
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].rollNumber == roll) {
            cout << "Enter new Roll Number: ";
            cin >> students[i].rollNumber;
            cin.ignore();
            cout << "Enter new Name: ";
            getline(cin, students[i].name);
            cout << "Enter new Marks: ";
            cin >> students[i].marks;

            cout << "Student updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student not found!\n";
    }
}

void StudentManagementSystem::deleteStudent() {
    if (numStudents == 0) {
        cout << "No students to delete.\n";
        return;
    }

    int roll;
    cout << "Enter Roll Number to delete: ";
    cin >> roll;

    bool found = false;
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].rollNumber == roll) {
            found = true;
            for (int j = i; j < numStudents - 1; ++j) {
                students[j] = students[j + 1];
            }
            numStudents--;

            cout << "Student deleted successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "Student not found!\n";
    }
}

void StudentManagementSystem::saveToFile() {
    ofstream outFile(FILE_NAME);
    if (!outFile) {
        cerr << "Error opening file!\n";
        return;
    }

    outFile << numStudents << endl;
    for (int i = 0; i < numStudents; ++i) {
        outFile << students[i].rollNumber << " " << students[i].name << " " << students[i].marks << endl;
    }

    outFile.close();
}

void StudentManagementSystem::loadFromFile() {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cerr << "Error opening file!\n";
        return;
    }

    inFile >> numStudents;
    for (int i = 0; i < numStudents; ++i) {
        inFile >> students[i].rollNumber >> students[i].name >> students[i].marks;
    }

    inFile.close();
}

void StudentManagementSystem::menu() {
    int choice;

    while (true) {
        cout << "\nStudent Management System\n";
        cout << "1. Add New Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                saveToFile();
                cout << "Exiting the program.\n";
                exit(0);
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    }
}

int main() {
    StudentManagementSystem system;
    system.loadFromFile();
    system.menu();

    return 0;
}

