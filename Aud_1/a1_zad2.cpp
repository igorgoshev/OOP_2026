//
// Created by igor on 2/24/26.
//

#include <iostream>
using namespace std;

struct Date {
    int day, month, year;

    int compare(Date other) {
        if (year > other.year) {
            return 1;
        } else if (year < other.year) {
            return -1;
        } else {
            if (month > other.month) {
                return 1;
            } else if (month < other.month) {
                return -1;
            } else {
                if (day > other.day) {
                    return 1;
                } else if (day < other.day) {
                    return -1;
                } else {
                    return 0;
                }
            }
        }
    }

    int difference_days(Date other) {
        int this_days = day + (month*30) + (year*365);
        int other_days = other.day + (other.month*30) + (other.year*365);
        return this_days - other_days;
    }

};

void read_date(Date &date) {
    //0 -> January,
    //1 -> February,
    // ...
    //11 -> December
    cin>>date.day>>date.month>>date.year;
}

void print_date(Date date) {
    cout << date.day <<"."<< date.month <<"." << date.year << endl;
}

int main() {

    Date date1, date2;
    read_date(date1);
    read_date(date2);

    int res = date1.compare(date2);

    if (res < 0) {
         cout << date2.difference_days(date1) << endl;
    } else if (res > 0) {
        cout << date1.difference_days(date2) << endl;
    } else {
        cout << date1.difference_days(date2) << endl;
    }
    return 0;
}