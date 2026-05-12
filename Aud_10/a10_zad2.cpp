//
// Created by igor on 5/11/26.
//

#include <iostream>
#include <fstream>

using namespace std;

bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'o' || c == 'u' || c == 'i';
}

int countVowels(string line) {
    int counter = 0;
    for (int i = 0; i < line.size(); ++i) {
        if (isVowel(line[i])) {
            counter++;
        }
    }
    return counter;
}

int main() {
    string line;
    //initialize and open the file
    ifstream ifile("/home/igor/Desktop/Demonstrator/OOP/Aud/Aud_10/zad2.txt");

    // initialize then open the file
    // ifstream ifile();
    // ifile.open("/home/igor/Desktop/Demonstrator/OOP/Aud/Aud_10/zad2.txt");

    // checks if the file is being opened properly
    if (!ifile.is_open()) {
        cout << "The file is not opened" << endl;
        return -1;
    }

    // int sum = 0;
    // int countLines = 0;

    // while (getline(ifile, line)) {
    //     int vowels = countVowels(line);
    //     if (vowels >= 10) {
    //         countLines++;
    //     }
    //     sum +=vowels;
    // }

    // variable to store each character
    char c;
    int total_vowels = 0;
    int line_vowels = 0;
    int lines_with_more_than_ten = 0;

    // reading character by character
    while (ifile.get(c)) {

        if (isVowel(c)) {
            total_vowels++;
            line_vowels++;
        }

        // checks if new line appears
        if (c == '\n') {
            if (line_vowels >= 10) {
                lines_with_more_than_ten++;
            }
            line_vowels = 0;
        }
    }

    cout << "Lines with more than 10 vowels " << lines_with_more_than_ten << endl;
    cout << "The total vowels are " << total_vowels << endl;

    // closes the file
    ifile.close();


    return 0;
}
