//
// Created by igor on 4/14/26.
//

#include <cstring>
#include <iostream>

using namespace std;

//parent or base class
class DebitAccount {
//in order to have access in child class
protected:
    string name;
    string lastName;
    long number;
    double balance;
public:
    DebitAccount(string name, string lastName, long number, double balance) {
        this->name = name;
        this->lastName = lastName;
        this->number = number;
        this->balance = balance;
    }

    void info() {
        cout << "Name: " << name << endl;
        cout << "Last Name: " << lastName << endl;
        cout << "Number: " << number << endl;
        cout << "Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            cout << "Withdrawing " << amount << "..." << endl;
            balance-=amount;
        } else {
            cout << "Trying to withdraw " << amount << "..." << endl;
            cout << "You cannot withdraw more money than you have!" << endl;
        }
    }

    void deposit(double amount) {
        balance+=amount;
    }

    ~DebitAccount(){}

};

//child or derived class
class CreditAccount : DebitAccount {
    double limit;
    double interest;
    double minus;

public:
    CreditAccount(string name="---", string lastName="---", long number=123123, double balance=500,
        double limit=500, double interest=0.05, double minus=0)
    //parent constructor being called
    : DebitAccount(name, lastName, number, balance) {
        this->minus = minus;
        this->interest = interest;
        this->limit = limit;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            //parent withdraw function called
            DebitAccount::withdraw(amount);
            return;
        }
        if (balance + limit - minus >= amount) {
            double credit = amount - balance;
            //parent deposit function called
            deposit(credit);
            this->minus+=credit;
            DebitAccount::withdraw(amount);

        } else {
            cout << "Trying to withdraw " << amount << "..." << endl;
            cout << "The bank does not give you that much credit." << endl;
        }

    }

    void info() {
        //parent info function being called
        DebitAccount::info();
        cout << "Limit: " << limit << endl;
        cout << "Minus: " << minus << endl;
        cout << "Interest: " << interest << endl;
        cout << "Minus + Interest: " << minus + minus*interest << endl;
    }

    ~CreditAccount(){}
};


int main() {
    cout << "======Debit Account======"<<endl;
    DebitAccount d("Igor", "Goshev", 1234123412341243, 15000);
    d.info();

    cout << "\n======Withdraw======" <<endl;
    d.withdraw(5000);
    d.info();

    cout << "\n======Withdraw======" <<endl;
    d.withdraw(10001);

    cout << "\n======Credit Account======" << endl;
    CreditAccount c("Igor", "Goshev", 1234123412341234, 500);
    c.info();

    cout << "\n======Withdraw======" << endl;
    c.withdraw(600);
    c.info();

    cout << "\n======Withdraw======" << endl;
    c.withdraw(500);
    c.info();

    cout << "\n======Withdraw======" << endl;
    c.withdraw(400);
    c.info();


}
