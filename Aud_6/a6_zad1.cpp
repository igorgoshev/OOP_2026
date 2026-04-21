//
// Created by igor on 4/14/26.
//

#include <chrono>
#include <iostream>
using namespace std;

class TennisPlayer {
    string name;
    string lastName;
    bool league; //true - > in Leauge
public:
    TennisPlayer(string &name, string &lastName, bool league) {
        this->name = name;
        this->lastName = lastName;
        this->league = league;
        cout << "Tennis Player Constructor" << endl;
    }

    friend ostream &operator<<(ostream &out, TennisPlayer p) {
        string fullName = p.name + " " + p.lastName;
        out << fullName << " " << (p.league ? " is playing in leauge." : " is not playing in leauge.") << endl;
        return out;
    }

    ~TennisPlayer() {}
};

class RankedTennisPlayer : public TennisPlayer {
private:
    int rank;

public:
    RankedTennisPlayer(string name, string lastName, bool leauge, int rank)
    //parent constructor being called
    : TennisPlayer(name, lastName, leauge) {
        this->rank = rank;
        cout << "Ranked Tennis Player Constructor" << endl;
    }

    friend ostream &operator<<(ostream &out, RankedTennisPlayer t) {
        out << TennisPlayer(t);
        out << "Rank: " << t.rank << endl;
        return out;
    }

    ~RankedTennisPlayer() {
    }
};

int main() {
    RankedTennisPlayer r("Igor", "Goshev", false, 1);
    cout <<"\n"<< r << endl;

    TennisPlayer t = r;
    cout << t << endl;
}
