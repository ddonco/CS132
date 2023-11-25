#ifndef _DRAGONFLY_H
#define _DRAGONFLY_H

using namespace std;

#include "Critter.h"

class Dragonfly : public Critter {
public:
    Dragonfly();
    virtual string getType() const override;
    virtual bool eat() override;
    virtual Direction getMove() override;

private:
    int eatCount;
    int moveCount;
    Direction lastDir;
    bool repeat;
};

#endif