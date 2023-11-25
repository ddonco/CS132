/*
 * Critters
 * These are utility types used by your classes and our system.
 *
 * DO NOT MODIFY THIS FILE!
 *
 * @version 2021/04/11
 * - initial C++ version for 21sp
 */

#ifndef _CRITTERTYPES_H
#define _CRITTERTYPES_H

#include <string>

enum Attack {
    FORFEIT,
    ROAR,
    POUNCE,
    SCRATCH
};
std::string to_string(Attack attack);
extern int ATTACK_COUNT;

enum Direction {
    CENTER,
    NORTH,
    EAST,
    SOUTH,
    WEST
};
std::string to_string(Direction direction);
extern int DIRECTION_COUNT;

#endif // _CRITTERTYPES_H
