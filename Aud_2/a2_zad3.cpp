//
// Created by igor on 3/3/26.
//

#include <iostream>
#include <cstring>
using namespace std;


enum Position {
    employee,
    director,
    boss
};

class Employee {
private:
    char name[50];
    double salary;
    Position position;

    //this function is private,
    //only access from inside class
    char* getPositionName(Position position) {
        if (position == 0) {
            return "employee";
        }
        else if (position == 1) {
            return "director";
        } else {
            return "boss";
        }
    }

public:
    Employee() {
        // cout << "default" << endl;
    }

    Employee(char name[], double salary, Position position) {
        strcpy(this->name, name);
        this->salary = salary;
        this->position = position;
    }

    ~Employee() {
        // cout << "Deconstructing" << endl;
    }

    double getSalary() {
        return salary;
    }

    void print() {
        cout << "Name: " << this->name << endl;
        cout << "Salary: " << this->salary << endl;
        cout << "Position: " << getPositionName(this->position) << endl;
    }
};

void sort(Employee e[], int n) {
    for (int i = 0; i< n; i++) {
        for (int j = 0; j < n-1; j++) {
            if (e[j].getSalary() < e[j+1].getSalary()) {
                Employee temp = e[j];
                e[j] = e[j+1];
                e[j+1] = temp;
            }
        }
    }
}

int main() {
    char name[50];
    double salary;
    int position;
    int n;
    cin >> n;
    cin.ignore();
    Employee e[n];
    for (int i = 0; i < n; i++) {
        cin.getline(name, 50);
        cin >> salary;
        cin >> position;
        cin.ignore();
        e[i] = Employee(name, salary, (Position) position);
    }

    sort(e, n);

    for ( int i = 0; i < n; i++) {
        e[i].print();
    }

    return 0;
}
