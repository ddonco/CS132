/*
 * Critters
 * These are utility types used by your classes and our system.
 *
 * DO NOT MODIFY THIS FILE!
 *
 * @version 2021/04/11
 * - initial C++ version for 21sp
 */

#include "crittertypes.h"

std::string to_string(Attack attack) {
    switch (attack) {
        case FORFEIT: return "FORFEIT";
        case ROAR:    return "ROAR";
        case POUNCE:  return "POUNCE";
        case SCRATCH: return "SCRATCH";
        default:      return "unknown";
    }
}
int ATTACK_COUNT = 4;

std::string to_string(Direction direction) {
    switch (direction) {
        case CENTER: return "CENTER";
        case NORTH:  return "NORTH";
        case EAST:   return "EAST";
        case SOUTH:  return "SOUTH";
        case WEST:   return "WEST";
        default:     return "unknown";
    }
}
int DIRECTION_COUNT = 5;
