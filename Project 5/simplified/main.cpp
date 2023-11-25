/**
 * Allison Obourn
 * CS 132, Winter 2023
 * Lecture 20
 * 
 * This program emulates CritterMain. It creates a model of the board
 * which is a grid shape and places some number of each critter type listed
 * in the model at random locations. The number of each is determined by 
 * the CRITTER_COUNT, which types by the names listed in CRITTER_TYPES. 
 * Repeatedly gets all the critters next moves and redraws them in the 
 * critter world at their new position
 * 
 **/

#include <iostream>
#include <vector>
#include "gwindow.h"
#include "CritterGui.h"

using namespace std;
using namespace sgl;

int main() {
    // start random out at the current millisecond
    srand(time(0));
    
    // create our model and gui
    CritterModel* model = new CritterModel();
    CritterGui gui(model);

    return 0;
}