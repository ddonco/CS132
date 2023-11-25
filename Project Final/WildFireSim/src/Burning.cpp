/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Burning class represents a square meter of land containing a fuel source that is actively
burning in a simulated environment. The environment is intended to simulate a forest in which
a wildfire is spreading, therefore the properties and member functions of the class are
related to fire spreading characteristics.
*/

#include "Burning.h"

Burning::Burning(
    double temperature,
    double windSpeed,
    Direction windDirection) : Fire(temperature, windSpeed, windDirection),
                               burningTemperature(temperature),
                               fuelRemaining(100) {}

MeterType Burning::getType() const {
    return BURNING;
}

string Burning::toString() const {
    return "Burning";
}

double Burning::getTemperature() const {
    return burningTemperature;
}

double Burning::getFuelRemaining() const {
    return fuelRemaining;
}

double Burning::spread(Direction d) {
    double spreadMagnitudes = burningTemperature / MAX_TEMP;
    if (getWindDirection() == d) {
        spreadMagnitudes *= getWindSpeed() / Meter::MAX_WINDSPEED + 1;
    } else if (getWindDirection() == getOppositDirection(d)) {
        spreadMagnitudes *= (1 - getWindSpeed() / Meter::MAX_WINDSPEED) * 0.7;
    }
    return spreadMagnitudes;
}

void Burning::update(double spreadFactor) {
    burningTemperature = min(burningTemperature + 40 * spreadFactor, Fire::MAX_TEMP);
    fuelRemaining = max(fuelRemaining - (burningTemperature / MAX_TEMP + 1), 0.0);
}
