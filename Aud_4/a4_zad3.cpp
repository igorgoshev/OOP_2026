//
// Created by igor on 3/17/26.
//

#include <iostream>
#include <cstring>

using namespace std;

class Student {
private:
    char name[50];
    int id;
    float gpa;
    static int ID;
    static int NUM_STUDENTS;
    static float AVERAGE;

public:
    Student(char name[], float gpa) {
        strcpy(this->name, name);
        this->gpa = gpa;

        this->id = ID++;
        NUM_STUDENTS++;
        AVERAGE+= gpa;
    }

    Student() {
    }

    static double total_average() {
        return AVERAGE/NUM_STUDENTS;
    }

    static int total_students() {
        return NUM_STUDENTS;
    }

    ~Student() {
    }

    void print() {
        cout <<"The student " << this->name << " with ID: " << this->id << " has an average grade of " << this->gpa << endl;
    }
};

int Student::NUM_STUDENTS = 0;
int Student::ID = 230001;
float Student::AVERAGE = 0.0;

int main() {
    int n;
    cin >> n;
    Student students[n];
    char name[50];
    float gpa;
    for (int i = 0; i < n; i++) {
        cin >> name >> gpa;
        students[i] = Student(name, gpa);
    }

    for (int i = 0; i < n; i++) {
        students[i].print();
    }

    // Only if the static field is public
    // cout << "Total students: " << Student::NUM_STUDENTS << endl;

    cout << "Total students: " << Student::total_students() << endl;
    cout << "Total average: " << Student::total_average() << endl;

    return 0;
}
