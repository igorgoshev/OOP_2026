//
// Created by igor on 3/3/26.
//

#include <cstring>
#include <iostream>
using namespace std;

class Email {
private:
    char to[50];
    char from[50];
    char subject[50];
    char content[255];

public:
    Email() {}

    Email(char to[], char from[], char subject[], char content[]) {
        strcpy(this->to, to);
        strcpy(this->from, from);
        strcpy(this->subject, subject);
        strcpy(this->content, content);
    }

    char* getTo() {
        return to;
    }
    char* getFrom() {
        return from;
    }

    char* getSubject() {
        return subject;
    }

    char* getContent() {
        return content;
    }

    void print() {
        cout << "From: " << from << endl;
        cout << "To: " << to << endl;
        cout << "Subject: " << subject << endl;
        cout << "Content: \n" << content << endl;
    }


    ~Email() {}
};

bool checkMail(char mail[]) {
    int size = strlen(mail);
    bool flag = false;
    for (int i =0; i< size; i++) {
        if (mail[i] == '@') {
            flag = true;
            continue;
        }
        // contains '.' after @ [example@gmail.com]
        if (flag && mail[i] == '.') {
            return true;
        }
    }
    return false;
}

int main() {
    char from[50], to[50], subject[50], content[255];
    cin.getline(from, 50);
    cin.getline(to, 50);
    cin.getline(subject, 50);
    cin.getline(content, 255);

    if (checkMail(from)) {
        if (checkMail(to)) {
            Email email (to, from, subject, content);

            /*
            // example usage of getters
            cout << "From: " << email.getFrom() << endl;
            cout << "To: " << email.getTo() << endl;
            cout << "Subject: " << email.getSubject() <<endl;
            cout << "Content: \n" << email.getContent();
            */

            email.print();


        } else {
            cout << "The receiver's mail is not valid!" << endl;
        }
    } else {
        cout << "The sender's mail is not valid!" << endl;
    }

    return 0;
}
