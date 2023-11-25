/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Grass class represents a square meter of land containing young forest as a fuel source
in a simulated environment. The environment is intended to simulate a forest in which
a wildfire is spreading, therefore the properties and member functions of the class are
related to fire spreading characteristics.
*/

#include "YoungForest.h"

YoungForest::YoungForest(double temperature,
                         double windSpeed,
                         Direction windDirection,
                         double combustionTemp) : Fuel(temperature,
                                                       windSpeed,
                                                       windDirection,
                                                       combustionTemp) {}

MeterType YoungForest::getType() const {
    return YOUNGFOREST;
}

string YoungForest::toString() const {
    return "YoungForest";
}

string YoungForest::getColor() const {
    return "#195900";
}
