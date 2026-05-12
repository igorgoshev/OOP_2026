//
// Created by igor on 5/12/26.
//

#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream ifile("/home/igor/Desktop/Demonstrator/OOP/Aud/Aud_10/zad3_in.txt");

    if (!ifile.is_open()) {
        cout << "The input file has not been opened" << endl;
        return -1;
    }

    // opens a file for output
    ofstream ofile("/home/igor/Desktop/Demonstrator/OOP/Aud/Aud_10/zad3_out.txt");

    if (!ofile.is_open()) {
        cout << "The output file has not been opened" << endl;
        return -1;
    }

    // variable to store each line
    string line;

    // reads line by line
    while (getline(ifile, line)) {
        // output line.size() in the file
        ofile << line.size() << endl;
        // output line in the file
        ofile << line << endl;
    }

    // close both the input and output file
    ifile.close();
    ofile.close();
}
