/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The FireBreak class represents a square meter of land containing a fire break intentended to
prevent the spread of fire in a simulated environment. The environment is intended to simulate
a forest in which a wildfire is spreading, therefore the properties and member functions of the
class are related to fire spreading characteristics.
*/

#include "FireBreak.h"

FireBreak::FireBreak(
    double temperature,
    double windSpeed,
    Direction windDirection) : Countermeasure(temperature, windSpeed, windDirection) {}

MeterType FireBreak::getType() const {
    return FIREBREAK;
}

string FireBreak::toString() const {
    return "FireBreak";
}

string FireBreak::getColor() const {
    return "brown";
}

bool FireBreak::atCombustion() const {
    return false;
}