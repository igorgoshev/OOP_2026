//
// Created by igor on 4/28/26.
//

#include <iostream>
#include <math.h>
using namespace std;

//abstract class (Base Class)
class GeometricBody {
protected:
    float height;

public:
    GeometricBody(float height) {
        this->height = height;
    }

    virtual void print() {
        cout << "Height: " << height << endl;
    }

    //pure virtual function (this makes this class abstract)
    virtual float volume() = 0;

    virtual float getRadius() {
        return -1;
    }

};

//Derived/Child class
class Cylinder : public GeometricBody {
private:
    float radius;

public:
    Cylinder(float height, float radius) : GeometricBody(height) {
        this->radius = radius;
    }

    void print() override {
        cout << "===CYLINDER===" << endl;
        GeometricBody::print();
        cout << "Radius: " << radius << endl;
    }

    //implementation of the pure virtual function
    float volume() override {
        return radius * radius * height * M_PI;
    }

    float getRadius() override {
        return radius;
    }
};

//Derived/Child class
class Cone : public GeometricBody {
private:
    float radius;

public:
    Cone(float height, float radius) : GeometricBody(height) {
        this->radius = radius;
    }

    //implementation of the pure virtual function
    float volume() override {
        return radius * radius * M_PI * height / 3.0;
    }

    void print() override {
        cout << "===CONE===" << endl;
        GeometricBody::print();
        cout << "Radius: " << radius << endl;
    }

    float getRadius() override {
        return radius;
    }
};

//Derived/Child class
class Cuboid : public GeometricBody {
    float a, b;

public:
    Cuboid(float height, float a, float b) : GeometricBody(height) {
        this->a = a;
        this->b = b;
    }

    void print() override {
        cout << "===CUBOID===" << endl;
        GeometricBody::print();
        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
    }

    //implementation of the pure virtual function
    float volume() override {
        return a*b*height;
    }

};

void findElementWithLargestVolume(GeometricBody *g[], int n) {
    float max = 0;
    int index = -1;
    for (int i = 0; i < n; ++i) {
        //virtual function volume() is called
        if (max < g[i]->volume()) {
            max = g[i]->volume();
            index = i;
        }
    }
    g[index]->print();

}

double getRadius(GeometricBody *g) {

    // we can do it like this as well
    // return g->getRadius();

    // Casting an object of type GeometricBody to Derived classes in compile time
    Cylinder *c = dynamic_cast<Cylinder *>(g);
    if (c != 0) {

        return c->getRadius();
    }

    Cone *cone = dynamic_cast<Cone *>(g);
    if (cone != 0) {
        return cone->getRadius();
    }

    return -1;

}

int main() {
    //dynamic allocated field of pointers to GeometricBody
    GeometricBody **g = new GeometricBody *[3];

    g[0] = new Cone(30, 3);
    g[1] = new Cylinder(7, 3);
    g[2] = new Cuboid(7, 3, 4);

    findElementWithLargestVolume(g, 3);

    cout << getRadius(g[2]) << endl;
    cout << getRadius(g[1]) << endl;

    //freeing the allocated memory
    delete [] g;

    return 0;

}
