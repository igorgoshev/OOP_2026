//
// Created by igor on 3/25/26.
//

#include <cstring>
#include <iostream>
using namespace std;

class Student {
    char index[6];
    char *name;
    float gpa;
    int yearStudies;

public:
    Student(char index[], char *name, float gpa, int year_studies) {
        strcpy(this->index, index);
        this->name = new char(strlen(name) + 1);
        strcpy(this->name, name);
        this->gpa = gpa;
        this->yearStudies = year_studies;
    }

    Student() {
    }

    Student(const Student &s) {
        strcpy(this->index, s.index);
        this->name = new char(strlen(s.name) + 1);
        this->gpa = s.gpa;
        this->yearStudies = s.yearStudies;
    }

    // Student &operator=(Student &s) {
    //     if (this != &s) {
    //         delete[] this->name;
    //         this->name = new char[strlen(s.name) + 1];
    //         strcpy(this->name, s.name);
    //         this->gpa = s.gpa;
    //         strcpy(this->index, s.index);
    //         this->yearStudies = s.yearStudies;
    //     }
    //     return *this;
    // }

    //postfix a++
    Student operator++(int) {
        Student s(*this);
        this->yearStudies++;
        return s;
    }

    //prefix ++a
    Student &operator++() {
        this->yearStudies++;
        return *this;
    }

    ~Student() {
        delete []name;
    }
};

class Group {
    Student *students;
    int size;

public:
    Group() {
        this->size = 0;
        students = new Student[size];
    }

    Group &operator+=(Student student) {
        Student *temp = new Student[size + 1];
        for (int i = 0; i < size; ++i) {
            temp[i] = this->students[i];
        }
        temp[size] = student;
        size++;
        delete[] students;
        students = temp;

        return *this;
    }

    ~Group() {
        delete []students;
    }
};

int main() {
    Student s1("123", "igor", 123, 1);
    Student s2("124", "david", 123, 2);
    Student s3("125", "stefan", 123, 3);
    Student s4("126", "valtko", 123, 4);

    Group g;
    g += s1;
    g += s2;
    g += s3;
    g += s4;

    return 0;
}
