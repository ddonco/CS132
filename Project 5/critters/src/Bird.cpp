/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #5, 02/15/23

 A Bird object is displayed as either a "^", ">", "v", or "<" depending on which
 direction the object is moving. A Bird moves in a repeating square pattern in a
 clockwise direction with 3 moves in each direction before changing.
 A Bird picks Roar in a fight if the opponent looks like "%", otherwise it Pounces.
 A Bird never eats when it finds food and the Bird has the color blue.
 */

#include "Bird.h"

Bird::Bird() : lastDirection(NORTH), moveCount(0) {}

bool Bird::eat() {
    return false;
}

Attack Bird::fight(std::string opponent) {
    if (opponent == "%") {
        return ROAR;
    }
    return POUNCE;
}

std::string Bird::getColor() {
    return "blue";
}

Direction Bird::getMove() {
    Direction move = this->lastDirection;
    if (this->moveCount > 3) {
        this->moveCount = 0;
        if (this->lastDirection == NORTH) {
            move = EAST;
        } else if (this->lastDirection == EAST) {
            move = SOUTH;
        } else if (this->lastDirection == SOUTH) {
            move = WEST;
        } else {
            move = NORTH;
        }
    }
    this->lastDirection = move;
    this->moveCount++;
    return move;
}

std::string Bird::getType() const {
    return "Bird";
}

std::string Bird::toString() {
    if (this->lastDirection == EAST) {
        return ">";
    } else if (this->lastDirection == SOUTH) {
        return "V";
    } else if (this->lastDirection == WEST) {
        return "<";
    } else {
        return "^";
    }
}