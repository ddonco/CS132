#include <vector>

#include "Cat.h"

Cat::Cat(bool wanderWest) : wanderWest(wanderWest), direction(CENTER), runCount(0), walkCount(0),
                            scared(false), hunting(false), huntingCount(0) {}

bool Cat::eat() {
    if (this->scared) {
        return false;
    }
    this->hunting = true;
    return true;
}

Attack Cat::fight(std::string) {
    if (this->scared) {
        return SCRATCH;
    } else if (this->hunting) {
        return POUNCE;
    } else {
        return ROAR;
    }
}

std::string Cat::getColor() {
    if (this->scared) {
        return "white";
    }
    return "orange";
}
Direction Cat::getMove() {
    std::vector<Direction> directions = {NORTH, EAST, SOUTH, WEST};
    if (this->scared && this->runCount < 9) {
        this->runCount++;
        return this->direction;
    } else if (this->scared) {
        this->runCount = 0;
        this->scared = false;
        return CENTER;
    } else if (this->hunting && this->huntingCount < 49) {
        this->huntingCount++;
        for (int i = 0; i < directions.size(); i++) {
            if (getNeighbor(directions[i]) != " " && getNeighbor(directions[i]) != ".") {
                this->hunting = false;
                this->huntingCount = 0;
                return directions[i];
            }
        }
        return CENTER;
    } else {
        this->hunting = false;
        this->huntingCount = 0;
        if (this->walkCount < 9) {
            this->walkCount++;
            return directions[walkCount % 2];
        } else {
            this->scared = true;
            this->walkCount = 0;
            int r = rand() % directions.size();
            this->direction = directions[r];
            return this->direction;
        }
    }
}

std::string Cat::getType() const {
    return "Cat";
}

std::string Cat::toString() {
    if (this->scared) {
        return "*";
    } else if (this->hunting) {
        return "H";
    }
    return "C";
}