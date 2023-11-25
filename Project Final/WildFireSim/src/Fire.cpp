/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Fire class represents a square meter of land containing a fuel source that has cought fire
in a simulated environment. The environment is intended to simulate a forest in which
a wildfire is spreading, therefore the properties and member functions of the class are
related to fire spreading characteristics.
*/

#include "Fire.h"

const double Fire::MAX_TEMP = 2000;

Fire::Fire(
    double temperature,
    double windSpeed,
    Direction windDirection) : Meter(temperature, windSpeed, windDirection),
                               fireTemperature(temperature),
                               fuelRemaining(100) {}

MeterType Fire::getType() const {
    return FIRE;
}

string Fire::toString() const {
    return "Fire";
}

string Fire::getColor() const {
    return "red";
}

double Fire::getTemperature() const {
    return fireTemperature;
}

double Fire::getFuelRemaining() const {
    return fuelRemaining;
}

double Fire::spread(Direction d) {
    double spreadMagnitudes = 0.25;
    if (getWindDirection() == d) {
        spreadMagnitudes *= getWindSpeed() / Meter::MAX_WINDSPEED + 1;
    }
    return spreadMagnitudes;
}

void Fire::update(double spreadFactor) {
    fireTemperature = min(fireTemperature + 100 * spreadFactor, MAX_TEMP);
    fuelRemaining = max(fuelRemaining - (fireTemperature / MAX_TEMP * 5), 0.0);
}