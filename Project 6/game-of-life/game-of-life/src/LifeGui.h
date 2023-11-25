/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #6, 02/24/23

LifeGui manages the animation of a LifeModel object, including drawing a grid representing
the LifeModel and updating the grid to reflect cell growth and death. The LifeGui represents
a live cell as an "X". The LifeGui triggers a new tick in the model every 50 milliseconds.
*/

#ifndef _LIFEGUI_H
#define _LIFEGUI_H

#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
#include "gobjects.h"
#include "gradiobutton.h"
#include "gtextfield.h"
#include "gthread.h"
#include "gwindow.h"

#include "LifeModel.h"

using namespace std;

class LifeGui {
public:
    static const int ANIMATION_DELAY; // ms between animation frames
    static const int SQUARE_SIZE;     // size of squared in the grid
    static const int SQUARE_X_OFFSET; // x offset between squares in the grid
    static const int SQUARE_Y_OFFSET; // y offset between squares in the grid
    static const string FONT_FAMILY;  // font used in the window
    static const int FONT_SIZE;       // fond size used in the window

    /*
    The LifeGui constructor takes a pointer to a LifeModel and initializes
    the GUI window for animation.
    Parameters:
        lm      *LifeModel   The LifeModel to display in the animation.
    */
    LifeGui(LifeModel *lm);
    /*
    The LifeGui destructor used to delete the stack allocated window object.
    */
    ~LifeGui();
    /*
    update will trigger the LifeModel to update and will update the GUI grid to
    display the current state of the model. Live cells are displayed as "X".
    Parameters:
        none
    Returns:
        none
    */
    void update();

private:
    /*
    getGridX returns the x position on the GUI window for a given column number.
    Perameters:
        col     int     A col number.
    Returns:
        x       int     An x coordinate position.
    */
    int getGridX(int col) const;
    /*
    getGridY returns the y position on the GUI window for a given row number. getGridY has
    an offset parameter to specify an amount of rows to offset the returned Y position.
    Perameters:
        row     int     A row number.
        offset  int     An amount of rows to offset the returned y position.
    Returns:
        y       int     A y coordinate position.
    */
    int getGridY(int row, int offset) const;
    /*
    animate is used to cyclically call update every 50 milliseconds to animate the GUI.
    Perameters:
        none
    Returns:
        none
    */
    // A pointer to a window object used for the GUI.
    sgl::GWindow *window;
    // A pointer to a LifeModel object which is displayed and animated in the GUI.
    LifeModel *lifeModel;
};

#endif