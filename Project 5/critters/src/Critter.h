/*
 * Critters
 * This class defines the methods necessary for an animal to be part of the simulation.
 * Your critter animal classes extend this class to add to its basic functionality.
 *
 * DO NOT MODIFY THIS FILE!
 *
 * @version 2021/04/11
 * - initial C++ version for 21sp
 */

#ifndef _CRITTER_H
#define _CRITTER_H

#include "crittertypes.h"
#include "CritterBase.h"
#include <string>

class Critter : public CritterBase {
    // The following five methods are the ones you must implement for your assignment.
public:
    virtual bool eat();
    virtual Attack fight(std::string opponent);
    virtual std::string getColor();
    virtual Direction getMove();
    virtual std::string getType() const = 0;
    virtual std::string toString();
};

#endif // _CRITTER_H
