#include "LetterInventory.h"
#include <iostream>

using namespace std;

const int LetterInventory::INVENTORY_LENGTH = 26;

/*
The LetterInventory constructor builds an array storing the count of each letter passed
in as a string parameter.
Parameters:
    data    string      A word of phase to build a LetterInventory.
*/
LetterInventory::LetterInventory(string data) : total_count(0) {
    for (int i = 0; i < data.size(); i++) {
        if (isalpha(data[i]) > 0) {
            char letter = tolower(data[i]);
            this->inventory[letter - 'a']++;
            this->total_count++;
        }
    }
}

/*
The set member function is used to set the value or count for a given letter in the letter
inventory.
Parameters:
    letter      char    The letter for which the value will be set.
    value       int     The value to set for the letter.
Returns:
    None
*/
void LetterInventory::set(char letter, int value) {
    if (!isalpha(letter) > 0 || value < 0) {
        throw string("first param must be alphabetical and second param must be >= 0");
    }
    letter = tolower(letter);
    this->total_count -= this->inventory[letter - 'a'];
    this->total_count += value;
    this->inventory[letter - 'a'] = value;
}

/*
The get member function is a public function used to get the LetterInventory value for
a letter.
*/
int LetterInventory::get(char letter) const {
    if (!isalpha(letter) > 0) {
        throw string("the letter param must be alphabetical");
    }
    return this->inventory[letter - 'a'];
}

/*
The size member function is a public function used to get the total size of the letter
inventory in terms of the count of all letters in the inventory.
Parameters:
    None
Returns:
    size    int     The count of all the letters in the LetterInventory.
*/
int LetterInventory::size() const {
    return this->total_count;
}

/*
The isEmpty member function is a public function used to check if the LetterInventory
is empty. If all letters have value 0, the function return true.
Parameters:
    None
Returns:
    isEmpty     int     True if the value of all letters in the inventory is zero.
*/
bool LetterInventory::isEmpty() const {
    return this->total_count == 0;
}

/*
The contains member function is a public function used to check if the calling letter
inventory contains all of the letters in the passed in string/phase. The function returns
true if the calling inventory has at least as many of each letter as that of the string
passed in as a parameter.
Parameters:
    other       string  A string to be checked if the calling LetterInventory contains all
                        the letters.
Returns:
    contains    int     True if the calling LetterInventory contains all of the letters.
*/
bool LetterInventory::contains(string other) const {
    LetterInventory otherInventory = LetterInventory(other);
    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        if (this->inventory[i] < otherInventory.inventory[i]) {
            return false;
        }
    }
    return true;
}

/*
The contains member function is a public function used to check if the calling letter
inventory contains all of the letters in the passed in LetterInventory. The function
returns true if the calling inventory has at least as many of each letter as that of
the LetterInventory passed in as a parameter.
Parameters:
    other       LetterInventory     A string to be checked if the calling letter
                                    inventory contains all the letters.
Returns:
    contains    int                 True if the calling LetterInventory contains all
                                    of the letters.
*/
bool LetterInventory::contains(LetterInventory other) const {
    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        if (this->inventory[i] < other.inventory[i]) {
            return false;
        }
    }
    return true;
}

/*
LetterInventory operator override for the [] operator. This override allows the []
operator to be used on a LetterInventory to return the value of a given letter.
Parameter:
    letter      char    A letter for which the value will be returned.
Returns:
    value       int     The value for the passed in letter.
*/
int LetterInventory::operator[](const char letter) {
    return this->inventory[letter - 'a'];
}

/*
LetterInventory operator override for the << operator. This override allows the <<
operator to be used on a LetterInventory to return an ostream object containing a
string of all the letters in the LetterInventory, in alphabetical order.
Parameter:
    li      LetterInventory     A LetterInventory to stringify and pass to an ostream.
Returns:
    out     ostream             A string representation of the LetterInventory.
*/
ostream &operator<<(ostream &out, LetterInventory &li) {
    out << "[";
    for (int i = 0; i < 26; i++) {
        for (int j = 1; j <= li.get(i + 'a'); j++) {
            out << (char)('a' + i);
        }
    }
    out << "]";
    return out;
}

/*
LetterInventory operator override for the + operator. This override allows the +
operator to be used on two LetterInventories to return a new LetterInventory that
is the summation of the value for each letter.
Parameter:
    other   LetterInventory     A LetterInventory that will be summed with the calling
                                LetterInventory.
Returns:
    newInventory    ostream     The summation of the two LetterInventories.
*/
LetterInventory LetterInventory::operator+(const LetterInventory &other) {
    LetterInventory newInventory = LetterInventory("");
    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        newInventory.set(i + 'a', this->get(i) + other.get(i));
    }
    return newInventory;
}

/*
LetterInventory operator override for the - operator. This override allows the -
operator to be used on two LetterInventories to return a new LetterInventory that
is the difference of the value for each letter of the calling LetterInventory
from another LetterInventory.
Parameter:
    other   LetterInventory     A LetterInventory that will be subtracted from the calling
                                LetterInventory.
Returns:
    newInventory    ostream     The difference of the two LetterInventories.
*/
LetterInventory LetterInventory::operator-(const LetterInventory &other) {
    LetterInventory newInventory = LetterInventory("");
    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        newInventory.set(i + 'a', this->get(i) - other.get(i));
    }
    return newInventory;
}
