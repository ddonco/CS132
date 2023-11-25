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

#include "FireSimGui.h"

FireSimGui::FireSimGui(FireSimModel *model) : gcb_showData(nullptr),
                                              grb_showTemperatures(nullptr),
                                              grb_showFuel(nullptr),
                                              gb_start(nullptr),
                                              gc_windDirection(nullptr),
                                              gs_windSpeed(nullptr),
                                              gl_windDirection(nullptr),
                                              gl_windSpeed(nullptr),
                                              showData(false),
                                              showTemperature(true),
                                              showFuel(false),
                                              windDirection(NORTH),
                                              windSpeed(0),
                                              model(model) {
    // Create a new window and assign properties.
    window = new GWindow(model->getWorldSize() * SQUARE_SIZE, model->getWorldSize() * SQUARE_SIZE);
    window->setExitOnClose(true);
    window->setBackground("white");
    window->setFont(FONT_FAMILY + "-" + to_string(FONT_SIZE));
    // Set the size of the window.
    window->setSize(
        getGridX(model->getWorldSize()) + SQUARE_X_OFFSET + 80,
        getGridY(model->getWorldSize()) + SQUARE_Y_OFFSET + 30);
    // Add a checkbox to allow the user to show or hide model data.
    gcb_showData = new sgl::GCheckBox("&Data", showData);
    gcb_showData->setActionListener([this] {
        this->toggleShowData();
    });
    window->addToRegion(gcb_showData, sgl::GWindow::Region::REGION_SOUTH);
    // Add a radiobutton to allow the user to show temperature at each position in the model.
    grb_showTemperatures = new sgl::GRadioButton("&Temperature", "data", showTemperature);
    grb_showTemperatures->setActionListener([this] {
        this->setShowTemperature();
    });
    window->addToRegion(grb_showTemperatures, sgl::GWindow::Region::REGION_SOUTH);
    // Add a radiobutton to allow the user to show fuel remaining at each position in the model.
    grb_showFuel = new sgl::GRadioButton("&Fuel", "data", showFuel);
    grb_showFuel->setActionListener([this] {
        this->setShowFuel();
    });
    window->addToRegion(grb_showFuel, sgl::GWindow::Region::REGION_SOUTH);
    // Add a label for the wind direction dropdown selection.
    gl_windDirection = new GLabel("Wind\nDirection:");
    window->addToRegion(gl_windDirection, sgl::GWindow::Region::REGION_EAST);
    // Add a dropdown selection for wind directions.
    gc_windDirection = new GChooser();
    gc_windDirection->addItems({"North", "East", "South", "West"});
    gc_windDirection->setActionListener([this] {
        this->setWindDirection();
    });
    window->addToRegion(gc_windDirection, sgl::GWindow::Region::REGION_EAST);
    // Add a label for the wind speed slider.
    gl_windSpeed = new GLabel("Wind Speed\n(0-100 MPH):");
    window->addToRegion(gl_windSpeed, sgl::GWindow::Region::REGION_EAST);
    // Add a wind speed slider that has a range of 0 to 100.
    gs_windSpeed = new GSlider(GSlider::VERTICAL, 0, 100, 0);
    gs_windSpeed->setActionListener([this] {
        this->setWindSpeed();
    });
    window->addToRegion(gs_windSpeed, sgl::GWindow::Region::REGION_EAST);

    gb_start = new GButton("&Start");
    gb_start->setActionListener([this] {
        this->gc_windDirection->setEnabled(false);
        this->gs_windSpeed->setEnabled(false);
        this->animate();
    });
    window->addToRegion(gb_start, sgl::GWindow::Region::REGION_EAST);

    // Call drawWorld to paint the initial state of the model.
    drawWorld();
}

void FireSimGui::toggleShowData() {
    showData = !showData;
}

void FireSimGui::setShowTemperature() {
    showTemperature = true;
    showFuel = false;
}

void FireSimGui::setShowFuel() {
    showFuel = true;
    showTemperature = false;
}

void FireSimGui::setWindDirection() {
    Direction d = directionFromString(gc_windDirection->getSelectedItem());
    windDirection = d;
}

void FireSimGui::setWindSpeed() {
    windSpeed = gs_windSpeed->getValue();
}

int FireSimGui::getGridX(int col) const {
    return col * SQUARE_SIZE + SQUARE_X_OFFSET;
}

int FireSimGui::getGridY(int row) const {
    return row * SQUARE_SIZE + SQUARE_Y_OFFSET;
}

void FireSimGui::drawWorld() {
    // Do we need to clear? Causes flickering, and everything gets drawn over anyway.
    // window->clear();
    window->drawRect(0, 0,
                     getGridX(model->getWorldSize()) + SQUARE_X_OFFSET,
                     getGridY(model->getWorldSize()) + SQUARE_Y_OFFSET);
    for (int row = 0; row < model->getWorldSize(); row++) {
        for (int col = 0; col < model->getWorldSize(); col++) {
            Meter *meter = model->get(row, col);
            if (meter != nullptr) {
                int drawX = getGridX(col);
                int drawY = getGridY(row);
                window->setColor(meter->getColor());
                window->fillRect(drawX, drawY, SQUARE_SIZE, SQUARE_SIZE);
                window->setColor("black");
                window->drawRect(drawX, drawY, SQUARE_SIZE, SQUARE_SIZE);
                if (showData && showTemperature) {
                    int meterTemp = (int)meter->getTemperature();
                    window->drawString(to_string(meterTemp), drawX + 2, drawY + SQUARE_SIZE - 6);
                } else if (showData && showFuel) {
                    int meterFuel = (int)meter->getFuelRemaining();
                    window->drawString(to_string(meterFuel), drawX + 4, drawY + SQUARE_SIZE - 6);
                }
            }
        }
    }
}

void FireSimGui::animate() {
    model->setWindProps(windDirection, windSpeed);
    // Start a timer listener to draw the current state of the model every 500 milliseconds.
    window->setTimerListener(500, [this] {
        this->gb_start->setEnabled(false);
        this->model->tick();
        this->drawWorld();
    });
}
