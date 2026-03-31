//
// Created by igor on 3/31/26.
//

#include <iostream>
#include <cstring>
using namespace std;

//YOUR CODE HERE:

enum AccountType {
    personal, //0
    company // 1
};

class Account {
    char name[30];
    int id;
    AccountType type;
    float balance;
    static int ACCOUNT_IDX;

public:
    Account(char name[], int type, float balance) {
        strcpy(this->name, name);
        this->type = (AccountType) type;
        this->balance = balance;
        this->id = ++ACCOUNT_IDX;
    }

    Account() {
    }


    friend ostream &operator<<(ostream &out, Account a) {
        out << a.id << " - " << a.name << " " << (a.type ? "company" : "person") << " " << a.balance << endl;
        return out;
    }

    Account &operator-=(float amount) {
        this->balance -= amount;
        return *this;
    }

    bool operator==(const Account &a) const {
        return this->id == a.id;
    }

    int getId() {
        return this->id;
    }

    ~Account() {
    }

    float getFee() {
        if (type == 0) {
            return balance * 0.008;
        } else {
            return balance * 0.015;
        }
    }
};

class Bank {
    char name[20];
    Account *accounts;
    int numAccounts;

public:
    Bank(char name[] = "") {
        strcpy(this->name, name);
        accounts = new Account[0];
        this->numAccounts = 0;
    }

    Bank(const Bank &b) {
        strcpy(this->name, b.name);
        accounts = new Account[b.numAccounts];
        this->numAccounts = b.numAccounts;
        for (int i = 0; i < numAccounts; ++i) {
            accounts[i] = b.accounts[i];
        }
    }

    Bank &operator=(const Bank &b) {
        if (this != &b) {
            strcpy(this->name, b.name);
            this->numAccounts = b.numAccounts;
            delete []accounts;
            this->accounts = new Account[numAccounts];
            for (int i = 0; i < numAccounts; ++i) {
                accounts[i] = b.accounts[i];
            }
        }
        return *this;
    }

    bool operator<(Bank &b) {
        return this->numAccounts < b.numAccounts;
    }

    friend ostream &operator<<(ostream &out, Bank b) {
        out << b.name << endl;

        for (int i = 0; i < b.numAccounts; ++i) {
            out << b.accounts[i];
        }
        return out;
    }

    Bank &operator+=(Account &a) {
        for (int i = 0; i < numAccounts; ++i) {
            // if (accounts[i].getId() == a.getId()) {
            if (accounts[i] == a) {
                return *this;
            }
        }
        Account *temp = new Account[numAccounts + 1];
        for (int i = 0; i < numAccounts; ++i) {
            temp[i] = accounts[i];
        }
        temp[numAccounts++] = a;
        delete []accounts;
        accounts = temp;
        return *this;
    }

    void bankFee() {
        for (int i = 0; i < numAccounts; ++i) {
            accounts[i] -= accounts[i].getFee();
        }
    }

    ~Bank() {
        delete[] accounts;
    }
};

Bank leastLiquid(Bank banks[], int n) {
    Bank min = banks[0];
    for (int i = 0; i < n; ++i) {
        if (banks[i] < min) {
            min = banks[i];
        }
    }
    return min;
}

int Account::ACCOUNT_IDX = 111110;

int main() {
    int testCase;
    cin >> testCase;
    if (testCase == 0) {
        cout << "TESTING ACCOUNT CONSTRUCTOR" << endl;
        Account account1("Paul", 0, 32000);
        Account account2("Globex", 1, 500000);
        Account account3("Anna", 0, 8700);
        cout << "TEST PASSED" << endl;
    } else if (testCase == 1) {
        cout << "TESTING ACCOUNT OPERATOR <<" << endl;
        Account account1("Paul", 0, 32000);
        Account account2("Globex", 1, 500000);
        Account account3("Anna", 0, 8700);
        cout << account1;
        cout << account2;
        cout << account3;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING ACCOUNT OPERATOR -=" << endl;
        Account account1("Paul", 0, 32000);
        Account account2("Globex Industries", 1, 500000);
        Account account3("Anna", 0, 8700);
        cout << account1;
        cout << account2;
        cout << account3;
        account1 -= 350;
        account2 -= 20000;
        account3 -= 500;
        cout << "===== DECREASE =====" << endl;
        cout << account1;
        cout << account2;
        cout << account3;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING BANK CONSTRUCTOR and <<" << endl;
        Bank bank1("Capital One Bank");
        cout << bank1;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 4) {
        cout << "TESTING BANK OPERATOR += and <<" << endl;
        Account account1("Paul", 0, 32000);
        Account account2("Globex Industries", 1, 500000);
        Account account3("Anna", 0, 8700);
        Bank bank1("Capital One Bank");
        bank1 += account1;
        bank1 += account2;
        bank1 += account3;
        cout << bank1;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 5) {
        cout << "TESTING BANK OPERATOR += and <<" << endl;
        Account account1("Paul", 0, 32000);
        Account account2("Globex Industries", 1, 500000);
        Account account3("Anna", 0, 8700);
        Bank bank1("Capital One Bank");
        bank1 += account1;
        bank1 += account2;
        bank1 += account3;
        bank1 += account1;
        cout << bank1;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 6) {
        cout << "TESTING BANK COPY-CONSTRUCTOR and OPERATOR =" << endl;
        Account account1("Paul", 0, 32000);
        Account account2("Globex Industries", 1, 500000);
        Account account3("Anna", 0, 8700);
        Account account4("Umbrella Corporation", 1, 300000);
        Account account5("Theo", 0, 15500);
        Bank bank1("Capital One Bank");
        bank1 += account1;
        bank1 += account2;
        bank1 += account3;
        Bank bank2(bank1);
        Bank bank4;
        {
            Bank bank3("First National Bank");
            bank3 += account4;
            bank3 += account5;
            bank4 = bank3;
        }
        cout << bank2;
        cout << bank4;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 7) {
        cout << "TESTING BANK OPERATOR < " << endl;
        Account account1("Paul", 0, 32000);
        Account account2("Globex Industries", 1, 500000);
        Account account3("Anna", 0, 8700);
        Account account4("Umbrella Corporation", 1, 300000);
        Account account5("Theo", 0, 15500);
        Bank bank1("Capital One Bank");
        bank1 += account1;
        bank1 += account2;
        bank1 += account3;
        Bank bank3("First National Bank");
        bank3 += account4;
        bank3 += account5;
        if (bank1 < bank3) {
            cout << "TEST FAILED" << endl;
        } else {
            cout << "TEST PASSED" << endl;
        }
    } else if(testCase==8)
    {
        cout<<"TESTING METHOD bankFee()"<<endl;
        char name[30],name1[30];
        int type, numberOfBanks, numberOfAccounts;
        float money;
        cin>>numberOfBanks;
        cin.ignore();
        Bank banks[10];
        for(int i=0;i<numberOfBanks;i++)
        {
            cin.getline(name,20);
            banks[i]=Bank(name);
            cin>>numberOfAccounts;
            cin.ignore();
            Account accounts[10];
            for(int j=0;j<numberOfAccounts;j++)
            {
                cin >> name1 >> type >> money;
                cin.ignore();
                accounts[j]=Account(name1,type,money);
                banks[i]+=accounts[j];
            }
        }
        for(int i=0;i<numberOfBanks;i++)
        {
            cout<<banks[i];
            cout<<"FEE-PAID"<<endl;
            banks[i].bankFee();
            cout<<banks[i];
        }
    }else if(testCase==9)
    {
        cout<<"TESTING METHOD leastLiquid()"<<endl;
        char name[30],name1[30];
        int type, numberOfBanks, numberOfAccounts;
        float money;
        cin>>numberOfBanks;
        cin.ignore();
        Bank banks[10];
        for(int i=0;i<numberOfBanks;i++)
        {
            cin.getline(name,20);
            banks[i]=Bank(name);
            cin>>numberOfAccounts;
            cin.ignore();
            Account accounts[10];
            for(int j=0;j<numberOfAccounts;j++)
            {
                cin >> name1 >> type >> money;
                cin.ignore();
                accounts[j]=Account(name1,type,money);
                banks[i]+=accounts[j];
            }
        }
        cout<<leastLiquid(banks,numberOfBanks);
    }
    return 0;
}
