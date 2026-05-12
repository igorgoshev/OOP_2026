//
// Created by igor on 5/11/26.
//
#include <iostream>
using namespace std;

class NegativeValueException {
    string msg;
    float price;

public:
    NegativeValueException(string msg, float price) {
        this->msg = msg;
        this->price = price;
    }

    void print() {
        cout << msg << endl;
        cout << "The price entered was " << price << endl;
    }
};

class Discount {
protected:
    static float EUR;
    static float DOLLAR;

public:
    virtual float discount_price() = 0;

    virtual float price() = 0;

    virtual void print_rule() = 0;
};

float Discount::EUR = 61.64;
float Discount::DOLLAR = 52.32;

class Product {
protected:
    string name;
    float amount;

public:
    Product(string name, float amount) {
        this->name = name;
        this->amount = amount;
    }

    void change_price(float price) {
        if (price < 0) {
            throw NegativeValueException("The price cannot be negative", price);
        }
        cout << "Testing" << endl;

        this->amount = price;
    }
};

class FoodProduct : public Product, public Discount {
public:
    FoodProduct(string n, float p) : Product(n, p) {
    }

    float discount_price() override {
        return price();
    }

    float price() override {
        return amount;
    }

    void print_rule() override {
        cout << "Name of food product: " << name << endl;
        cout << "Price of food product: " << price() << endl;
    }
};

class Drinks : public Product, public Discount {
private:
    bool isAlchoholic;

public:
    Drinks(string name, float amount, bool isAl) : Product(name, amount) {
        this->isAlchoholic = isAl;
    }

    float discount_price() override {
        if (isAlchoholic && price() / EUR > 20) {
            return price() * 0.95;
        }
        if (name == "Coca-Cola" && !isAlchoholic) {
            return price() * 0.9;
        }
        return price();
    }

    float price() override {
        return amount;
    }

    void print_rule() override {
        cout << "Name of drink product: " << name << endl;
        cout << "Price of drink product: " << price() << endl;
    }
};

class Cosmetics : public Product, public Discount {
public:
    Cosmetics(string n, float p) : Product(n, p) {
    }

    float discount_price() override {
        if (price() / DOLLAR > 20) {
            return price() * 0.86;
        }
        if (price() / EUR > 5) {
            return price() * 0.88;
        }
        return price();
    }

    float price() override {
        return amount;
    }

    void print_rule() override {
        cout << "Name of cosmetic product: " << name << endl;
        cout << "Price of cosmetic product: " << price() << endl;
    }
};

float total_discount(Discount **products, int n) {
    float sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += products[i]->discount_price();
    }
    return sum;
}


int main() {
    int n = 0;
    float newPrice;
    Discount **d = new Discount *[10];
    d[n++] = new FoodProduct("leb", 30);
    d[n++] = new Drinks("viski", 1350, true);
    d[n++] = new FoodProduct("sirenje", 390);
    d[n++] = new Drinks("votka", 850, true);
    d[n++] = new Cosmetics("krema", 720);
    d[n++] = new Drinks("sok", 50, false);
    d[n++] = new Cosmetics("parfem", 3500);

    cout << "Vkupnata cena na site proizvodi e: " << total_discount(d, n) << endl;

    //se menuva cenata na site Kozmeticki proizvodi
    cout << "Promena na cenata na kozmetickite proizvodi " << endl;
    for (int i = 0; i < n; ++i) {
        Cosmetics* c = dynamic_cast<Cosmetics *>(d[i]);
        if (c != 0){
            c->print_rule();
            cin >> newPrice;
            try{
                c->change_price(newPrice);
            }
            catch (NegativeValueException i){
                i.print();
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        delete d[i];
    }
    delete[] d;

    return 0;
}
