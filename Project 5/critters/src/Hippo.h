/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #5, 02/15/23

 A Hippo object is displayed as a number representing the level of hunger
 of the Hippo. As the Hippo eats food the number decreases until it reaches
 0 and remains at 0, at which point the Hippo will no longer eat. A Hippo is
 gray in color while it is still hungry and becomes white once hunger has reached
 0. A Hippo moved 5 steps in a random direction, then choses a new random direction
 and again moves 5 steps, and so on. A Hippo picks Scratch as its fighting
 behavior if it is hungry, otherwise it chooses Pounce. A hippo eats until its hunger
 has reached 0.
 */

#ifndef _HIPPO_H
#define _HIPPO_H

#include "Critter.h"

class Hippo : public Critter {
public:
    /*
    The Hippo constructor takes one integer parameter specifying the level of hunger
    of the Hippo, in other words, the amount of food the Hippo can/will eat.
    Parameters:
        hunger      int     The amount of food the Hippo can eat to eat.
    */
    Hippo(int hunger);
    /*
    eat is called to determine if the object will eat when it finds food. The Hippo
    returns true if hunger is greater than 0, otherwise returns false.
    Parameters:
        none
    Returns:
        eat     bool    True if hunger is greater than 0, otherwise false.
    */
    virtual bool eat() override;
    /*
    fight is called to determine the fighting behavior of the object. The Hippo
    returns SCRATCH if hunger is greater than 0, otherwise returns POUNCE.
    Parameters:
        none
    Returns:
        behavior    Attack  returns SCRATCH if hunger is greater than 0, otherwise returns POUNCE.
    */
    virtual Attack fight(std::string) override;
    /*
    getColor is used to get the color of the object. The Hippo returns "gray" if
    hunger is greater than 0, otherwise returs "white".
    Parameters:
        none
    Returns:
        color   string  Returns "gray" if hunger is greater than 0, otherwise returs "white".
    */
    virtual std::string getColor() override;
    /*
    getMove is used to get the direction of movment of the object. The Hippo randomly
    selects a direction to move, then moves 5 spaces, then repeats.
    Parameters:
        none
    Returns:
        direction   Direction   Returns NORTH, EAST, SOUTH, or WEST 5 times in a row then
                                changes to a new random direction and repeats that one 5 times.
    */
    virtual Direction getMove() override;
    /*
    getType return the type of object, which is "Hippo" for a Hippo object.
    Parameters:
        none
    Returns:
        type    string  Always "Hippo".
    */
    virtual std::string getType() const override;
    /*
    toString returns a string representation of the object. A Hippo is displayed as a number
    representing the amount of food the Hippo will eat.
    Parameters:
        none
    Returns:
        type    string  A number representing the amount of food the Hippo will eat.
    */
    virtual std::string toString() override;
    /*
    isHungry returns a boolean value of whether or not the Hippo is still hungry,
    in other words, if hunger is greater than 0.
    Parameters:
        none
    Returns
        isHungry    bool    True if hunger is greater than 0, otherwise false.
    */
    // bool isHungry() const;

private:
    Direction direction;
    int moveCount;
    int hunger;
};

#endif