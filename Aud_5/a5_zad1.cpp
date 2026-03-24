//
// Created by igor on 3/24/26.
//

#include <iostream>

using namespace std;

class Array {
    int *elements;
    int capacity;
    int size; //n
public:
    Array(int capacity = 5) {
        elements = new int[capacity];
        this->size = 0;
        this->capacity = capacity;
    }

    Array(const Array &a) {
        elements = new int[a.capacity];
        for (int i = 0; i < a.size; i++) {
            elements[i] = a.elements[i];
        }
        this->capacity = a.capacity;
        this->size = a.size;
    }

    Array &operator+=(int n) {
        if (size == capacity) {
            capacity = capacity * 2;
            int *temp = new int[capacity];
            for (int i = 0; i < size; i++) {
                temp[i] = elements[i];
            }
            temp[size] = n;
            ++size;
            delete []elements;
            elements = temp;
        } else {
            elements[size++] = n;
        }

        return *this;
    }

    //(Array &a, int n)
    Array &operator-=(int n) {
        int *temp = new int[capacity];
        int newSize = 0;
        for (int i = 0; i < size; i++) {
            if (elements[i] != n) {
                temp[newSize++] = elements[i];
            }
        }
        delete []elements;
        elements = temp;
        this->size = newSize;

        return *this;
    }

    int &operator[](int index) {
        int pom = -1;
        if (index >= 0 && index < size) {
            return elements[index];
        }
        return pom;
    }

    int *getElem() {
        return elements;
    }

    bool operator==(Array &a) {
        if (size != a.size) return false;
        for (int i = 0; i < size; i++) {
            if (elements[i] != a.elements[i]) return false;
        }

        return true;
    }

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }

    Array operator+(int n) {
        Array result(*this);
        for (int i = 0; i < size; i++) {
            result.elements[i] += n;
        }

        result;
    }

    friend ostream &operator<<(ostream &out, Array &a);

    friend istream &operator>>(istream &in, Array &a);

    ~Array() {
        delete []elements;
    }
};

Array operator+(Array &a1, Array &a2) {
    Array result(a1);

    for (int i = 0; i < a2.getSize(); i++) {
        result += a2.getElem()[i];
    }

    return result;
}


ostream &operator<<(ostream &out, Array &a) {
    out << "The capacity is: " << a.capacity << endl;
    out << "The size is: " << a.size << endl;
    out << "[ ";
    for (int i = 0; i < a.size; i++) {
        if (i == a.size - 1) {
            out << a.elements[i] << " ]";
        } else {
            out << a.elements[i] << ", ";
        }
    }
    return out;
}

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

int main() {
    Array a;
    // cin>>a;
    a += (6);
    a += (4);
    a += (3);
    a += (2);
    a += (1);
    cout << a << endl;

    Array b(a);
    cout << "Check a==b " << (a == b) << endl;

    b -= (2);
    cout << "Check a==b " << (a == b) << endl;
    b -= (3);
    cout << b << endl;

    a[0] = 9;
    cout << a << endl;
    a = (a + 5);
    cout << "a+5: " << ;

    cout << "a+b: " << (a + b);
    return 0;
}
