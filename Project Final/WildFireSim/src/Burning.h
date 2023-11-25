/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Burning class represents a square meter of land containing a fuel source that is actively
burning in a simulated environment. The environment is intended to simulate a forest in which
a wildfire is spreading, therefore the properties and member functions of the class are
related to fire spreading characteristics.
*/

/**
 * @file PerlinNoise.h
 * @brief A Class for generating Perlin noise. Largely based upon the wikipedia example.
 * @author Lucas Henderson & various wikipedia users (see page history)
 * @date 3/11/2023
 *
 *  https://en.wikipedia.org/wiki/Perlin_noise#Implementation
 *  Differences:
 *  * Has been refactored into a class
 *  * Uses a seedable PRNG
 */

#ifndef _BURNING_H
#define _BURNING_H

#include "Fire.h"
#include "Utilities.h"

using namespace std;

class Burning : public Fire {
public:
    /**
     * @brief Burning Sets the intial properties of a Burning Object
     * @param temperature The Burning object's temperature
     * @param windSpeed The Burning object's wind speed
     * @param windDirection The Burning object's wind direction
     */
    Burning(double temperature, double windSpeed, Direction windDirection);
    /*
    getType returns a MeterType enum of the object.
    Parameters:
        none
    Returns:
        meterType   MeterType   An enum representing the object type.
    */
    virtual MeterType getType() const override;
    /*
    getColor returns the type of the object as a string.
    Parameters:
        none
    Return
        type    string      The type of the object as a string.
    */
    virtual string toString() const override;
    /*
    getTemperature returns the temperature of the object.
    Parameters:
        none
    Return
        temperature     double      The temperature of the object.
    */
    virtual double getTemperature() const override;
    /*
    getFuelRemaining returns the remaining fuel percent of the object.
    Parameters:
        none
    Return
        fuelRemaining   double      The remaining fuel percent.
    */
    virtual double getFuelRemaining() const override;
    /*
    spread is used to calculate and return the magniture of temperature spread
    from this object with temperature being the driving factor of how the fire
    spreads. A Direction parameter is supplied to this function to specify the
    direction in which spread will be calculated. The spread magnitude is greatest
    in the direction of the wind of this object and least in the opposite
    direction of the wind. Note: wind direction is the direction from which the
    wind is coming, ex. a North wind comes from the North and blows South.
    Parameters:
        direction   Direction   The direction
    Return
        type    string      The type of the object as a string.
    */
    double spread(Direction d) override;
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
    // The temperature of the object.
    double burningTemperature;
    // The relative amount of fuel remaining of the object.
    double fuelRemaining;
};

#endif
