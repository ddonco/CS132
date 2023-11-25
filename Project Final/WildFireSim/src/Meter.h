/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Meter class represents a square meter of land in a simulated environment. The
environment is intended to simulate the spread of a wildfire, therefore the properties
and member functions of the class are related to fire spreading characteristics.
*/

#ifndef _METER_H
#define _METER_H

#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace std;

class Meter {
public:
    // Stores the maximum temperature of a Meter.
    static const double MAX_TEMP;
    // Stores the maximum wind speed of a Meter.
    static const double MAX_WINDSPEED;

    /**
     * @brief Meter Sets the intial properties of a Meter Object
     * @param temperature The Meter object's temperature
     * @param windSpeed The Meter object's wind speed
     * @param windDirection The Meter object's wind direction
     */
    Meter(double temperature, double windSpeed, Direction windDirection);
    /*
    A virtual Meter destructure is declared to handle possible undefined behavior when deleteing
    a sub-class of the polymorphic Meter class.
    */
    virtual ~Meter();
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
    virtual double getTemperature() const;
    /*
    getWindDirection returns the wind direction of the object.
    Parameters:
        none
    Return
        windDirection   Direction   The wind direction of the object.
    */
    virtual Direction getWindDirection() const;
    /*
    getWindSpeed returns the wind speed of the object.
    Parameters:
        none
    Return
        windSpeed   double      The wind speed of the object.
    */
    virtual double getWindSpeed() const;
    /*
    setWindDirection sets the wind direction of the object.
    Parameters:
        windDirection   Direction   The wind direction of the object.
    Return
        none
    */
    virtual void setWindDirection(Direction d);
    /*
    setWindSpeed sets the wind speed of the object.
    Parameters:
        windSpeed   double      The wind speed of the object.
    Return
        none
    */
    virtual void setWindSpeed(double speed);
    /*
    atCombustion returns false because a Meter object cannot catch fire.
    Parameters:
        none
    Return
        atCombustion    bool    False.
    */
    virtual bool atCombustion() const;
    /*
    getFuelRemaining returns the remaining fuel percent of the object.
    Parameters:
        none
    Return
        fuelRemaining   double      The remaining fuel percent.
    */
    virtual double getFuelRemaining() const;
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
    virtual double spread(Direction);
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
    virtual void update(double spreadMagniture);

private:
    // The temperature of the object.
    double temperature;
    // The windspeed of the object.
    double windSpeed;
    // The wind direction of the object.
    Direction windDirection;
    // The relative amount of fuel remaining of the object.
    double fuelRemaining;
};

#endif
