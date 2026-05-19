//
// Created by igor on 5/19/26.
//
#include <iostream>
#include <cstring>
#include <limits.h>

using namespace std;

class Museum {
protected:
    string name;
    string city;
    float base_price;
    int workingHours;

public:
    Museum(string name, string city, float base_price, int workingHours) {
        this->name = name;
        this->city = city;
        this->base_price = base_price;
        this->workingHours = workingHours;
    }

    int getWrokingHours() {
        return workingHours;
    }

    virtual void printDetail() = 0;

    virtual double calculateTicketCost() = 0;
};

class ScientificMuseum : public Museum {
    bool interactiveStakes;
    int numPresentations;

public:
    ScientificMuseum(string name, string city, float base_price, int workingHours, bool interactive,
                     int numPresentations)
        : Museum(name, city, base_price, workingHours) {
        this->interactiveStakes = interactive;
        this->numPresentations = numPresentations;
    }

    void printDetail() override {
        //[Museum Name] - (Scientific) [City] [Number of multimedia presentations] [Ticket price]
        cout << name + " - (Scientific) " + city + " " << numPresentations << " " << calculateTicketCost() <<endl;
    }

    double calculateTicketCost() override {
        double price = base_price;
        if (interactiveStakes) {
            price = price * 1.12;
        }
        return price + numPresentations * 6;
    };
};

class ArtMuseum : public Museum {
    bool amateur;
    int numArtworks;

public:
    ArtMuseum(string name, string city, float base_price, int workingHours, bool amateur, int numArtworks)
        : Museum(name, city, base_price, workingHours) {
        this->amateur = amateur;
        this->numArtworks = numArtworks;
    }

    void printDetail() override {
        //[Museum Name] - (Art) [City] [Amateur exhibitions] [Ticket price]
        cout << name + " - (Art) " + city + " " << amateur << " " << calculateTicketCost() << endl;
    }

    double calculateTicketCost() override {
        double price = base_price;
        if (amateur) {
            price = price * 0.82;
        }
        return price + 3 * numArtworks;
    }
};

int findCheapestScientificMuseum(Museum **m, int n) {
    double min = INT_MAX;
    int idx = -1;

    for (int i = 0; i < n; ++i) {
        ScientificMuseum *s = dynamic_cast<ScientificMuseum *>(m[i]);
        if (s != nullptr) {
            if (min >= s->calculateTicketCost()) {
                if (min == s->calculateTicketCost()) {
                    if (s->getWrokingHours() > m[idx]->getWrokingHours()) {
                        // min = s->calculateTicketCost();
                        idx = i;
                    }
                } else {
                    min = s->calculateTicketCost();
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

    Museum **m = new Museum *[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if (testCase == 1) {
        cout << "Abstract and child classes OK" << endl;
    } else if (testCase == 2) {
        for (int i = 0; i < n; i++) {
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    } else if (testCase == 3) {
        for (int i = 0; i < n; i++) {
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    } else if (testCase == 4) {
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if (cheapest_sci_museum_index >= 0) {
            m[cheapest_sci_museum_index]->printDetail();
        } else {
            cout << "Scientific Museum not found in the array!" << endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
