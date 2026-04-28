//
// Created by igor on 4/28/26.
//

#include <cstring>
#include <iostream>

using namespace std;

class QuizAttempt {
protected:
    char studentIndex[7];

public:
    QuizAttempt(char index[]) {
        strcpy(this->studentIndex, index);
    }

    virtual double score() = 0;

    virtual void print() = 0;

    bool operator>=(QuizAttempt &q) {
        return this->score() >= q.score();
    }
};

class MCQuizAttempt : public QuizAttempt {
    char correct[10];
    char answered[10];

public:
    MCQuizAttempt(char index[], char correct[], char answered[]) : QuizAttempt(index) {
        strcpy(this->correct, correct);
        strcpy(this->answered, answered);
    }

    double score() override {
        double score = 0;
        for (int i = 0; i < 10; i++) {
            if (answered[i] == correct[i]) {
                score += 1;
            } else {
                score -= 0.25;
            }
        }
        return score;
    }

    bool checkAnswer(char _correct, char answer) {
        return _correct == answer;
    }

    void print() override {
        for (int i = 0; i < 10; ++i) {
            cout << i + 1 << ". Correct: " << correct[i] << " Answer: " << answered[i] << " Points: " <<
                    (checkAnswer(correct[i], answered[i]) ? "1" : "-0.25") << endl;
        }

        cout << "Total score: " << score() << endl;
    }
};

class TFQuizAttempt : public QuizAttempt {
    bool correct[10];
    bool answered[10];

public:
    TFQuizAttempt(char index[], bool correct[], bool answered[]) : QuizAttempt(index) {
        for (int i = 0; i < 10; ++i) {
            this->correct[i] = correct[i];
            this->answered[i] = answered[i];
        }
    }

    double score() override {
        double score = 0;
        for (int i = 0; i < 10; ++i) {
            if (correct[i] == answered[i]) {
                score += 1;
            } else {
                score -= 0.5;
            }
        }
        return score;
    }

    bool checkAnswer(bool _correct, bool answer) {
        return _correct == answer;
    }

    void print() override {
        for (int i = 0; i < 10; ++i) {
            cout << i + 1 << ". Correct: " << correct[i] << " Answer: " << answered[i] << " Points: " <<
                    (checkAnswer(correct[i], answered[i]) ? "1" : "-0.5") << endl;
        }
        cout << "Total score: " << score() <<endl;
    }
};

double averagePointsOfPassedStudents(QuizAttempt **attempts, int n) {
    double average = 0;
    int counter = 0;

    for (int i = 0; i < n; ++i) {
        if (attempts[i]->score() >= 5) {
            average += attempts[i]->score();
            counter++;
        }
    }

    return average/counter*1.0;
}

int main() {
    QuizAttempt **qa = new QuizAttempt *[5];

    char correct[] = "ABCADABCDB";
    char answered[] = "AACDDAACBB";
    char index[] = "211255";

    bool correct_b[] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    bool answered_b[] = {1, 0, 1, 1, 1, 0, 0, 0, 1, 0};

    bool correct_b1[] = {0, 0, 1, 0, 1, 1, 0, 1, 1, 0};
    bool answered_b1[] = {0, 1, 1, 0, 1, 1, 0, 1, 1, 0};


    qa[0] = new MCQuizAttempt(index, correct, answered);
    qa[1] = new TFQuizAttempt(index, correct_b, answered_b);
    qa[2] = new TFQuizAttempt(index, correct_b1, answered_b1);

    for (int i = 0; i < 3; ++i) {
        qa[i]->print();
    }

    cout << averagePointsOfPassedStudents(qa, 3) << endl;
    //operator >= in base class
    cout << (qa[1] >= qa[0]) << endl;
    cout << (qa[0] >= qa[1]) << endl;
    cout << (qa[0] >= qa[0]) << endl;
    cout << (qa[2] >= qa[1]) << endl;


    //freeing the allocated memory
    delete [] qa;
    return 0;
}
