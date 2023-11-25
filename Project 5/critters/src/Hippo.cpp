/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #5, 02/15/23

 A Hippo object is displayed as a number representing the level of hunger
 of the Hippo. As the Hippo eats food the number decreases until it reaches
 0 and remains at 0, at which point the Hippo will no longer eat. A Hippo is
 gray in color while it is still hungry and becomes white once hunger has reached
 0. A Hippo moved 5 steps in a random direction, then choses a new random direction
 and again moves 5 steps, and so on. A Hippo picks Scratch as its fighting
 behavior if it is hungry, otherwise it chooses Pounce. A hippo eats until its hunger
 has reached 0.
 */

#include <vector>

#include "Hippo.h"

Hippo::Hippo(int hunger) : direction(CENTER), moveCount(5),
                           hunger(hunger) {}

bool Hippo::eat() {
    if (this->hunger > 0) {
        this->hunger--;
        return true;
    }
    return false;
}

Attack Hippo::fight(std::string) {
    if (this->hunger > 0) {
        return SCRATCH;
    }
    return POUNCE;
}

std::string Hippo::getColor() {
    if (this->hunger > 0) {
        return "gray";
    }
    return "white";
}
Direction Hippo::getMove() {
    if (this->moveCount >= 5) {
        this->moveCount = 0;
        std::vector<Direction> directions = {NORTH, EAST, SOUTH, WEST};
        int r = rand() % directions.size();
        this->direction = directions[r];
        return this->direction;
    }
    this->moveCount++;
    return this->direction;
}

std::string Hippo::getType() const {
    return "Hippo";
}

std::string Hippo::toString() {
    return std::to_string(this->hunger);
}