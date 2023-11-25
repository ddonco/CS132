/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The FireRetardant class represents a square meter of land containing a fuel source has been
treated with a fire retardant in a simulated environment. The environment is intended to simulate
a forest in which a wildfire is spreading, therefore the properties and member functions of the
class are related to fire spreading characteristics.
*/

#include "FireRetardant.h"

FireRetardant::FireRetardant(
    double temperature,
    double windSpeed,
    Direction windDirection) : Countermeasure(temperature, windSpeed, windDirection) {}

MeterType FireRetardant::getType() const {
    return FIRERETARDANT;
}

string FireRetardant::toString() const {
    return "FireRetardant";
}

string FireRetardant::getColor() const {
    return "orange";
}