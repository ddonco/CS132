/*
Group 3: Dillon Donohue & Lucas Henderson
CS 132, Winter 2023
Final Project - Milestone 2, 03/04/23

The WildFireSim application simulates a wildfire where a fire has broken out among
natural fuel sources including grass, young forest, and old forest. The model simulates
the spread of the fire and a GUI displays the spread of the fire. Firefighting countermeasures
such as fire breakes and fire retardant are also included in the model to simulate
their effect on the spread of a wildfire.
*/

#ifndef _FIRESIMGUI_H_
#define _FIRESIMGUI_H_

#include "gbutton.h"
#include "gcheckbox.h"
#include "gchooser.h"
#include "glabel.h"
#include "gradiobutton.h"
#include "gslider.h"
#include "gwindow.h"
#include <sstream>

#include "FireSimModel.h"

using namespace sgl;

class FireSimGui {
public:
    /**
     * @brief FireSimGui creates a GUI window to display the current
    state of the passed in model.
     * @param model The FireSimModel
     */
    FireSimGui(FireSimModel *model);

    /**
     * @brief animate starts a timer listener to tick the model forward one step and display
    the updated model once every half second.
     */
    void animate();

private:
    // ms between animation frames.
    const int ANIMATION_DELAY = 500;
    // Size of squared in the grid.
    const int SQUARE_SIZE = 20;
    // x offset between squares in the grid.
    const int SQUARE_X_OFFSET = 2;
    // y offset between squares in the grid.
    const int SQUARE_Y_OFFSET = 3;
    // Font used in the window.
    const string FONT_FAMILY = "Arial";
    // Fond size used in the window.
    const int FONT_SIZE = 6;
    // Pointer to show data check box object.
    GCheckBox *gcb_showData;
    // Pointer to show temperature radio button object.
    GRadioButton *grb_showTemperatures;
    // Pointer to show fuel radio button object.
    GRadioButton *grb_showFuel;
    // Pointer to animation start button object.
    GButton *gb_start;
    // Pointer to wind direction chooser object.
    GChooser *gc_windDirection;
    // Pointer to wind speed slider.
    GSlider *gs_windSpeed;
    // Pointer to a label object for wind direction.
    GLabel *gl_windDirection;
    // Pointer to a label object for wind speed.
    GLabel *gl_windSpeed;
    // Boolean value toggled to show/hide data in gui.
    bool showData;
    // Boolean value toggled to show/hide temperature data in gui.
    bool showTemperature;
    // Boolean value toggled to show/hide remaining fuel data in gui.
    bool showFuel;
    // Stores the user selected wind direction.
    Direction windDirection;
    // Stores the user selected wind speed.
    double windSpeed;

    // A window object on which the gui is drawn.
    GWindow *window;
    // The model of the current state of the fire simulation world.
    FireSimModel *model;

    /*
    getGridX returns the x position on the GUI window for a given column number.
    Perameters:
        col     int     A col number.
    Returns:
        x       int     An x coordinate position.
    */
    int getGridX(int col) const;
    /*
    getGridY returns the y position on the GUI window for a given row number.
    Perameters:
        row     int     A row number.
    Returns:
        y       int     A y coordinate position.
    */
    int getGridY(int row) const;
    /*
    drawWorld drawns the current state of the FireSimModel onto the gui.
    It first clears everything currently on the GUI and then redraws each
    position in the model with the object currently in that position.
    Parameters:
        none
    Returns:
        none
    */
    void drawWorld();
    /*
    toggleShowData is used to toggle the showData parameter between true and false.
    */
    void toggleShowData();
    /*
    setShowTemperature is used to set the showTemperature parameter to true.
    */
    void setShowTemperature();
    /*
    setShowFuel is used to set the showFuel parameter to true.
    */
    void setShowFuel();
    /*
    setWindDirection is used to apply the user specified wind direction to the
    windDirection member variable.
    */
    void setWindDirection();
    /*
    setWindSpeed is used to apply the user specified wind speed to the
    windSpeed member variable.
    */
    void setWindSpeed();
};

#endif
