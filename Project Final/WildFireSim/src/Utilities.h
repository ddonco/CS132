#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <string>
#include <vector>

using namespace std;

// MeterType represents each of the possible classes that can exist in a wildfire simulation.
enum MeterType {
    METER,
    FUEL,
    GRASS,
    YOUNGFOREST,
    OLDFOREST,
    FIRE,
    BURNING,
    BURNT,
    COUNTERMEASURE,
    FIRERETARDANT,
    FIREBREAK,
    UNKNOWN
};

// Direction represents each of the cardinal directions.
enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NONE,
};
/*
toLowerCase returns the lower case version of the given string.
Parameters
    s           string      A string.
Returns:
    lower       string      The lower case version of the string.
*/
string toLowerCase(string s);
/*
getDirectionOffset returns a position offset as a row, column vector for a given direction.
For example, given north the row, column offset is {0, 1}.
Parameters
    d       Direction       The direction of the requested offset.
Returns:
    offset  vector<int>     The row, col offset of the direction.
*/
vector<int> getDirectionOffset(Direction d);
/*
getOppositDirection returns the opposite direction of the provided direction.
Parameters
    d           Direction       A direction.
Returns:
    opposite    Direction       The opposite direction of the given direction.
*/
Direction getOppositDirection(Direction d);
/*
directionFromString returns the Direction enum of the provided direction string.
Parameters
    d           string       A direction as a string.
Returns:
    direction   Direction    The corresponding enum direction.
*/
Direction directionFromString(string d);

#endif