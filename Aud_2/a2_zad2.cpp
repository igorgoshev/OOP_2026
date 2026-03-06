//
// Created by igor on 3/3/26.
//

#include <math.h>
#include <iostream>

using namespace std;

class Triangle {
private:
    int a;
    int b;
    int c;

public:
    Triangle() {}

    Triangle(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    int perimeter() {
        return a + b + c;
    }

    float area () {
        float s = (a+b+c)/2.0;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }

    ~Triangle(){}
};

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    Triangle t(a, b, c);

    cout << "The triangle has the perimeter: " << t.perimeter() << endl;
    cout << "The triangle has the area: " << t.area() << endl;

    return 0;
}
