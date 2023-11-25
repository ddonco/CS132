/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Meter class represents a square meter of land in a simulated environment. The
environment is intended to simulate the spread of a wildfire, therefore the properties
and member functions of the class are related to fire spreading characteristics.
*/

#include "Meter.h"

const double Meter::MAX_TEMP = 100;
const double Meter::MAX_WINDSPEED = 100;

Meter::Meter(double temperature,
             double windSpeed,
             Direction windDirection) : temperature(temperature),
                                        windSpeed(windSpeed),
                                        windDirection(windDirection),
                                        fuelRemaining(100) {}

Meter::~Meter() {}

MeterType Meter::getType() const {
    return METER;
}

string Meter::toString() const {
    return "Meter";
}

string Meter::getColor() const {
    return "white";
}

double Meter::getTemperature() const {
    return temperature;
}

Direction Meter::getWindDirection() const {
    return windDirection;
}

double Meter::getWindSpeed() const {
    return windSpeed;
}

void Meter::setWindDirection(Direction d) {
    windDirection = d;
}
void Meter::setWindSpeed(double speed) {
    windSpeed = speed;
}

bool Meter::atCombustion() const {
    return false;
}

double Meter::getFuelRemaining() const {
    return fuelRemaining;
}

double Meter::spread(Direction) {
    return 0;
}

void Meter::update(double spreadFactor) {
    temperature *= spreadFactor + 1;
}