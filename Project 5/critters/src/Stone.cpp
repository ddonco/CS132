/*
 * Critters
 * A Stone object is displayed as S and always stays put.
 * It always picks ROAR in a fight.
 */

#include "Stone.h"

Stone::Stone() {
    // empty
}

Attack Stone::fight(std::string) {
    return ROAR;
}

std::string Stone::getColor() {
    return "gray";
}

std::string Stone::getType() const {
    return "Stone";
}

std::string Stone::toString() {
    return "S";
}
