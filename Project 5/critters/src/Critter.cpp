/*
 * Critters
 * This class defines the methods necessary for an animal to be part of the simulation.
 * Your critter animal classes extend this class to add to its basic functionality.
 *
 * DO NOT MODIFY THIS FILE!
 *
 * @version 2021/04/11
 * - initial C++ version for 21sp
 */

#include "Critter.h"

bool Critter::eat() {
    return false;
}

Attack Critter::fight(std::string /*opponent*/) {
    return FORFEIT;
}

std::string Critter::getColor() {
    return "black";
}

Direction Critter::getMove() {
    return CENTER;
}

std::string Critter::toString() {
    return "?";
}
