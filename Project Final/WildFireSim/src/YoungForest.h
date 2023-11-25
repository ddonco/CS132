/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/11/23

The Grass class represents a square meter of land containing young forest as a fuel source
in a simulated environment. The environment is intended to simulate a forest in which
a wildfire is spreading, therefore the properties and member functions of the class are
related to fire spreading characteristics.
*/

#ifndef _YOUNGFOREST_H
#define _YOUNGFOREST_H

#include "Fuel.h"

class YoungForest : public Fuel {
public:
    /**
     * @brief YoungForest Sets the intial properties of a YoungForest Object
     * @param temperature The YoungForest object's temperature
     * @param windSpeed The YoungForest object's wind speed
     * @param windDirection The YoungForest object's wind direction
     * @param combustionTemp The YoungForest object's combustion temperature
     */
    YoungForest(double temperature,
                double windSpeed,
                Direction windDirection,
                double combustionTemp);
    /*
    getType returns a MeterType enum of the object.
    Parameters:
    none
    Returns:
    meterType   MeterType   An enum representing the object type.
    */
    MeterType getType() const override;
    /*
    getColor returns the color of the object as a string.
    Parameters:
        none
    Return
        color   string      The color of the object.
    */
    string getColor() const override;
    /*
    getColor returns the type of the object as a string.
    Parameters:
        none
    Return
        type    string      The type of the object as a string.
    */
    string toString() const override;
};

#endif // _YOUNGFOREST_H
