/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #5, 02/15/23

 A Cat object is displayed by one of three symbols depending on the current state of the Cat.
 A Cat is either in its normal state (C), or it can be hunting (H) or scared (*). The Cat moves
 either North-East or North-West depending on the value of the boolean wanderWest parameter
 in the constuctor. A Cat is in its normal state for 10 steps and then becomes scared. A Cat
 is then scared for 10 steps and returns to its normal state. A Cat will eat if its not scared,
 and eating will put the Cat into the hunting state. A Cat will remain in the hunting state
 for either 50 steps or until an opponent is detected next to the Cat. If an opponent is next
 to the Cat, the Cat will move in the direction of the opponent and resume its normal state.
 If a Cat is in its normal state, its fighting behavior is Roar, if its hunting its
 behavior is Pounce, and if its scared its behavior is Scratch. A Cat has the color orange
 when in its normal state or hunting, and is white when scared.

 */

#ifndef _CAT_H
#define _CAT_H

#include "Critter.h"

class Cat : public Critter {
public:
    /*
    The Cat constructor takes one argument that's used to define if the Cat will walk
    NE or NW using the wanderWest parameter.
    Parameters:
        wanderWest  bool    If true, the Cat will move NW, otherwise it will move NE.
    */
    Cat(bool wanderWest);
    /*
    eat is called to determine if the object will eat when it finds food. The Cat
    returns true when in its normal state. If its scared it returns false.
    Parameters:
        none
    Returns:
        eat     bool    False if scared, otherwise true.
    */
    virtual bool eat() override;
    /*
    fight is called to determine the fighting behavior of the object. The Cat
    returns ROAR if in its normal state, SCRATCH if its scared, or POUNCE
    if its hunting.
    Parameters:
        none
    Returns:
        behavior    Attack  SCRATCH if scared, POUNCE if hunting or ROAR otherwise.
    */
    virtual Attack fight(std::string) override;
    /*
    getColor is used to get the color of the object. The Car return the string "white"
    if its scared, otherwise returns "orange".
    Parameters:
        none
    Returns:
        color   string  "white" if scared, otherwise "orange".
    */
    virtual std::string getColor() override;
    /*
    getMove is used to get the direction of movment of the object. If the Cat is in its
    normal state, it will walk North-East or North-West depending on the value of
    wanderWest (wanderWest=true -> Cat moves NW). A Cat walks normally for 10 steps,
    then becomes scared. When a Cat is scared, it randomly chooses a new direction and
    moved 10 steps in that direction. After 10 steps the Car returns to its normal
    state. If a Cat is hunting, the Cat return remains still for 50 steps. While the
    Cat is hunting, if an opponent moves into a space directly next to the Cat, the
    Cat will move in the direction of the opponent and return to the normal state.
    Parameters:
        none
    Returns:
        direction   Direction   Returns N, then E, then N, then E... when in its normal
                                state and wanderWest is false. If wanderWest is true,
                                returns N, then W, then N, then W.... If hunting returns
                                CENTER. If scared a new direction is selected at random
                                and returns that direction.
    */
    virtual Direction getMove() override;
    /*
    getType return the type of object, which is "Cat" for a Cat object.
    Parameters:
        none
    Returns:
        type    string  Always "Cat".
    */
    virtual std::string getType() const override;
    /*
    toString returns a string representation of the object. A Cat is represented
    by an "C" in its normal state, "H" if its hunting, and "*" if its scared.
    Parameters:
        none
    Returns:
        type    string  "H" if its hunting, "*" if its scared, or "C" otherwise.
    */
    virtual std::string toString() override;

private:
    bool wanderWest;
    Direction direction;
    int runCount;
    int walkCount;
    bool scared;
    bool hunting;
    int huntingCount;
};

#endif