/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #3, 01/26/23

This program is used to take in two user entered words or phases, build an inventory
of the letters in the input, and compare the two inputs to tell the user if they are
anagrams.

Usage: Call '.\app.exe' from the build folder. Follow the user prompts to enter
first and second words/phases as requested.
*/

#include <iostream>

#include "LetterInventory.h"
#include "lib132.h"

using namespace std;

/*
printIntro prints an introductory statement for the user.
Parameters:
    None
Returns:
    None
*/
void printIntro() {
    cout << "Welcome to the CS 132 anagram solver." << endl;
    cout << "Enter two words, phrases, or series of letters" << endl;
    cout << "to find out if they are anagrams of each other." << endl;
}

int main() {
    printIntro();
    // Ask the user for the first word/phase.
    string firstInput = getUserStringInput("First word/phrase/letters: ");
    // Ask the user for the second word/phase.
    string secondInput = getUserStringInput("Second word/phrase/letters: ");
    // Create letter inventories for the first and second inputs.
    LetterInventory firstLI = LetterInventory(firstInput);
    LetterInventory secondLI = LetterInventory(secondInput);

    cout << endl;
    // If the two letter inventories are the same size and the first inventory contains
    // the same letters as the second, then they must be anagrams.
    if (firstLI.size() == secondLI.size() &&
        firstLI.contains(secondLI)) {
        cout << "They are anagrams!" << endl;
    } else {
        cout << "Sorry, no anagrams here!" << endl;
    }
}