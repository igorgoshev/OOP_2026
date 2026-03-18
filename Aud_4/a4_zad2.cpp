//
// Created by igor on 3/17/26.
//

#include <iostream>
#include <cstring>
using namespace std;

class Library;
class LibraryMember;

class Book {
private:
    char title[50];
    char author[50];
    bool available;

    //allowing the class Library to access private and protected fields of the class Book
    friend Library;

    //allowing to access the private or protected properties from LibraryManagement inside the function
    friend void checkOutBook(LibraryMember member, Library &library, int index);

public:
    //2 in 1 (Default, Constructor with Params)
    Book(char title[] = "", char author[] = "", bool available = false) {
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->available = available;
    }


    Book(const Book &book) {
        strcpy(this->title, book.title);
        strcpy(this->author, book.author);
        this->available = book.available;
    }

    ~Book() {
    }
};

class Library {
private:
    char name[50];
    Book books[50];
    int numBooks;

    //allowing to access the private or protected properties from LibraryManagement inside the function
    friend void checkOutBook(LibraryMember member, Library &library, int index);

public:
    Library(char name[] = "Brakja Miladinovci") {
        strcpy(this->name, name);
        this->numBooks = 0;
    }

    void addBook(Book book) {
        if (numBooks >= 50) {
            cout << "Maximum books capacity" << endl;
            return;
        }

        this->books[numBooks++] = book;
    }

    void print() {
        cout << "Name: " << this->name << endl;
        cout << "Number of book is this library: " << numBooks << endl;
        for (int i = 0; i < numBooks; i++) {
            cout << i + 1 << ": " << books[i].title << " - " << books[i].author << " is " << books[i].available << endl;
        }
    }
};

class LibraryMember {
private:
    char name[50];
    int id;

    //allowing to access the private or protected properties from LibraryManagement inside the function
    friend void checkOutBook(LibraryMember member, Library &library, int index);

public:
    LibraryMember(char name[] = "", int id = 0) {
        strcpy(this->name, name);
        this->id = id;
    }
};

//Library is passed by reference to change book content
void checkOutBook(LibraryMember member, Library &library, int index) {
    if (library.books[index].available) {
        cout << member.id << " ID " << member.name << " is taking out " << library.books[index].title << endl;
        library.books[index].available = false;
    } else {
        cout << "The book is not available." << endl;
    }
}

int main() {
    Library l;


    Book b1("Book1", "Author1", true);
    Book b2("Book2", "Author2", true);
    Book b3("Book3", "Author2", true);
    Book b4("Book4", "Author1", true);
    LibraryMember m("Igor", 1);

    l.addBook(b1);
    l.addBook(b2);
    l.addBook(b3);
    l.addBook(b4);
    cout << "=============Library Details=============" << endl;
    l.print();

    //When book is available
    cout << endl << "===============Taking book===============" << endl;
    checkOutBook(m, l, 1);
    cout << endl;

    cout << "=============Library Details=============" << endl;
    l.print();

    //When book is not available
    cout << endl << "===============Taking book===============" << endl;
    checkOutBook(m, l, 1);
    cout << endl;

    cout << "=============Library Details=============" << endl;
    l.print();

    return 0;
}
