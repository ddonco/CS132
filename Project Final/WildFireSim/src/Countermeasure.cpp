/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Countermeasure class represents a square meter of land containing some sort of fire
fighting countermeasure in a simulated environment. The environment is intended to simulate
a forest in which a wildfire is spreading, therefore the properties and member functions of the
class are related to fire spreading characteristics.
*/

#include "Countermeasure.h"

const double Countermeasure::COUNTERMEASURE_TEMP_INCREMENT = 10;

Countermeasure::Countermeasure(
    double temperature,
    double windSpeed,
    Direction windDirection) : Meter(temperature, windSpeed, windDirection),
                               counterTemperature(temperature),
                               fuelRemaining(100),
                               combustionTemp(1000) {}

MeterType Countermeasure::getType() const {
    return COUNTERMEASURE;
}

string Countermeasure::toString() const {
    return "Countermeasure";
}

string Countermeasure::getColor() const {
    return "black";
}

double Countermeasure::getTemperature() const {
    return counterTemperature;
}

bool Countermeasure::atCombustion() const {
    return counterTemperature >= combustionTemp;
}

void Countermeasure::update(double spreadFactor) {
    counterTemperature += COUNTERMEASURE_TEMP_INCREMENT * spreadFactor;
}
