/*
 * Critters
 * A Stone object is displayed as S and always stays put.
 * It always picks ROAR in a fight.
 */
#include <vector>

#include "Bumblebee.h"

Bumblebee::Bumblebee() : lastDirection(WEST), currentSteps(0), totalSteps(1) {}

std::string Bumblebee::getColor() {
    return "yellow";
}

Direction Bumblebee::getMove() {
    currentSteps++;
    if (currentSteps <= totalSteps) {
        return lastDirection;
    }
    currentSteps = 1;
    totalSteps++;
    if (lastDirection == WEST) {
        lastDirection = WEST;
        return SOUTH;
    } else if (lastDirection == SOUTH) {
        lastDirection = SOUTH;
        return EAST;
    } else if (lastDirection == EAST) {
        lastDirection = EAST;
        return NORTH;
    }
    lastDirection = WEST;
    return WEST;
}

std::string Bumblebee::getType() const {
    return "Bumblebee";
}

std::string Bumblebee::toString() {
}