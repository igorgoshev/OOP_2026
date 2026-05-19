//
// Created by igor on 5/16/26.
//

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class NoProductFoundException {
    string category;

public:
    NoProductFoundException(string category) {
        this->category = category;
    }

    void print() {
        cout << "No products from category "<< category <<" were found in the store" <<endl;
    }
};

class Product {
    string name;
    string category;
    int price;
    int quantity;

public:

    Product() {

    }

    Product (string name, string category, int price, int quantity) {
        this->name = name;
        this->category = category;
        this->price =price;
        this->quantity = quantity;
    }

    int totalPrice() {
        return price * quantity;
    }

    friend ostream &operator<<(ostream &out, Product p) {
        out << p.name << " (" << p.category << ") " << p.quantity << " x " << p.price << " = " << p.totalPrice() <<endl;
        return out;
    }

    bool isCategorySame(string &category) {
        return this->category == category;
    }


};

class Store {
    Product *products;
    int numProducts;

public:
    Store() {
        products = nullptr;
        numProducts = 0;
    }

    Store(const Store &s) {
        products = new Product[s.numProducts];
        numProducts = s.numProducts;
        for (int i = 0; i < numProducts; ++i) {
            products[i] = s.products[i];
        }
    }

    Store &operator=(const Store &s) {
        if (this != &s) {
            delete[]products;

            products = new Product[s.numProducts];
            numProducts = s.numProducts;
            for (int i = 0; i < numProducts; ++i) {
                products[i] = s.products[i];
            }
        }
        return *this;
    }

    friend ostream &operator<< (ostream &out, Store &s) {
        for (int i = 0; i < s.numProducts; ++i) {
            out << s.products[i];
        }
        return out;
    }

    Store &operator+=(Product p) {
        Product *tmp = new Product[numProducts+1];
        for (int i = 0; i < numProducts; ++i) {
            tmp[i] = products[i];
        }
        tmp[numProducts] = p;
        numProducts++;
        delete[]products;
        products = tmp;
        return *this;
    }

    Store fromCategory(string &category) {
        Store filteredStore;
        for (int i = 0; i < numProducts; ++i) {
            if (products[i].isCategorySame(category)) {
                filteredStore+=products[i];
            }
        }
        if (filteredStore.numProducts == 0) {
            throw NoProductFoundException(category);
        }
        return filteredStore;
    }

    ~Store() {
        delete [] products;
    }
};



void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();


    Store s;

    ifstream ifile("input.txt");
    string name;
    while (getline(ifile, name)) {
        string cat;
        int price, quantity;
        getline(ifile, cat);
        ifile >> price;
        ifile >> quantity;
        ifile.ignore();
        Product p(name, cat, price, quantity);
        s+=p;
    }

    ifile.close();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    ofstream out1File("output1.txt");
    ofstream out2File("output2.txt");
    out1File << s;
    try {
        Store filteredStore = s.fromCategory(category);
        out2File << filteredStore;
    } catch (NoProductFoundException e) {
        e.print();
    }
    out1File.close();
    out2File.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}