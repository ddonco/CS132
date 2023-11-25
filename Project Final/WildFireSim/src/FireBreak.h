/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The FireBreak class represents a square meter of land containing a fire break intentended to
prevent the spread of fire in a simulated environment. The environment is intended to simulate
a forest in which a wildfire is spreading, therefore the properties and member functions of the
class are related to fire spreading characteristics.
*/

#ifndef _FIREBREAK_H
#define _FIREBREAK_H

#include "Countermeasure.h"
#include "Utilities.h"

using namespace std;

class FireBreak : public Countermeasure {
public:
    /**
     * @brief FireBreak Sets the intial properties of a FireBreak Object
     * @param temperature The FireBreak object's temperature
     * @param windSpeed The FireBreak object's wind speed
     * @param windDirection The FireBreak object's wind direction
     */
    FireBreak(double temperature, double windSpeed, Direction windDirection);
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
    atCombustion always returns false because a FireBreak cannot catch fire.
    Parameters:
        none
    Return
        atCombustion    bool    False.
    */
    virtual bool atCombustion() const override;
};

#endif
