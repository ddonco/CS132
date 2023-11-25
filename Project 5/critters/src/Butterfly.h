/*
 * Critters
 * A Stone object is displayed as S and always stays put.
 * It always picks ROAR in a fight.
 */

#ifndef _BUTTERFLY_H
#define _BUTTERFLY_H

#include "Critter.h"

class Butterfly : public Critter {
public:
    Butterfly();
    virtual std::string getColor() override;
    virtual Direction getMove() override;
    virtual std::string getType() const override;
    virtual std::string toString() override;

private:
    Direction lastDirection;
    bool flap;
    int dir;
};

#endif