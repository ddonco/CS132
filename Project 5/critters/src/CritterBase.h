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

#ifndef _CRITTERBASE_H
#define _CRITTERBASE_H

#include "crittertypes.h"
#include <string>

class CritterBase {
    // The following five methods are the ones you must implement for your assignment.
public:
    CritterBase();
    virtual bool eat() = 0;
    virtual Attack fight(std::string opponent) = 0;
    virtual std::string getColor() = 0;
    virtual Direction getMove() = 0;
    virtual std::string getType() const = 0;
    virtual std::string toString() = 0;

    // The following functionality is optional in case you want to use it to
    // help make your Wolf class more fancy. Enjoy!
    int getHeight() const;
    std::string getNeighbor(Direction dir) const;
    int getWidth() const;
    int getX() const;
    int getY() const;
    bool isAlive() const;
    bool isAwake() const;

    virtual void onLose();
    virtual void onMate();
    virtual void onMateEnd();
    virtual void onReset();
    virtual void onSleep();
    virtual void onWakeUp();
    virtual void onWin();

private:
    // The following methods are called by our model to help implement
    // the optional methods above.
    void __setAlive(bool alive);
    void __setAwake(bool awake);
    void __setLocation(int x, int y);
    void __setModelSize(int width, int height);
    void __setNeighbor(Direction dir, const std::string& neighbor);

    int __x;
    int __y;
    int __width;
    int __height;
    bool __alive;
    bool __awake;
    std::string __neighbors[5];

    friend class CritterModel;
};

#endif // _CRITTERBASE_H
