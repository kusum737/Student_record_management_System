#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
    int rollNo;
    char name[50];
    float marks;

public:
    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << setw(10) << rollNo
             << setw(20) << name
             << setw(10) << marks << endl;
    }

    int getRollNo() const {
        return rollNo;
    }
};

// Function declarations
void addStudent();
void displayAll();
void searchStudent(int);
void deleteStudent(int);

int main() {
    int choice;
    do {
            ifdef _WIN32
            system("cls");
            else
                system("clear");

            #endif // WIN32
        cout << "\n--- Student Record Management ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int roll;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                cout << "Enter Roll No to search: ";
                cin >> roll;
                searchStudent(roll);
                break;
            case 4:
                cout << "Enter Roll No to delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}

// Function Definitions

void addStudent() {
    Student s;
    ofstream outFile("students.dat", ios::binary | ios::app);
    s.input();
    outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    outFile.close();
    cout << "Student record added successfully.\n";
}

void displayAll() {
    Student s;
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!\n";
        return;
    }
    cout << "\n--- All Student Records ---\n";
    cout << setw(10) << "Roll No" << setw(20) << "Name" << setw(10) << "Marks\n";
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        s.display();
    }
    inFile.close();
}

void searchStudent(int roll) {
    Student s;
    bool found = false;
    ifstream inFile("students.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.getRollNo() == roll) {
            cout << "\nRecord Found:\n";
            cout << setw(10) << "Roll No" << setw(20) << "Name" << setw(10) << "Marks\n";
            s.display();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found)
        cout << "Record not found.\n";
}

void deleteStudent(int roll) {
    Student s;
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.getRollNo() != roll) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}
