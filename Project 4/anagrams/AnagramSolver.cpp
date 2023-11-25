/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #4, 02/06/23

AnagramSolver is intended find anagram phrases/words given an input
word or phrase, using a user supplied list of words as a dictionary.
*/

#include <iostream>

#include "AnagramSolver.h"
#include "LetterInventory.h"

using namespace std;

/*
printStrVec is used to output a vector of strings to the console.
This function is not part of the AnagramSolver class becasue it is a
generic utility function.
Parameters:
    vec     vector<string>  A vector of strings to be output.
Returns:
    none
*/
void printStrVec(vector<string> vec) {
    cout << "[";
    if (vec.size() > 0) {
        cout << vec[0];
        for (int i = 1; i < vec.size(); i++) {
            cout << ", " << vec[i];
        }
    }
    cout << "]" << endl;
}

AnagramSolver::AnagramSolver(const vector<string> &dictionary) {
    this->dictionary = dictionary;
}

vector<string> AnagramSolver::getWords(const string &phrase) {
    LetterInventory phraseInventory = LetterInventory(phrase);
    vector<string> words;
    // Loop through all words in the dictionary to find potential candidates
    // for anagrams.
    for (string word : this->dictionary) {
        LetterInventory li = LetterInventory(word);
        // If the letter inventory of the phase contains a word in the dictionary
        // add it to the list of potential anagram candidates.
        if (phraseInventory.contains(li)) {
            words.push_back(word);
        }
    }
    return words;
}

void AnagramSolver::printHelper(
    LetterInventory &currentInventory,
    vector<string> &words,
    vector<string> &chosen,
    int maxWords) {
    // An anagram is found and output if no letters are left in the current LetterInventory
    // and either there is no words max (max = 0) or the number of words is less than or equal
    // to the max.
    if (currentInventory.isEmpty() && (maxWords == 0 || chosen.size() <= maxWords)) {
        printStrVec(chosen);
        // If there is no words max or the size of chosen words is less than max words,
        // continue searching/recursing.
    } else if (maxWords == 0 || chosen.size() < maxWords) {
        for (int i = 0; i < words.size(); i++) {
            // Check if the current letters in the LetterInventory contain the next potential
            // word to add to chosen.
            if (currentInventory.contains(words[i])) {
                // Chose a word and add it to chosen.
                chosen.push_back(words[i]);
                LetterInventory wordInventory = LetterInventory(words[i]);
                // Subtract the chosen words letters from the current LetterInventory.
                currentInventory = currentInventory - wordInventory;
                // Recursively search for words to make an anagram.
                printHelper(currentInventory, words, chosen, maxWords);
                // Add the letter of the chosen word back to the current LetterInventory.
                currentInventory = currentInventory + wordInventory;
                // Unchose a word and remove from chosen.
                chosen.erase(chosen.begin() + chosen.size() - 1);
            }
        }
    }
}

void AnagramSolver::print(const string &phrase) {
    vector<string> chosen;
    LetterInventory li = LetterInventory(phrase);
    vector<string> words = getWords(phrase);
    printHelper(li, words, chosen, 0);
}

void AnagramSolver::print(const string &phrase, int max) {
    vector<string> chosen;
    LetterInventory li = LetterInventory(phrase);
    vector<string> words = getWords(phrase);
    printHelper(li, words, chosen, max);
}