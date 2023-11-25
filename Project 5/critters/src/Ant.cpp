/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #5, 02/15/23

 An Ant object is displayed as an "%" and is the color red. It walks either
 north-east or south-east depending on the value of the walkSouth bool
 parameter passed in to the constuctor. An Ant always picks Scratch in a
 fight and always eats when it find food.
 */

#include "Ant.h"

Ant::Ant(bool walkSouth) : walkSouth(walkSouth), lastDirection(CENTER) {}

bool Ant::eat() {
    return true;
}

Attack Ant::fight(std::string) {
    return SCRATCH;
}

std::string Ant::getColor() {
    return "red";
}

Direction Ant::getMove() {
    Direction move;
    if (walkSouth) {
        if (this->lastDirection != SOUTH) {
            move = SOUTH;
        } else {
            move = EAST;
        }
    } else {
        if (this->lastDirection != NORTH) {
            move = NORTH;
        } else {
            move = WEST;
        }
    }
    this->lastDirection = move;
    return move;
}

std::string Ant::getType() const {
    return "Ant";
}

std::string Ant::toString() {
    return "%";
}