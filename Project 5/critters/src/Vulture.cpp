/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #5, 02/15/23

 A Vulture object is displayed as either a "^", ">", "v", or "<" depending on which
 direction the object is moving. A Vulture moves in a repeating square pattern in the
 clockwise direction with 3 moves in each direction before changing.
 A Vulture picks Roar in a fight if the opponent looks like "%", otherwise it Pounces.
 The Vulture is black in color. A Vulture eats when its hungry, which is its initial
 state until it first eats. A Vulture will become hungry again after fighting.
 */

#include "Vulture.h"

Vulture::Vulture() : lastDirection(NORTH), moveCount(0), hungry(true) {}

bool Vulture::eat() {
    if (this->hungry) {
        this->hungry = false;
        return true;
    }
    return false;
}

Attack Vulture::fight(std::string opponent) {
    if (opponent == "%") {
        this->hungry = true;
        return ROAR;
    }
    return POUNCE;
}

std::string Vulture::getColor() {
    return "black";
}

std::string Vulture::getType() const {
    return "Vulture";
}