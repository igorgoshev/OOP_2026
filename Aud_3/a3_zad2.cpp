//
// Created by igor on 3/10/26.
//

#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    //2 in 1 Constructor (Default and with params)
    Date(int day = 0, int month = 0, int year = 0) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    int getDay() {
        return day;
    }

    int getMonth() {
        return month;
    }

    int getYear() {
        return year;
    }

    //Copy constructor
    // Date(const Date &d) {
    //     this->day = d.day;
    //     this->month = d.month;
    //     this->year = d.year;
    // }

    ~Date() {

    }
};


// -1 -> d1 is after d2
//  0 -> equals
//  1 -> d2 is after d1
int compareDates(Date d1, Date d2) {
    if (d1.getYear() > d2.getYear()) {
        return -1;
    } else if (d1.getYear() < d2.getYear()) {
        return 1;
    } else if (d1.getMonth() > d2.getMonth()) {
        return -1;
    } else if (d1.getMonth() < d2.getMonth()) {
        return 1;
    } else if (d1.getDay() > d2.getDay()) {
        return -1;
    } else if (d1.getDay() < d2.getDay()) {
        return 1;
    } else {
        return 0;
    }
}

class Employee {
private:
    char name[20];
    double salary;
    Date dateOfBirth;

public:
    //2 in 1 Constructor
    Employee(char *name = "", double salary = 0, Date dateOfBirth = Date()) {
        strcpy(this->name, name);
        this->salary = salary;
        this->dateOfBirth = dateOfBirth;
    }

    Date getDateOfBirth() {
        return dateOfBirth;
    }

    double getSalary() {
        return salary;
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
        cout << "Date of birth: " << dateOfBirth.getDay() << "." << dateOfBirth.getMonth() << "." << dateOfBirth.getYear() << endl;
    }

    ~Employee() {
    }
};

class Company {
private:
    char name[20];
    Date since;
    Employee employees[100];
    int numOfEmp;

public:
    Company(char name[], Date since, Employee employees[], int numOfEmp) {
        strcpy(this->name, name);
        this->since = since;
        this->numOfEmp = numOfEmp;
        for (int i = 0; i < numOfEmp; i++) {
            this->employees[i] = employees[i];
        }
    }

    Company(char name[], Date since) {
        strcpy(this->name, name);
        this->since = since;
        this->numOfEmp = 0;
    }

    Employee findYoungestEmployee() {
        Employee youngest = employees[0];

        for (int i = 0; i < numOfEmp; i++) {
            if (compareDates(youngest.getDateOfBirth(), employees[i].getDateOfBirth()) == 1) {
                youngest = employees[i];
            }
        }
        return youngest;
    }

    Employee findEmployeeWithBiggestSalary() {
        Employee emp = employees[0];
        for (int i = 0; i< numOfEmp; i++) {
            if (emp.getSalary() < employees[i].getSalary()) {
                emp = employees[i];
            }
        }
        return emp;
    }

    void addEmployee(Employee emp) {
        if (numOfEmp == 100) {
            cout << "Maximum employees reached" << endl;
        } else {
            employees[numOfEmp++] = emp;
            //employees[numOfEmp] = emp;
            //employees++;
        }
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Since: " << since.getDay() << "." << since.getMonth() << "." << since.getYear() << endl;
        cout << "It has " << numOfEmp << "employees" << endl;
        cout << "Youngest Employee:" << endl;
        findYoungestEmployee().print();
        cout << "Richest Employee: " << endl;
        findEmployeeWithBiggestSalary().print();
    }
};

int main() {
    Date d1(1, 2, 1999);
    Date d2(1, 1, 1999);
    Date d3(1, 1, 2006);
    Date d4(1, 1, 2010);
    Date d5(1, 1, 2007);
    Employee emp[4];
    emp[0] = Employee("Igor", 2000, d1);
    emp[1] = Employee("David", 3000, d2);
    emp[2] = Employee("Stefan", 1000, d3);
    Company company("FINKI", d4, emp, 3);
    company.print();

    Employee e("Darko", 2500, d5);

    company.addEmployee(e);
    cout << "==============================" << endl;

    company.print();
    return 0;
}
