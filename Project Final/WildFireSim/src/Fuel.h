/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Fuel class represents a square meter of land containing some sort of fuel source
in a simulated environment. The environment is intended to simulate a forest in which
a wildfire is spreading, therefore the properties and member functions of the class are
related to fire spreading characteristics.
*/

#ifndef _FUEL_H
#define _FUEL_H

#include "Meter.h"
#include "Utilities.h"

using namespace std;

class Fuel : public Meter {
public:
    /**
     * @brief Fuel Sets the intial properties of a Fuel Object
     * @param temperature The fuel object's temperature
     * @param windSpeed The fuel object's wind speed
     * @param windDirection The fuel object's wind direction
     * @param combustionTemp The fuel object's combustion temperature
     */
    Fuel(double temperature, double windSpeed, Direction windDirection, double combustionTemp);

    /**
     * @brief getType provides the type of the object
     * @return An enum representing the object type.
     */
    virtual MeterType getType() const override;

    /**
     * @brief getColor Returns the color of the object as a string.
     * @return Color of the object as a string
     */
    virtual string getColor() const override;

    /**
     * @brief toString Returns the type of the object as a string.
     * @return Type of the object as a string
     */
    virtual string toString() const override;

    /**
     * @brief getTemperature Returns the temperature of the object.
     * @return The temperature of the object as a double.
     */
    virtual double getTemperature() const override;

    /**
     * @brief atCombustion Tests whether or not the current temperature of the object
    is at or above the combustion temperature of the object.
     * @return True if temperature >= combustion temperature.
     */
    virtual bool atCombustion() const override;
    /**
     * @brief update Used to modify the temperature and fuel remaining of the object.
    The updated temperature is calculated based on the current temperature and the
    spread magniture passed in to the function. Fuel remaining is updated based on
    the temperature of the object.
     * @param spreadFactor The magnitude of spread applied to this object.
     */
    virtual void update(double spreadFactor) override;

private:
    static const double FUEL_TEMPERATURE_INCREMENT;
    // The temperature of the object.
    double fuelTemperature;
    // The windspeed of the object.
    double fuelRemaining;
    // The wind direction of the object.
    double combustionTemp;
};

#endif
