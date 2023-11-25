/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #6, 02/24/23

LifeGui manages the animation of a LifeModel object, including drawing a grid representing
the LifeModel and updating the grid to reflect cell growth and death. The LifeGui represents
a live cell as an "X". The LifeGui triggers a new tick in the model every 50 milliseconds.
*/

#include "LifeGui.h"

using namespace std;
using namespace sgl;

// Assign class constant values.
const int LifeGui::ANIMATION_DELAY = 500;
const int LifeGui::SQUARE_SIZE = 25;
const int LifeGui::SQUARE_X_OFFSET = 2;
const int LifeGui::SQUARE_Y_OFFSET = 3;
const string LifeGui::FONT_FAMILY = "Monospaced";
const int LifeGui::FONT_SIZE = 20;

LifeGui::LifeGui(LifeModel *lm) : lifeModel(lm) {
    // Create a new window and assign properties.
    window = new GWindow(false);
    window->setTitle("Game of Life");
    window->setBackground("White");
    window->setColor("black");
    window->setRepaintImmediately(true);
    window->setFont(FONT_FAMILY + "-" + to_string(FONT_SIZE));
    // Set the size of the window.
    window->setSize(
        getGridX(lifeModel->getCols()) + SQUARE_X_OFFSET,
        getGridY(lifeModel->getRows(), 0) + SQUARE_Y_OFFSET);

    window->setResizable(false);
    window->center();
    window->setVisible(true);
    window->toFront();
    // Call update one time to paint the initial state of the model.
    this->update();
}

LifeGui::~LifeGui() {
    delete window;
}

int LifeGui::getGridX(int col) const {
    return col * SQUARE_SIZE + SQUARE_X_OFFSET;
}

int LifeGui::getGridY(int row, int offset) const {
    return (row + offset) * SQUARE_SIZE + SQUARE_Y_OFFSET;
}

void LifeGui::update() {
    // Create a timer listener which will first clear the window canvas, then repaint
    // the grid to show the current/new state of the model.
    window->setTimerListener(ANIMATION_DELAY, [this] {
        window->clearCanvas();
        window->drawRect(0, 0,
                         getGridX(lifeModel->getCols()) + SQUARE_X_OFFSET,
                         getGridY(lifeModel->getRows(), 0) + SQUARE_Y_OFFSET);
        // Iterate over each roe and column of the LifeModel.
        for (int r = 0; r < lifeModel->getRows(); r++) {
            for (int c = 0; c < lifeModel->getCols(); c++) {
                int drawX = getGridX(c);
                int drawY = getGridY(r, 0);
                // Draw each grid square
                window->drawRect(drawX, drawY, SQUARE_SIZE, SQUARE_SIZE);
                // If there is a live cell in the current grid position, draw an X
                if (lifeModel->isAlive(r, c)) {
                    drawY = getGridY(r, 1);
                    window->drawString("X", drawX + 5, drawY - 4);
                }
            }
        }
        // Call update on the LifeModel to advance the model one step.
        this->lifeModel->update();
    });
}
