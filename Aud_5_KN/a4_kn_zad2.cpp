//
// Created by igor on 3/25/26.
//

#include <cstring>
#include <iostream>
using namespace std;

class Student {
    char name[50];
    int id;
    float gpa;
    static int real_index;
    static int num_students;

    static float total_average;

public:
    Student(char name[], float gpa) {
        num_students++;
        total_average+=gpa;
        strcpy(this->name, name);
        // strcpy(this->id, id);
        this->gpa = gpa;
        id = real_index++;
    }

    static int get_num_students() {
        return num_students;
    }

    static float get_total_average() {
        return total_average;
    }

    ~Student(){}

};

int Student::num_students = 0;
float Student::total_average = 0;
int Student::real_index = 230001;

int main() {
    cout << Student::get_num_students() << endl;
    Student s("Igor",  6.4);
    cout << Student::get_num_students();

    return 0;
}
