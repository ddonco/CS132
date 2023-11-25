/*
 * Critters
 * A Stone object is displayed as S and always stays put.
 * It always picks ROAR in a fight.
 */

#ifndef _STONE_H
#define _STONE_H

#include "Critter.h"

class Stone : public Critter {
public:
    Stone();
    virtual Attack fight(std::string) override;
    virtual std::string getColor() override;
    virtual std::string getType() const override;
    virtual std::string toString() override;
};

#endif // _STONE_H
