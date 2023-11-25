// Allison Obourn
// CS 132, Winter 2023
// Lecture 20

// The CritterGui represents a simple graphical user interface for the Critters
// program. It colors the background of the entire screen light green and
// draws 10 of each critter at random locations, moving them all every two
// seconds based on each Critter's specified movement and then redraws them.

#include "CritterGui.h"
#include "Critter.h"

// Constructs a GUI window to display the current state of the
// passed in model
CritterGui::CritterGui(CritterModel *model) : model(model) {
    window = new GWindow(WORLD_SIZE * SQUARE_SIZE, WORLD_SIZE * SQUARE_SIZE);
    window->setExitOnClose(true);
    window->setBackground("black");

    // set our timer to call the tick function every 500 milliseconds
    window->setTimerListener(500, [this] { this->drawCritters(); });
}

// draws all of the critters in the grid on the GUI, clearing it off first so
// each critter is only displayed once. Each critter is displayed as the string
// its toString returns in the color its getColor returns in the x, y position
// of its indecies in the grid multiplied by the cell size.
void CritterGui::drawCritters() {
    model.tick();
    window->clear();
    for (int row = 0; row < WORLD_SIZE; row++) {
        for (int col = 0; col < WORLD_SIZE; col++) {
            Critter *critter = model.get(row, col);
            if (critter != nullptr) {
                window->setColor(critter->getColor());
                window->drawString(critter->toString(), row * SQUARE_SIZE,
                                   col * SQUARE_SIZE);
            }
        }
    }
}