//
// Created by igor on 3/3/26.
//

#include <iostream>
using namespace std;

class Cuboid {
private:
    int a;
    int b;
    int c;

public:
    //default Constructor
    Cuboid() {
        cout << "This is default Constructor." << endl;
    }

    // Cuboid(int aa, int bb, int cc) {
    //     cout << "This is constructor with params." << endl;
    //     a = aa;
    //     b = bb;
    //     c = cc;
    // }

    Cuboid(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    int area() {
        return 2*((a*b) + (a*c) + (b*c));
    }

    int volume() {
        return a*b*c;
    }

    //deconstructor
    ~Cuboid() {
        cout << "Deconstructing" << endl;
    }

};

int main() {
    Cuboid c(2, 3, 5);
    cout << "The area is: "<< c.area() << endl;
    cout << "The volume is: " << c.volume() << endl;

    return 0;
}