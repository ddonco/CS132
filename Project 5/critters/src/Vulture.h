/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #5, 02/15/23

 A Vulture object is displayed as either a "^", ">", "v", or "<" depending on which
 direction the object is moving. A Vulture moves in a repeating square pattern in the
 clockwise direction with 3 moves in each direction before changing.
 A Vulture picks Roar in a fight if the opponent looks like "%", otherwise it Pounces.
 The Vulture is black in color. A Vulture eats when its hungry, which is its initial
 state until it first eats. A Vulture will become hungry again after fighting.
 */

#ifndef _VULTURE_H
#define _VULTURE_H

#include "Bird.h"

class Vulture : public Bird {
public:
    Vulture();
    /*
    eat is called to determine if the object will eat when it finds food. The Vulture
    is initially hungry and remains hungry until it first eats and returns true. After
    first eating eat will return false until the Vulture becomes hungry again at which
    point eat will return true again.
    Parameters:
        none
    Returns:
        eat     bool    Only return true if the Vulture is hungry, otherwise false.
    */
    virtual bool eat() override;
    /*
    fight is called to determine the fighting behavior of the object. The Vulture
    returns the ROAR behavior when the passed in opponent looks like "%", otherwise
    it returns POUNCE. Every time the Vulture fights, the Vulture becomes hungry again
    and the hungry member variable is set to true.
    Parameters:
        none
    Returns:
        behavior    Attack  ROAR if opponent == "%", otherwise POUNCE.
    */
    virtual Attack fight(std::string opponent) override;
    /*
    getColor is used to get the color of the object. The Vulture always returns
    the string "black".
    Parameters:
        none
    Returns:
        color   string  Always "black".
    */
    virtual std::string getColor() override;
    /*
    getType return the type of object, which is "Vulture" for an Vulture object.
    Parameters:
        none
    Returns:
        type    string  Always "Vulture".
    */
    virtual std::string getType() const override;

private:
    Direction lastDirection;
    int moveCount;
    bool hungry;
};

#endif