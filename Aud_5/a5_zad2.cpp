//
// Created by igor on 3/24/26.
//

#include <cstring>
#include <iostream>

using namespace std;

class Student {
    char index[6];
    char *name;
    int yearStudies;
    float gpa;

public:
    Student(char index[] = "", char name[] = "", int yearStudies = 0, float gpa = 0) {
        strcpy(this->index, index);
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->yearStudies = yearStudies;
        this->gpa = gpa;
    }

    //called when Student s2 = s1;
    Student(const Student &s) {
        strcpy(this->index, s.index);
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name, s.name);
        this->yearStudies = s.yearStudies;
        this->gpa = s.gpa;
    }

    //called when s2 = s1
    Student &operator=(Student &s) {
        if (this != &s) {
            strcpy(this->index, s.index);
            delete []name;
            this->name = new char[strlen(s.name) + 1];
            strcpy(this->name, s.name);
            this->yearStudies = s.yearStudies;
            this->gpa = s.gpa;
        }
        return *this;
    }

    //prefix
    Student &operator++() {
        yearStudies++;
        return *this;
    }

    //postfix
    Student operator++(int a) {
        Student s(*this);
        yearStudies++;
        return s;
    }

    bool operator>(const Student &s) const {
        return this->gpa > s.gpa;
    }

    char *getIndex() {
        return index;
    }

    float getGPA() {
        return gpa;
    }

    friend ostream &operator<<(ostream &out, Student &s);

    ~Student() {
        //free memory
        delete []name;
    }
};

ostream &operator<<(ostream &out, Student &s) {
    out << s.name << " with ID: " << s.index << " has an average gpa of " << s.gpa << " and is " << s.yearStudies <<
            " year of studies." << endl;
    return out;
}

class Group {
    Student *students;
    int size;

public:
    Group() {
        students = new Student[0];
        this->size = 0;
    }

    Group(const Group &g) {
        students = new Student[g.size];
        for (int i = 0; i < g.size; i++) {
            students[i] = g.students[i];
        }
        this->size = g.size;
    }

    Group &operator+=(Student &student) {
        Student *temp = new Student[size + 1];
        for (int i = 0; i < size; i++) {
            temp[i] = students[i];
        }
        temp[size++] = student;
        delete []students;
        students = temp;
        return *this;
    }

    //postfix
    Group operator++(int) {
        Group g(*this);
        for (int i = 0; i < size; ++i) {
            students[i]++;
        }
        return g;
    }

    //prefix
    Group &operator++() {
        for (int i = 0; i < size; ++i) {
            students[i]++;
        }
        return *this;
    }

    Student &operator[](char *index) {
        for (int i = 0; i < size; ++i) {
            if (strcmp(students[i].getIndex(), index) == 0) {
                return students[i];
            }
        }
    }

    void awards() {
        cout << "Students with an average of 10.00:" << endl;
        for (int i = 0; i < this->size; ++i) {
            if (students[i].getGPA() == 10.00) {
                cout << students[i];
            }
        }
    }

    void highestAverage() {
        Student max = students[0];
        for (int i = 0; i < size; ++i) {
            if (max.getGPA() < students[i].getGPA()) {
                max = students[i];
            }
        }
        cout << "The highest average student is: " << endl;
        cout << max << endl;
    }

    friend ostream &operator<<(ostream &out, Group &g);


    ~Group() {
        //free memory
        delete []students;
    }
};

ostream &operator<<(ostream &out, Group &g) {
    out << "The group has " << g.size << " students." << endl;
    for (int i = 0; i < g.size; ++i) {
        out << i+1 << ". " << g.students[i];
    }
    return out;
}

int main() {
    Student s1("111111", "Petar Petreski", 1, 10.00);
    Student s2("222222", "Nikola Nikolov", 2, 9.54);
    Student s3("333333", "David Davidovski", 3, 10.00);
    Student s4("444444", "Jovan Jovanovski", 4, 6.47);
    Student changeStudent("999999", "Stefan Stefanov", 3, 8.7);
    Group g;

    if (s1 > s4) {
        s4++;
    }

    g+=s1;
    g+=s2;
    g+=s3;
    g+=s4;
    cout << g <<endl;

    cout << "==== Changing value ====" << endl;
    g["111111"] = changeStudent;
    cout << endl;

    cout << g << endl;

    cout << "==== Increment Group ====" << endl;
    g++;
    cout << endl;
    cout << g << endl;

    g.awards();
    g.highestAverage();

    return 0;
}
