/*
 * Critters
 * A Stone object is displayed as S and always stays put.
 * It always picks ROAR in a fight.
 */
#include <vector>

#include "Butterfly.h"

Butterfly::Butterfly() : lastDirection(CENTER), flap(false), dir(-1) {}

std::string Butterfly::getColor() {
    return "yellow";
}

Direction Butterfly::getMove() {
    this->dir++;
    if (this->dir % 2 == 0) {
        return NORTH;
    } else if (this->dir % 4 == 1) {
        return WEST;
    } else {
        return EAST;
    }
}

std::string Butterfly::getType() const {
    return "Butterfly";
}

std::string Butterfly::toString() {
    this->flap = !this->flap;
    if (this->flap) {
        return "x";
    } else {
        return "-";
    }
}