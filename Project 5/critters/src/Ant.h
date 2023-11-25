/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #5, 02/15/23

An Ant object is displayed as an "%" and is the color red. It walks either
north-east or south-east depending on the value of the walkSouth bool
parameter passed in to the constuctor. An Ant always picks Scratch in a
fight and always eats when it find food.
*/

#ifndef _ANT_H
#define _ANT_H

#include "Critter.h"

class Ant : public Critter {
public:
    /*
    The Ant constructor takes one argument thats used to define if the Ant will walk
    NE or SE using the walkSouth parameter.
    Parameters:
        walkSouth   bool    If true, the Ant will walk SE, otherwise it will walk NE.
    */
    Ant(bool walkSouth);
    /*
    eat is called to determine if the object will eat when it finds food. The Ant
    always return true and therefore always eats.
    Parameters:
        none
    Returns:
        eat     bool    Always true.
    */
    virtual bool eat() override;
    /*
    fight is called to determine the fighting behavior of the object. The Ant
    always returns the SCRATCH behavior.
    Parameters:
        none
    Returns:
        behavior    Attack  Always SCRATCH.
    */
    virtual Attack fight(std::string) override;
    /*
    getColor is used to get the color of the object. The Ant always returns
    the string "red".
    Parameters:
        none
    Returns:
        color   string  Always "red".
    */
    virtual std::string getColor() override;
    /*
    getMove is used to get the direction of movment of the object. If the walkSouth
    member variable is true, getMove first returns S, then E, then S, then E, and so on.
    If walkSouth is false, get move return N, then E, then N, then E, and so on.
    Parameters:
        none
    Returns:
        direction   Direction   Returns directions in the repeating pattern of S, E, S, E...
                                if the walkSouth member variable is true. If walkSouth is
                                false this function will return the repeating pattern of
                                N, E, N, E....
    */
    virtual Direction getMove() override;
    /*
    getType return the type of object, which is "Ant" for an Ant object.
    Parameters:
        none
    Returns:
        type    string  Always "Ant".
    */
    virtual std::string getType() const override;
    /*
    toString returns a string representation of the object. An Ant is represented
    by an "%".
    Parameters:
        none
    Returns:
        type    string  Always "%".
    */
    virtual std::string toString() override;

private:
    bool walkSouth;
    Direction lastDirection;
};

#endif