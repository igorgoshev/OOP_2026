//
// Created by igor on 5/12/26.
//

#include <iostream>
using namespace std;

class NegativePriceException {
    string msg;
    float price;

public:
    // NegativePriceException(string msg) {
    //     this->msg = msg;
    // }

    NegativePriceException(string msg, float price) {
        this->msg = msg;
        this->price = price;
    }

    void print() {
        cout << msg << endl;
        cout << "The price entered was: " << price << endl;
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

class Product {
protected:
    string name;
    float value;

public:
    Product(string name, float value) {
        this->name = name;
        this->value = value;
    }

    void changePrice(float p) {
        if (p < 0) {
            // throwing an instance of NegativePriceException
            throw NegativePriceException("You cannot enter a negative price!", p);
        }
        // code below doesn't execute if condition is true
        cout << "I am changing price" << endl;

        this->value = p;
    }
};

class FoodProduct : public Product, public Discount {
public:
    FoodProduct(string name, float value) : Product(name, value) {
    }

    float discount_price() override {
        return price();
    }

    float price() override {
        return value;
    }

    void print_rule() override {
        cout << "The food product name is " << name << endl;
        cout << "The price is " << price() << endl;
    }
};

class Drinks : public Product, public Discount {
private:
    bool isAlh;
    string brand;

public:
    Drinks(string name, float value, string brand, bool isAlh) : Product(name, value) {
        this->isAlh = isAlh;
        this->brand = brand;
    }

    float discount_price() override {
        if (isAlh && value / EUR > 20) {
            return price() * 0.95;
            // return price() - price()*0.05;
            // price*(1-0.05) -> price*0.95
        }
        if (!isAlh && brand == "Coca-Cola") {
            return price() * 0.9;
        }
        return price();
    }

    float price() override {
        return value;
    }

    void print_rule() override {
        cout << "The drink brand is " << brand << endl;
        cout << "The price of the product is " << price() << endl;
    }
};

class Cosmetics : public Product, public Discount {
public:
    Cosmetics(string name, float amount) : Product(name, amount) {
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
        return value;
    }

    void print_rule() override {
        cout << "The cosmetic product name is " << name << endl;
        cout << "The product price is " << price() << endl;
    }
};

void total_discount(Discount **d, int n) {
    float total = 0;
    for (int i = 0; i < n; ++i) {
        total += d[i]->discount_price();
    }
    cout << "The total discount is " << total << endl;
}

float Discount::EUR = 61.64;
float Discount::DOLLAR = 52.55;

void changePriceToProduct() {
    Product p("Soda", 100);
    p.changePrice(-20);
    cout << "test" << endl;
}

int main() {
    // try to execute function
    try {
        changePriceToProduct();
    } catch (NegativePriceException e) {
        // this block is being executed if exception instance is thrown
        // e is the instance being caught
        e.print();
    }

    cout << "======================= MAIN =======================" << endl;
    int n = 0;
    float newPrice;
    Discount **d = new Discount *[10];
    d[n++] = new FoodProduct("Bread", 30);
    d[n++] = new Drinks("Whiskey", 1350, "Jack Daniel's", true);
    d[n++] = new FoodProduct("Cheese", 390);
    d[n++] = new Drinks("Vodka", 850, "Finlandia", true);
    d[n++] = new Cosmetics("Cream", 720);
    d[n++] = new Drinks("Juice", 50, "Coca-Cola", false);
    d[n++] = new Cosmetics("Parfume", 3500);

    total_discount(d, n);

    // price is changed only for cosmetic products
    cout << "Changing prices of comsetic products " << endl;

    for (int i = 0; i < n; ++i) {
        Cosmetics *c = dynamic_cast<Cosmetics *>(d[i]);
        if (c != 0) {
            c->print_rule();
            cin >> newPrice;
            try {
                c->changePrice(newPrice);
            } catch (NegativePriceException i) {
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
