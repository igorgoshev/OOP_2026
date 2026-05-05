//
// Created by igor on 5/4/26.
//

//diamond problem

#include <iostream>
using namespace std;

// base class
class Vehicle {
protected:
    double acceleration;

public:
    Vehicle() {
        cout << "Vehicle Constructor" << endl;
    }

    void setAcceleration(double a) {
        this->acceleration = a;
    }

    // accessible if when extending virtual is added
    void accelerate() {
        cout << "Vehicle Accelerating" << endl;
    }

    ~Vehicle() {
        cout << "Vehicle Destructor" << endl;
    }
};

// parent 1 class
class Car : virtual public Vehicle {
    // virtual -> makes one object of vehicle, meaning no ambiguity when calling accelerate()
public:
    Car() {
        cout << "Car Constructor" << endl;
    }

    void virtual drive() {
        cout << "Car is driving" << endl;
    }

    ~Car() {
        cout << "Car Destructor" << endl;
    }
};

// parent 2 class
class Jet : virtual public Vehicle {
    // virtual -> makes one object of vehicle, meaning no ambiguity when calling accelerate()
public:
    // automatically called Vehicle()
    Jet() {
        cout << "Jet Constructor" << endl;
    }

    virtual void fly() {
        cout << "Jet is flying" << endl;
    }

    ~Jet() {
        cout << "Jet Destructor" << endl;
    }
};

// child class
class JetCar : public Jet, public Car {
public:
    JetCar() {
        cout << "JetCar Constructor" << endl;
    }

    void fly() override {
        cout << "JetCar flying" << endl;
    }

    void drive() override {
        cout << "JetCar driving" << endl;
    }

    ~JetCar() {
        cout << "Jetcar Destructor" << endl;
    }
};

// when JetCar is passed JetCar::Drive() is called
void analyzeCarPerformance(Car *car) {
    car->drive();
}

// when JetCar is passed JetCar::fly() is called
void analyzeJetPerformance(Jet *jet) {
    jet->fly();
}

int main() {
    cout << "=========== Constructor Calling ==========" << endl;
    Car c;
    Jet j;
    JetCar jet_car;
    cout << "==========================================" << endl;

    cout << "========== accelerate() Calling ==========" << endl;
    cout<<"JetCar ";
    jet_car.accelerate(); // only 1 instance of Vehicle created
    cout<<"Car ";
    c.accelerate(); // can be used without virtual extending
    cout<<"Jet ";
    j.accelerate(); // can be used without virtual extending
    cout << "==========================================" << endl;

    cout << "===== analyzeCarPerformance Calling ======" << endl;
    analyzeCarPerformance(&c);
    analyzeCarPerformance(&jet_car);
    cout << "==========================================" << endl;

    cout << "===== analyzeJetPerformance Calling ======" << endl;
    analyzeJetPerformance(&j);
    analyzeJetPerformance(&jet_car);
    cout << "==========================================" << endl;

    cout << "=========== Destructor Calling ===========" << endl;


    return 0;
}
