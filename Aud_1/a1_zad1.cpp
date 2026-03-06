//
// Created by igor on 2/24/26.
//

#include <iostream>
using namespace std;

void without_ref(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap_with_ref(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int a,b;
    cin >> a >> b;
    without_ref(a, b);
    cout << a << " " << b << endl;
    swap_with_ref(a, b);
    cout << a << " " << b << endl;
    return 0;
}