//
// Created by igor on 2/24/26.
//

#include <chrono>
#include <iostream>
using namespace std;

struct City {
    char name[50];
    int population;
};

struct President {
    char name[50];
    char lastname[50];
    char party[50];

    void print() {
        cout << name << " " << lastname << " representing " << party << endl;
    }
};

struct Country {
    char name[50];
    President president;
    City city;
    int population;
};

void read(Country &country) {
    cin >> country.name;
    cin >> country.president.name;
    cin >> country.president.lastname;
    cin >> country.president.party;
    cin >> country.city.name;
    cin >> country.city.population;
    cin >> country.population;
}

Country findCountryWithBiggestCity(Country countries[], int n) {
    int max = 0;
    int maxi = 0;
    for (int i =0; i< n; i++) {
        if (countries[i].city.population > max) {
            max = countries[i].city.population;
            maxi = i;
        }
    }
    return countries[maxi];
}

int main() {
    Country countries[50];
    int n;
    cin >> n;
    for (int i = 0; i<n; i++) {
        read(countries[i]);
    }

    Country country = findCountryWithBiggestCity(countries, n);
    country.president.print();

    return 0;
}
