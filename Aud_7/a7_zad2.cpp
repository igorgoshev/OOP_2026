//
// Created by igor on 4/21/26.
//

#include <iostream>

using namespace std;

class User {
    string username;
    string companyName;
    int position; // [1-10]

public:
    User(string username = "", string companyName = "", int position = 0) {
        this->username = username;
        this->companyName = companyName;
        this->position = position;
    }

    friend ostream &operator<<(ostream &out, User u) {
        out << "\t" << u.username << endl;
        out << "\t" << u.companyName << endl;
        out << "\t" << "Position: " << u.position << endl;
        return out;
    }

    bool operator==(User &u) {
        return u.username == this->username;
    }

    ~User() = default;

    int getPosition() {
        return position;
    }
};

class Group {
protected:
    User *users;
    int n;
    string name;

public:
    Group(string name) {
        this->name = name;
        n = 0;
        users = nullptr;
    }

    float averagePosition() {
        float sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += users[i].getPosition();
        }
        return sum / n * 1.0;
    }

    Group(const Group &g) {
        this->name = g.name;
        this->n = g.n;
        this->users = new User[n];
        for (int i = 0; i < n; ++i) {
            users[i] = g.users[i];
        }
    }

    virtual void addMember(User &u) {
        for (int i = 0; i < n; ++i) {
            if (users[i] == u) {
                return;
            }
        }
        User *tmp = new User[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = users[i];
        }

        tmp[n++] = u;
        delete[]users;
        users = tmp;
    }

    virtual float rating() {
        return (10 - averagePosition()) * (n * 1.0 / 100 * 1.0);
    }

    friend ostream &operator<<(ostream &out, Group g) {
        out << g.name << endl;
        out << "Members: " << g.n << endl;
        out << "Rating: " << g.rating() << endl;
        for (int i = 0; i < g.n; ++i) {
            out << g.users[i] << endl;
        }
        return out;
    }

    ~Group() {
        delete [] users;
    }
};

class PrivateGroup : public Group {
    static int CAPACITY;
    static const float COEF;

public:
    PrivateGroup(string name = "") : Group(name) {
    }

    PrivateGroup(const PrivateGroup &pg) : Group(pg) {
    }

    void addMember(User &u) override {
        if (n == CAPACITY) {
            return;
        }
        Group::addMember(u);
    }

    float rating() override {
        return (10 - averagePosition()) * (n * 1.0 / CAPACITY * 1.0) * COEF;
    }

    static void setCapacity(int value) {
        CAPACITY = value;
    }

    friend ostream &operator<<(ostream &out, PrivateGroup g) {
        out << g.name << endl;
        out << "Members: " << g.n << endl;
        out << "Rating: " << g.rating() << endl;

        for (int i = 0; i < g.n; ++i) {
            out << g.users[i] << endl;
        }

        return out;
    }
};

int PrivateGroup::CAPACITY = 3;
const float PrivateGroup::COEF = 0.8;

int main() {
    User u1("igosev", "FINKI", 5);
    User u2("darsov", "FINKI", 6);
    User u3("sandonov", "FINKI", 8);
    User u4("vspasev", "FINKI", 10);

    Group g("Asistenti");
    g.addMember(u1);
    g.addMember(u2);
    g.addMember(u3);
    g.addMember(u3);

    cout << g << endl;

    PrivateGroup pg("Profesori");
    pg.addMember(u1);
    pg.addMember(u2);
    pg.addMember(u3);
    pg.addMember(u4);

    cout << pg << endl;

    return 0;
}
