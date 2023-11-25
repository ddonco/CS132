// CS 132, Winter 2022
//
// AnagramMain contains a main program that prompts a user for the name of a
// dictionary file and then gives the user the opportunity to find anagrams of
// various phrases.  It constructs an AnagramSolver object to do the actual
// search for anagrams that match the user's phrases.

// NOTE: All uses of your AnagramSolver are commented out so that this code will
//       compile and run when you first download it. You will need to uncomment the
//       lines with the comments before them starting with "TODO" in order for it
//       to run your code.

#include "AnagramSolver.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Prompts the user for the name of the dictionary file, opens that file and reads each
// line of it into  a vector which it returns. Assumes the file exists.
vector<string> getDictionary() {
    cout << "What is the name of the dictionary file? ";
    string fileName;
    getline(cin, fileName);
    ifstream inputFile;
    inputFile.open(fileName);

    // read dictionary into a vector
    vector<string> dictionary;
    string word;
    while (getline(inputFile, word)) {
        dictionary.push_back(word);
    }
    return dictionary;
}

// Prompts the user for the maximum number of words to include in the anagram.
// If the user does not enter anything no max is assumed and 0 is supplied as
// the max. The max is then returned.
int getMax() {
    cout << "Max words to include (Enter for no max)? ";
    int max = 0;
    string count;
    getline(cin, count);
    if (count.length() != 0) {
        max = stoi(count);
    }
    return max;
}

// overrides the print operator for vectors of strings so that
// they print out surrounded with square brackets with each pair of
// elements separated by a comma and space
ostream &operator<<(ostream &out, vector<string> v) {
    out << "[";
    if (v.size() > 0) {
        out << v[0];
        for (int i = 1; i < v.size(); i++) {
            out << ", " << v[i];
        }
    }
    out << "]";
    return out;
}

int main() {
    cout << "Welcome to the CS 132 anagram solver." << endl;
    cout << endl;

    vector<string> dictionary = getDictionary();

    AnagramSolver solver(dictionary);
    bool done = false;
    while (!done) {
        cout << endl;
        cout << "Phrase to scramble (Enter to quit)? ";
        string phrase;
        getline(cin, phrase);
        if (phrase.length() == 0) {
            done = true;
        } else {
            cout << "All words found in \"" << phrase << "\":" << endl;

            vector<string> words = solver.getWords(phrase);
            cout << words << endl;

            cout << endl;
            int max = getMax();
            cout << endl;

            solver.print(phrase, max);
        }
    }
    return 0;
}
