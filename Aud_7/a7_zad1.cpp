//
// Created by igor on 4/21/26.
//

#include <chrono>
#include <complex>
#include <iostream>
using namespace std;

class HotelReservation {
protected:
    int nights;
    int numPeople;
    string name;
    string lastName;
    static int PRICE_PER_NIGHT_PER_PERSON;

public:
    HotelReservation(int nights = 0, int numPeople = 0, string name = "", string lastName = "") {
        this->nights = nights;
        this->numPeople = numPeople;
        this->name = name;
        this->lastName = lastName;
    }

    virtual int price() {
        return PRICE_PER_NIGHT_PER_PERSON * numPeople * nights;
    }

    virtual int price(int amount) {
        if (amount >= price()) {
            return amount - price();
        }
        return -1;
    }

    virtual void info() {
        cout << "Reservation made by: " << name + " " + lastName << endl;
        cout << "Nights: " << nights << endl;
        cout << "People: " << numPeople << endl;
        cout << "Total price: " << price() << endl;
    }

    ~HotelReservation() = default;
};

class HalfBoardHotelReservation : public HotelReservation {
    static int PRICE_BREAKFAST;

public:
    HalfBoardHotelReservation(int nights = 0, int numPeople = 0, string name = "", string lastName = "")
        : HotelReservation(nights, numPeople, name, lastName) {
    }


    int price() override {
        //HotelReservaton::price() -> parent method of price()
        return HotelReservation::price() + numPeople * nights * PRICE_BREAKFAST;
    }

    int price(int amount) override {
        if (amount >= price()) {
            return amount - price();
        }
        return -1;
    }

    void info() override {
        cout << "Half board Hotel ";
        HotelReservation::info();
    }
};

class Hotel {
    string hotelName;
    int balance;

public:
    Hotel(string hotelName, int balance) {
        this->balance = balance;
        this->hotelName = hotelName;
    }

    // The implementation of the function price(int amount) is called depending
    // on what type of object is being passed (HalfBoard or HotelReservation)
    int pay(HotelReservation &hr, int amount) {
        hr.info();
        return hr.price(amount);
    }
};

int HotelReservation::PRICE_PER_NIGHT_PER_PERSON = 25;
int HalfBoardHotelReservation::PRICE_BREAKFAST = 5;

int main() {
    HotelReservation hotelReservation(5, 5, "Igor", "Goshev");

    //halfBoardHotelReservation -> points to object HalfBoardHotelReservation (Base + HalfBoard)
    HotelReservation *halfBoardHotelReservation = new HalfBoardHotelReservation(5, 5, "David", "Arsov");


    Hotel h("Drim", 1000);
    int change = h.pay(hotelReservation, hotelReservation.price());
    if (change < 0) {
        cout << "You do not have enough money." << endl;
    } else {
        cout << "The change is " << change << endl;
    }


    change = h.pay(*halfBoardHotelReservation, hotelReservation.price());
    if (change < 0) {
        cout << "You do not have enough money." << endl;
    } else {
        cout << "The change is " << change << endl;
    }

    change = h.pay(*halfBoardHotelReservation, halfBoardHotelReservation->price() + 150);
    if (change < 0) {
        cout << "You do not have enough money." << endl;
    } else {
        cout << "The change is " << change << endl;
    }


    delete halfBoardHotelReservation;
}
