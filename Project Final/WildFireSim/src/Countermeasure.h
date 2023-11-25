/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Countermeasure class represents a square meter of land containing some sort of fire
fighting countermeasure in a simulated environment. The environment is intended to simulate
a forest in which a wildfire is spreading, therefore the properties and member functions of the
class are related to fire spreading characteristics.
*/

#ifndef _COUNTERMEASURE_H
#define _COUNTERMEASURE_H

#include "Meter.h"
#include "Utilities.h"

using namespace std;

class Countermeasure : public Meter {
public:
    static const double TEMPERATURE_CHANGE_FACTOR;

public:
    /**
     * @brief Countermeasure Sets the intial properties of a Countermeasure Object
     * @param temperature The Countermeasure object's temperature
     * @param windSpeed The Countermeasure object's wind speed
     * @param windDirection The Countermeasure object's wind direction
     */
    Countermeasure(double temperature, double windSpeed, Direction windDirection);
    /*
    getType returns a MeterType enum of the object.
    Parameters:
        none
    Returns:
        meterType   MeterType   An enum representing the object type.
    */
    virtual MeterType getType() const;
    /*
    getColor returns the color of the object as a string.
    Parameters:
        none
    Return
        color   string      The color of the object.
    */
    virtual string getColor() const;
    /*
    getColor returns the type of the object as a string.
    Parameters:
        none
    Return
        type    string      The type of the object as a string.
    */
    virtual string toString() const;
    /*
    getTemperature returns the temperature of the object.
    Parameters:
        none
    Return
        temperature     double      The temperature of the object.
    */
    virtual double getTemperature() const override;
    /*
    atCombustion tests whether or not the current temperature of the object
    is at or above the combustion temperature of the object.
    Parameters:
        none
    Return
        atCombustion    bool    True if temperature >= combustion temperature.
    */
    virtual bool atCombustion() const override;
    /*
    update is used to modify the temperature and fuel remaining of the object.
    The updated temperature is calculated based on the current temperature and the
    spread magniture passed in to the function. Fuel remaining is updated based on
    the temperature of the object.
    Parameters:
        spreadMagnitude     double  The magnitude of spread applied to this object.
    Return
        none
    */
    virtual void update(double spreadFactor) override;

private:
    static const double COUNTERMEASURE_TEMP_INCREMENT;
    double counterTemperature;
    double fuelRemaining;
    double combustionTemp;
};

#endif
