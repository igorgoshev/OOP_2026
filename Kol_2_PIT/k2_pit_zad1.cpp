//
// Created by igor on 5/19/26.
//
#include <chrono>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class StudentFailedException {
    string index;

public:
    StudentFailedException(string index) {
        this->index = index;
    }

    void print() {
        cout << "Student with id " << index << " failed the course" << endl;
    }
};

class Student {
    string index;
    string name;
    string lastName;
    int points;

public:
    Student(string index, string name, string lastName, int points) {
        this->index = index;
        this->name = name;
        this->lastName = lastName;
        this->points = points;
    }

    Student() {
    }




    friend ostream &operator<<(ostream &out, Student s) {
        out << s.index << " " << s.name + " " + s.lastName << " " << s.points << " Grade: " << s.grade() << endl;

        return out;
    }

    int grade() {
        // 100 = > 10
        int g = points / 10;
        if (g < 5) {
            return 5;
        }
        if (g == 10) {
            return 10;
        }
        return g + 1;
    }

    string getIndex() {
        return index;
    }
};

class Results {
    Student *students;
    int numStudents;

public:
    Results() {
        students = nullptr;
        numStudents = 0;
    }

    Results(const Results &s) {
        students = new Student[s.numStudents];
        numStudents = s.numStudents;
        for (int i = 0; i < numStudents; ++i) {
            students[i] = s.students[i];
        }
    }

    Results &operator+=(Student s) {
        if (s.grade() == 5) {
            throw StudentFailedException(s.getIndex());
        }
        Student *tmp = new Student[numStudents + 1];
        for (int i = 0; i < numStudents; ++i) {
            tmp[i] = students[i];
        }

        delete[]students;
        tmp[numStudents] = s;
        numStudents++;
        students = tmp;

        return *this;
    }

    friend ostream &operator<<(ostream &out, Results &r) {
        if (r.numStudents == 0) {
            out << "None" <<endl;
        }

        for (int i = 0; i < r.numStudents; ++i) {
            out << r.students[i];
        }

        return out;
    }

    Results withGrade(int grade) {
        Results studentsWithGrade;
        for (int i = 0; i < numStudents; ++i) {
            if (students[i].grade() == grade) {
                studentsWithGrade += students[i];
            }
        }
        return studentsWithGrade;
    }

    ~Results() {
        delete [] students;
    }
};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

Results readFile() {
    Results r;
    ifstream ifile("input.txt");

    string name, lastName, index;
    int points;
    while (ifile >> index >> name >> lastName >> points) {
        Student s(index, name, lastName, points);
        try {
            r+=s;
        } catch (StudentFailedException e) {
            e.print();
        }

    }

    ifile.close();
    return r;
}

void outputFile(Results r, int grade) {
    ofstream output1file("output1.txt");
    ofstream output2file("output2.txt");

    output1file << r;
    Results filtered = r.withGrade(grade);
    output2file << filtered;
}

int main() {
    wtf();

    Results results = readFile();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    int grade;
    cin >> grade;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT


    outputFile(results, grade);




    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");


    return 0;
}
