/*
 * Critters
 * A Stone object is displayed as S and always stays put.
 * It always picks ROAR in a fight.
 */

#ifndef _BUMBLEBEE_H
#define _BUMBLEBEE_H

#include "Critter.h"

class Bumblebee : public Critter {
public:
    Bumblebee();
    virtual std::string getColor() override;
    virtual Direction getMove() override;
    virtual std::string getType() const override;
    virtual std::string toString() override;

private:
    Direction lastDirection;
    int currentSteps;
    int totalSteps;
};

#endif