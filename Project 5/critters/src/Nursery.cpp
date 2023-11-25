/*
 * Critters
 */

#include "Nursery.h"
#include "Ant.h"
#include "Bird.h"
#include "Butterfly.h"
#include "Cat.h"
#include "Hippo.h"
#include "Stone.h"
#include "Vulture.h"
#include <random>

std::vector<std::string> Nursery::getAvailableCritterTypes() {
    return {"Ant", "Bird", "Hippo", "Stone", "Vulture", "Cat"};
    // Add in the other critter types as you write them:
    // {"Ant", "Bird", "Hippo", "Stone", "Vulture", "Cat"};
}

int Nursery::getDefaultCritterCount() {
    return 20;
}

Critter *Nursery::makeBabyCritter(std::string type) {
    if (type == "Stone") {
        return new Stone();
    }
    // uncomment these creations of different Critter types
    // as you implement them

    else if (type == "Ant") {
        bool walkSouth = rand() % 2 == 0;
        return new Ant(walkSouth);
    } else if (type == "Bird") {
        return new Bird();
    } else if (type == "Hippo") {
        int hunger = rand() % 10;
        return new Hippo(hunger);
    } else if (type == "Vulture") {
        return new Vulture();
    } else if (type == "Cat") {
        bool walkWest = rand() % 2 == 0;
        return new Cat(walkWest);
    }
    return nullptr;
}
