/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Fuel class represents a square meter of land containing some sort of fuel source
in a simulated environment. The environment is intended to simulate a forest in which
a wildfire is spreading, therefore the properties and member functions of the class are
related to fire spreading characteristics.
*/

#include "Fuel.h"

const double Fuel::FUEL_TEMPERATURE_INCREMENT = 20;

Fuel::Fuel(double temperature,
           double windSpeed,
           Direction windDirection,
           double combustionTemp) : Meter(temperature, windSpeed, windDirection),
                                    fuelTemperature(temperature),
                                    fuelRemaining(100),
                                    combustionTemp(combustionTemp) {}

MeterType Fuel::getType() const {
    return FUEL;
}

string Fuel::toString() const {
    return "Fuel";
}

string Fuel::getColor() const {
    return "green";
}

double Fuel::getTemperature() const {
    return fuelTemperature;
}

bool Fuel::atCombustion() const {
    return fuelTemperature >= combustionTemp;
}

void Fuel::update(double spreadFactor) {
    fuelTemperature += FUEL_TEMPERATURE_INCREMENT * spreadFactor;
}
