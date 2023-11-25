/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Burnt class represents a square meter of land containing a fuel source that is now
burnt in a simulated environment. The environment is intended to simulate a forest in which
a wildfire is spreading, therefore the properties and member functions of the class are
related to fire spreading characteristics.
*/

#include "Burnt.h"

Burnt::Burnt(
    double temperature,
    double windSpeed,
    Direction windDirection) : Fire(temperature, windSpeed, windDirection),
                               burntTemperature(temperature),
                               fuelRemaining(0) {}

MeterType Burnt::getType() const {
    return BURNT;
}

string Burnt::toString() const {
    return "Burnt";
}

string Burnt::getColor() const {
    return "gray";
}

double Burnt::getTemperature() const {
    return burntTemperature;
}

double Burnt::getFuelRemaining() const {
    return fuelRemaining;
}

double Burnt::spread(Direction) {
    return 0;
}

void Burnt::update(double) {
    this->burntTemperature = max(burntTemperature - 25, 150.0);
}