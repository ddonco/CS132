/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #6, 02/24/23

LifeMain prompts a user with the Game of Life rules and asks the user to enter the name
of an initializaiton file. The user is then asked to either tick through the simulation
one step at a time, animate the simulation in a GUI, or quit.
*/

#include <fstream>
#include <iostream>

#include "LifeGui.h"
#include "LifeModel.h"

using namespace std;

/*
printIntro will print an introductory statement to the console.
Parameters:
    none
Returns:
    none
*/
void printIntro() {
    cout << "Welcome to the CS 132 Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl;
    cout << endl;
}

/*
fileExists checks if a file exists and returns true if it does or false otherwise.
Parameters:
    fileName    string      The filename to be checked if it exists.
Returns:
    fileExists  bool        True if file exists, false if not.
*/
bool fileExists(string fileName) {
    ifstream file(fileName);
    return file.good();
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
    string fileName;
    cout << prompt;
    getline(cin, fileName);
    while (!fileExists(fileName)) {
        cout << "File not found. Try again: ";
        getline(cin, fileName);
    }
    return fileName;
}

int main() {
    printIntro();
    string fileName = getUserFileName("Grid input file name? ");
    LifeModel lm = LifeModel(fileName);
    cout << lm << endl;

    LifeGui *lg;
    bool guiCreated = false;
    char input = 0;
    // Exit the loop and terminate the program if the user enters 'q'.
    while (input != 'q') {
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> input;
        input = tolower(input);
        // Update the model one step if the user enters 't'.
        if (input == 't') {
            lm.update();
            cout << lm << endl;
            // Start a GUI animation if the user enters 'a'.
        } else if (input == 'a') {
            // Check if the GUI has been created before, if so first delete the previous
            // GUI object before making another.
            if (guiCreated) {
                delete lg;
                guiCreated = false;
            }
            lg = new LifeGui(&lm);
            lg->update();
            guiCreated = true;
        }
    }

    cout << "Have a nice Life!" << endl;
    exit(0);
    return 0;
}