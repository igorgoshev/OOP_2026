//
// Created by igor on 3/17/26.
//

#include <iostream>
#include <cstring>
using namespace std;

class Team {
private:
    char name[100];
    int since;
    char city[100];

public:
    //2 in 1 Constructor (Default and with params)
    Team(char name[] = "", int since = 0, char city[] = "") {
        strcpy(this->name, name);
        strcpy(this->city, city);
        this->since = since;
    }

    //Copy constructor
    Team(const Team &team) {
        cout << "Copy Constructor" << endl;
        strcpy(this->name, team.name);
        strcpy(this->city, team.city);
        this->since = team.since;
    }

    void print() {
        cout << name << "-" << since << ": "<< city << endl;
    }

    char *getName() {
        return name;
    }

    ~Team() {
    }
};

class Game {
private:
    Team home;
    Team away;
    int homeGoals;
    int awayGoals;

public:
    //Passed by reference so that copy constructor is not called
    Game(Team &home, Team &away, int homeGoals = 0, int awayGoals = 0) {
        this->home = home;
        this->away = away;
        this->homeGoals = homeGoals;
        this->awayGoals = awayGoals;
    }

    //Copy constructor called
    Team getHome() const {
        return home;
    }
    //Copy constructor called
    Team getAway() const {
        return away;
    }

    int getHomeGoals() const {
        return homeGoals;
    }

    int getAwayGoals() const {
        return awayGoals;
    }

    ~Game() {
    }
};

//Passed by reference so that copy constructor is not called
bool isRematch(const Game &game1, const Game &game2) {
    return strcmp(game1.getHome().getName(), game2.getAway().getName()) == 0 &&
           strcmp(game1.getAway().getName(), game2.getHome().getName()) == 0;
}

//Passed by reference so that copy constructor is not called
Team duel(const Game &game1, const Game &game2) {
    if (isRematch(game1, game2)) {
        int team1Goals = game1.getHomeGoals() + game2.getAwayGoals();
        int team2Goals = game1.getAwayGoals() + game2.getHomeGoals();
        if (team1Goals > team2Goals) {
            return game1.getHome(); // game2.getAway();
        } else if (team2Goals > team1Goals) {
            return game1.getAway(); // game2.getHome();
        } else {
            cout << "The result of the matches is a draw." << endl;
            return 0;
        }

    } else {
        cout << "The games do not count as rematches." << endl;
        return 0;
    }
}


int main() {
    // Team t;
    Team t1("Rabotnicki", 1985, "Skopje");
    Team t2("Vardar", 1989, "Skopje");
    Team t3("Belasica", 1992, "Strumica");
    Game g1(t1, t2, 3, 4);
    Game g2(t2, t1, 3, 3);
    Team winner = duel(g1, g2);
    winner.print();

    return 0;
}