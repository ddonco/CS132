// Allison Obourn 
// CS 132, Winter 2023
// Lecture 20

// The CritterGui represents a simple graphical user interface for the Critters 
// program. It colors the background of the entire screen light green and
// draws 10 of each critter at random locations, moving them all every two 
// seconds based on each Critter's specified movement and then redraws them. 

#ifndef _critter_gui_h_
#define _critter_gui_h_ 

#include "gwindow.h"
#include "CritterModel.h"
using namespace sgl;

class CritterGui {
public:
    // Constructs a GUI window to display the current state of the 
    // passed in model
    CritterGui(CritterModel* model);
private:
    // the number of pixels wide/tall of each square
    const int SQUARE_SIZE = 20;

    // the window the simulation is drawn on
    GWindow* window;

    // the model of the current state of the critter world. Used to keep track 
    // of the position of each critter
    CritterModel* model;

    // Draws the current state of the Critter model onto the GUI. It clears 
    // everything currently on the GUI and then redraws each Critter at its 
    // (possibly new) current location. 
    void drawCritters();
};

#endif