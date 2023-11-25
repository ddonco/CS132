/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #1, 01/12/23

This program is used to allow a user to generate madlibs through the console using text
files that contain madlib placeholders.

Usage: Call '.\madlibs.exe' from a folder that contains a madlib text files. Follow the
user prompts to enter input file name, output file name, and madlib words as requested.
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "lib132.cpp"

/*
printIntro will print an introductory statement to the console.
Parameters:
    none
Returns:
    none
*/
void printIntro() {
    cout << "Welcome to the game of Mad Libs." << endl;
    cout << "I will ask you to provide several words" << endl;
    cout << "and phrases to fill in a mad lib story." << endl;
    cout << "The result will be written to an output file." << endl;
}

/*
getUserStringInput is used to print a prompt to the console and wait for user input.
Parameters:
    prompt  string      A prompt to be printed to the console.
Returns:
    input   string      User input.
*/
string getUserStringInput(string prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

/*
getUserFileName is used to prompt a user for a file name. The function checks if the
entered file exists, if not the user is prompted until a valid file name is entered.
Parameters:
    prompt      string      A prompt to be printed to the console.
Returns:
    fileName    string      The name of a valid file.
*/
string getUserFileName(string prompt) {
    string fileName = getUserStringInput(prompt);
    while (!fileExists(fileName)) {
        fileName = getUserStringInput("File not found. Try again: ");
    }
    return fileName;
}

/*
printFile opens a file and prints the contents to the console.
Parameters:
    fileName    string      The name of a file to be printed.
Returns:
    none
*/
void printFile(string fileName) {
    ifstream input;
    input.open(fileName);
    string line;
    while (getline(input, line)) {
        cout << line << endl;
    }
    input.close();
}

/*
hasVowelFirst is used to check if a string has a vowel at the first position and returns
true or false accordingly.
Parameters:
    word        string      A string to check if it contains a vowel first.
Returns:
    vowelFirst  bool        True if the string has a vowel in the first position.
*/
bool hasVowelFirst(string word) {
    char first = tolower(word[0]);
    if (first == 'a' || first == 'e' || first == 'i' || first == 'o' || first == 'u') {
        return true;
    }
    return false;
}

/*
replaceMadlibToken is used to parse a string, find madlib placeholders, prompt the user to
enter text for those placeholders, and replace the placeholders with the user input. Madlib
placeholders are denoted by open and close angle brackets, < >. The line string is passed as
a reference such that the contents of the string can be edited without having to be returned.
Parameters:
    line    string      A line to search for madlib placeholders and replace with user input.
Returns:
    none
*/
void replaceMadlibToken(string &line) {
    bool keepLooking = true;
    while (keepLooking) {
        int leftToken = line.find("<");
        int rightToken = line.find(">", leftToken);
        if (leftToken != string::npos && rightToken != string::npos) {
            string madlibPlaceholder = line.substr(leftToken + 1, rightToken - leftToken - 1);
            cout << "Please type ";
            if (hasVowelFirst(madlibPlaceholder)) {
                cout << "an ";
            } else {
                cout << "a ";
            }
            cout << madlibPlaceholder << ": ";
            string input;
            getline(cin, input);
            line.replace(leftToken, rightToken - leftToken + 1, input);
        } else {
            keepLooking = false;
        }
    }
}

/*
createMadLib is used to read a madlib text file, loop over the lines in the file,
replace madlib placeholders in the lines, and lastly output the file contents
into a file specified by the user.
Parameters:
    inputFileName   string  The name of the madlib input file with placeholders.
    outputFileName  string  The name of the generated madlib file.
Returns:
    none
*/
void createMadLib(string inputFileName, string outputFileName) {
    ifstream input;
    input.open(inputFileName);
    ofstream output;
    output.open(outputFileName);
    string line;
    while (getline(input, line)) {
        string userInput;
        replaceMadlibToken(line);
        output << line;
        output << endl;
    }
    input.close();
    output.close();
    cout << "Your mad-lib story has been created!" << endl;
}

int main() {
    printIntro();
    cout << endl;
    // Get the users requested action.
    string command = getUserStringInput("Create, view or quit? ");
    command = toLowerCase(command);

    // As long as the user does enter 'quit', continue to prompt the user
    // to create, view, or quit.
    while (command != "quit") {
        if (command == "view") {
            string fileName = getUserFileName("Input file name: ");
            printFile(fileName);
            cout << endl;
        }

        if (command == "create") {
            string inputFileName = getUserFileName("Input file name: ");
            string outputFileName = getUserStringInput("Output file name: ");
            cout << endl;
            createMadLib(inputFileName, outputFileName);
            cout << endl;
        }

        command = getUserStringInput("Create, view or quit? ");
        command = toLowerCase(command);
    }
}