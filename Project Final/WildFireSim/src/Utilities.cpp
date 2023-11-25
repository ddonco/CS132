#include "Utilities.h"

string toLowerCase(string s) {
    string lower;
    for (char c : s) {
        lower.append(string(1, tolower(c)));
    }
    return lower;
}

vector<int> getDirectionOffset(Direction d) {
    if (d == NORTH) {
        return {1, 0};
    } else if (d == EAST) {
        return {0, 1};
    } else if (d == SOUTH) {
        return {-1, 0};
    } else if (d == WEST) {
        return {0, -1};
    } else {
        return {0, 0};
    }
}

Direction getOppositDirection(Direction d) {
    if (d == NORTH) {
        return SOUTH;
    } else if (d == EAST) {
        return WEST;
    } else if (d == SOUTH) {
        return NORTH;
    } else if (d == WEST) {
        return EAST;
    } else {
        return NONE;
    }
}

Direction directionFromString(string d) {
    d = toLowerCase(d);
    if (d == "north") {
        return NORTH;
    } else if (d == "east") {
        return EAST;
    } else if (d == "south") {
        return SOUTH;
    } else if (d == "west") {
        return WEST;
    } else {
        return NONE;
    }
}