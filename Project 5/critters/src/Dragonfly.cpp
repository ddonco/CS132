#include "Dragonfly.h"

Dragonfly::Dragonfly() : eatCount(0), moveCount(0), lastDir(EAST), repeat(true) {}

string Dragonfly::getType() const {
    return "Dragonfly";
}

bool Dragonfly::eat() {
    eatCount++;
    return true;
}

Direction Dragonfly::getMove() {
    if (lastDir == EAST && repeat && moveCount == eatCount) {
        repeat = false;
        moveCount = 0;
        lastDir = NORTH;
        return NORTH;
    } else if (lastDir == EAST && moveCount == eatCount) {
        repeat = true;
        moveCount = 0;
        lastDir = SOUTH;
        return SOUTH;
    } else {
        moveCount++;
        lastDir = EAST;
        return EAST;
    }
}