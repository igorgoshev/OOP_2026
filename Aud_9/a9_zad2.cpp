//
// Created by igor on 5/5/26.
//

#include <iostream>
using namespace std;

// parent class 2
class Product {
protected:
    string name;
    double amount;

public:
    Product(string name, double price) {
        this->name = name;
        this->amount = price;
    }

};

// parent class 1
class Discount {
public:

    virtual double price() = 0;
    virtual double discountedPrice() = 0;
};

class FoodProduct : public Product, public Discount {
private:
    int calories;
public:
    // parent constructor called for Product only
    FoodProduct(string name, double price, int calories) : Product(name, price) {
        this->calories = calories;
    }

    double price() override {
        return calories*amount/100.0;
    }

    double discountedPrice() override {
        return price()*0.8;
    }

};

class DigitalProduct : public  Product, public Discount {
private:
    int size;
public:
    DigitalProduct(string name, double price, int size) : Product(name, price) {
        this->size = size;
    }

    double price() override {
        return amount*size/10000.0;
    }

    double discountedPrice() override {
        return price() * 0.7;
    }
};

// of type discount to be able to call discountedPrice()
void totalDiscount(Discount *d[], int n) {
    double totalDiscount = 0;
    for (int i = 0; i < n; ++i) {
        totalDiscount+=d[i]->discountedPrice();
    }
    cout << "The total discount is: "<< totalDiscount << endl;
}


// of type discount to be able to call price()
void totalPrice(Discount *d[], int n) {
    double totalPrice = 0;
    for (int i = 0; i < n; ++i) {
        totalPrice+= d[i]->price();
    }
    cout <<"The total price is: " << totalPrice << endl;
}

int main () {
    // this will work with Product **p = new Product*[3] also
    Discount **d = new Discount*[3];
    d[0] = new FoodProduct("Cheese", 450, 1200);
    d[1] = new FoodProduct("Wine", 780, 250);
    d[2] = new DigitalProduct("WOW", 380, 400);

    totalPrice(d, 3);
    totalDiscount(d, 3);

    // freeing allocated memory;
    delete [] d;
}
