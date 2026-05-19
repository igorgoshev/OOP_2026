//
// Created by igor on 5/16/26.
//

#include <iostream>

using namespace std;

class Library {
protected:
    string name;
    string city;
    float base_price;
    bool worksWeekend;

public:
    Library(string name, string city, float base_price, bool worksWeekend) {
        this->name = name;
        this->city = city;
        this->base_price = base_price;
        this->worksWeekend = worksWeekend;
    }

    bool getWorksWeekend() {
        return worksWeekend;
    }

    virtual void printDetail() = 0;

    virtual double calculateMembershipCardCost() = 0;


};

class AcademicLibrary : public Library {
    bool research;
    int specialCollection;
    static int PRICE_SPECIAL_COLLECTION;

public:
    AcademicLibrary(string name, string city, float base_price, bool worksWeekend, bool research, int specialCollection)
        : Library(name, city, base_price, worksWeekend) {
        this->research = research;
        this->specialCollection = specialCollection;
    }

    void printDetail() override {
        //[Ime na biblioteka] - (Academic) [Grad] [Broj na spec. kolekcii] [Cena na clenarina]
        cout << name << " - " << "(Academic) " << city << " " << specialCollection << " " <<
                calculateMembershipCardCost() << endl;
    }

    double calculateMembershipCardCost() override {
        float price = base_price;
        if (research) {
            price = base_price * 1.24;
        }
        return price + (specialCollection * PRICE_SPECIAL_COLLECTION);
    }
};

int AcademicLibrary::PRICE_SPECIAL_COLLECTION = 6;

class NationalLibrary : public Library {
    bool culture;
    int numberSignatures;

    static int PRICE_SIGNATURE;

public:
    NationalLibrary(string name, string city, float base_price, bool worksWeekend, bool culture, int numberSignatures)
        : Library(name, city, base_price, worksWeekend) {
        this->culture = culture;
        this->numberSignatures = numberSignatures;
    }

    //[Ime na biblioteka] - (National) [Grad] [Broj na rakopisi] [Cena na clenarina] (10 поени)
    void printDetail() override {
        cout << name << " - (National) " << city << " " << numberSignatures << " " << calculateMembershipCardCost() <<
                endl;
    }

    double calculateMembershipCardCost() override {
        float price = base_price;
        if (culture) {
            price = base_price * 0.93;
        }
        return price + (numberSignatures * PRICE_SIGNATURE);
    }
};

int NationalLibrary::PRICE_SIGNATURE = 15;

int findMostExpensiveNationalLibrary(Library **l, int n) {
    float max = 0;
    int idx = -1;
    for (int i = 0; i < n; ++i) {
        NationalLibrary *n = dynamic_cast<NationalLibrary *>(l[i]);
        if (n != nullptr) {
            if (max <= n->calculateMembershipCardCost()) {
                if (max == n->calculateMembershipCardCost()) {
                    if (n->getWorksWeekend()) {
                        idx = i;
                    }
                } else {
                    max = n->calculateMembershipCardCost();
                    idx = i;
                }
            }
        }
    }

    return idx;
}

//Your code here

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library **m = new Library *[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if (testCase == 1) {
        cout << "Abstract and child classes OK" << endl;
    } else if (testCase == 2) {
        for (int i = 0; i < n; i++) {
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    } else if (testCase == 3) {
        for (int i = 0; i < n; i++) {
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    } else if (testCase == 4) {
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if (most_expensive_nat_lib_index >= 0) {
            m[most_expensive_nat_lib_index]->printDetail();
        } else {
            cout << "National Library not found in the array!" << endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
