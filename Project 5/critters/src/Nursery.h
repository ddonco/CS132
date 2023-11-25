/*
 * Critters
 * This file declares a function that can be used to create a new critter
 * of a given type specified by a string such as "Ant" or "Stone".
 *
 * DO NOT MODIFY THIS FILE!
 *
 * @version 2021/04/11
 * - initial C++ version for 21sp
 */

#ifndef _NURSERY_H
#define _NURSERY_H

#include "Critter.h"
#include <string>
#include <vector>

class Nursery {
public:
    /**
     * Returns all types of critters that can be created by this nursery.
     * The default expected return is:
     * {"Ant", "Bird", "Hippo", "Stone", "Vulture", "Wolf"}.
     * But you can modify this to add/remove
     */
    static std::vector<std::string> getAvailableCritterTypes();

    /**
     * Returns the number of each type of critter that should be initially placed
     * into the world.
     * The default expected return is 25, but you can customize this for testing.
     */
    static int getDefaultCritterCount();

    /**
     * Creates and returns a new critter of the given type, such as "Ant" or "Stone".
     *
     * Any parameters required by that type's constructor should be generated randomly.
     * Specifically:
     * - An Ant should have its 'walk south' Boolean constructor parameter
     *   set to true or false with equal probability.
     * - A Hippo should have its hunger set to 0-9 inclusive with equal probability.
     *
     * The critter returned should be heap-allocated (using 'new').
     *
     * If an unknown type of critter is passed, such as "Banana", this function
     * should return a null pointer (nullptr).
     */
    static Critter* makeBabyCritter(std::string type);
};

#endif // _NURSERY_H
