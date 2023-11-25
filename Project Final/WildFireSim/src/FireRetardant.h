/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The FireRetardant class represents a square meter of land containing a fuel source has been
treated with a fire retardant in a simulated environment. The environment is intended to simulate
a forest in which a wildfire is spreading, therefore the properties and member functions of the
class are related to fire spreading characteristics.
*/

#ifndef _FIRERETARDANT_H
#define _FIRERETARDANT_H

#include "Countermeasure.h"
#include "Utilities.h"

using namespace std;

class FireRetardant : public Countermeasure {
public:
    /**
     * @brief FireRetardant Sets the intial properties of a FireRetardant Object
     * @param temperature The FireRetardant object's temperature
     * @param windSpeed The FireRetardant object's wind speed
     * @param windDirection The FireRetardant object's wind direction
     */
    FireRetardant(double temperature, double windSpeed, Direction windDirection);

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
};

#endif
