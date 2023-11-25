/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #5, 02/15/23

 A Bird object is displayed as either a "^", ">", "v", or "<" depending on which
 direction the object is moving. A Bird moves in a repeating square pattern in a
 clockwise direction with 3 moves in each direction before changing.
 A Bird picks Roar in a fight if the opponent looks like "%", otherwise it Pounces.
 A Bird never eats when it finds food and the Bird has the color blue.
 */

#ifndef _BIRD_H
#define _BIRD_H

#include "Critter.h"

class Bird : public Critter {
public:
    /*
    The Bird constructor initializes member variables for a Bird object.
    Parameters:
        none
    */
    Bird();
    /*
    eat is called to determine if the object will eat when it finds food. The Bird
    always return false and therefore never eats.
    Parameters:
        none
    Returns:
        eat     bool    Always false.
    */
    virtual bool eat() override;
    /*
    fight is called to determine the fighting behavior of the object. The Bird
    returns the ROAR behavior when the passed in opponent looks like "%", otherwise
    it returns POUNCE.
    Parameters:
        none
    Returns:
        behavior    Attack  ROAR if opponent == "%", otherwise POUNCE.
    */
    virtual Attack fight(std::string opponent) override;
    /*
    getColor is used to get the color of the object. The Bird always returns
    the string "blue".
    Parameters:
        none
    Returns:
        color   string  Always "blue".
    */
    virtual std::string getColor() override;
    /*
    getMove is used to get the direction of movment of the object. The Bird first moves
    NORTH 3 spaces, then EAST 3 spaces, then SOUTH 3 spaces, then WEST 3 spaces, and repeats.
    Parameters:
        none
    Returns:
        direction   Direction   Returns N, then E, then S, then W, in a repeating clockwise square.
    */
    virtual Direction getMove() override;
    /*
    getType return the type of object, which is "Bird" for a Bird object.
    Parameters:
        none
    Returns:
        type    string  Always "Bird".
    */
    virtual std::string getType() const override;
    /*
    toString returns a string representation of the object. A Bird is represented
    by either a "^", ">", "v", or "<" depending on the direction of movement.
    Parameters:
        none
    Returns:
        type    string  Either a "^", ">", "v", or "<".
    */
    virtual std::string toString() override;

private:
    Direction lastDirection;
    int moveCount;
};

#endif