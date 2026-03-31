//
// Created by igor on 3/25/26.
//

#include <iostream>
using namespace std;

class Array {
    int *elements;
    int size;
    int capacity;

public:
    Array(int capacity = 5) {
        elements = new int[capacity];
        size = 0;
        this->capacity = capacity;
    }

    Array(const Array &a) {
        this->elements = new int[a.capacity];
        this->size = a.size;
        this->capacity = a.capacity;
        for (int i = 0; i < a.size; ++i) {
            this->elements[i] = a.elements[i];
        }
    }

    Array &operator+=(int num) {
        if (size != capacity) {
            elements[size++] = num;
        } else {
            capacity = capacity * 2;
            int *temp = new int[capacity];
            for (int i = 0; i < size; i++) {
                temp[i] = elements[i];
            }
            temp[size++] = num;
            delete []elements;
            elements = temp;
        }
        return *this;
    }

    Array &operator-=(int num) {
        int *temp = new int[capacity];
        int newSize = 0;
        for (int i = 0; i < size; ++i) {
            if (elements[i] != num) {
                temp[newSize++] = elements[i];
            }
        }
        size = newSize;
        delete []elements;
        elements = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, Array &a) {
        out << "The array has " << a.size << " and capacity of " << a.capacity << endl;
        out << "[ ";
        for (int i = 0; i < a.size; ++i) {
            if (a.size - 1 == i) {
                out << a.elements[i] << " ";
            } else {
                out << a.elements[i] << ", ";
            }
        }
        out << "]" << endl;
        return out;
    }

    bool operator==(const Array &a) const {
        if (a.size != this->size) return false;
        for (int i = 0; i < size; ++i) {
            if (elements[i] != a.elements[i]) {
                return false;
            }
        }
        return true;
    }

    Array operator+(Array &a) {
        Array result(*this);
        for (int i = 0; i < a.size; ++i) {
            result += a.elements[i];
        }
        return result;
    }


    int &operator[](int index) {
        int pom = -1;
        if (index < 0 || index >= size) {
            return pom;
        }
        return elements[index];
    }

    friend istream &operator>>(istream &in, Array &a);

    ~Array() {
        delete []elements;
    }

    int *getElements() {
        return elements;
    }

    int getSize() {
        return size;
    }
};


istream &operator>>(istream &in, Array &a) {
    int n;
    in >> n;
    for (int i = 0; i < n; i++) {
        int number;
        in >> number;
        a += number;
    }

    return in;
}

Array operator+(Array &left, int num) {
    Array result(left);

    for (int i = 0; i < result.getSize(); ++i) {
        result.getElements()[i] += num;
    }
    return result;
}

int main() {
    Array a;
    // cin >> a;
    a += 5;
    a += 6;
    a += 7;
    a += 5;
    a += 6;
    a += 7;


    Array b = a;
    if (a == b) {
        cout << "The arrays are the same" << endl;
    }

    b -= 5;

    if (a == b) {
        cout << "The arrays are the same" << endl;
    }

    b[0] = 9;

    cout << a;
    cout << b;

    Array c = a+b;
    Array d = a+2;

    cout << c;
    cout << d;

    return 0;
}
