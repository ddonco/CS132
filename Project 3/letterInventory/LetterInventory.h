#ifndef _LetterInventory_h
#define _LetterInventory_h

#include <string>
#include <vector>

using namespace std;

class LetterInventory {
    static const int INVENTORY_LENGTH;

private:
    int inventory[26] = {0};
    int total_count;

public:
    LetterInventory(string data);
    void set(char letter, int value);
    int get(char letter) const;
    int size() const;
    bool isEmpty() const;
    bool contains(string other) const;
    bool contains(LetterInventory other) const;
    int operator[](const char letter);
    LetterInventory operator+(const LetterInventory &li);
    LetterInventory operator-(const LetterInventory &li);
};

ostream &operator<<(ostream &out, LetterInventory &li);

#endif