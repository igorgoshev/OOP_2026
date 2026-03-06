//
// Created by igor on 2/24/26.
//

#include <iostream>
#include <cstring>
using namespace std;

struct Student {
    char name[50];
    char lastname[50];
    int index;
    int total_points;

    void print() {
        name[0] = toupper(name[0]);
        lastname[0] = toupper(lastname[0]);
        cout << name << " " << lastname << " " << index << " " << total_points << endl;
    }
};

void sort(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            if (students[j].total_points < students[j+1].total_points) {
                Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
}

void read_student(Student &student) {
    int a, b, c, d;
    cin >> student.name;
    cin >> student.lastname;
    cin >> student.index;
    cin >> a >> b >> c >> d;
    student.total_points = a + b + c + d;
}

int main() {
    int n;
    cin >> n;
    Student students[100];

    for (int i = 0; i < n; i++) {
        read_student(students[i]);
    }

    sort(students, n);

    for (int i = 0; i < n; i++) {
        students[i].print();
    }

    return 0;
}
