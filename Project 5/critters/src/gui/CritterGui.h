/*
 * Critters
 * The graphical user interface (GUI) that displays the simulation.
 * The GUI interacts heavily with the CritterModel, which contains the actual
 * game board and state. The GUI's job is to display that state and to allow
 * the user to advance the game with its go/stop/tick buttons.
 *
 * DO NOT MODIFY THIS FILE!
 *
 * @version 2021/04/11
 * - initial C++ version for 21sp
 */

#ifndef _CRITTERGUI_H
#define _CRITTERGUI_H

#include "gborder.h"
#include "gbutton.h"
#include "gcanvas.h"
#include "gcheckbox.h"
#include "gcontainer.h"
#include "gevent.h"
#include "glabel.h"
#include "gtimer.h"
#include "gwindow.h"
#include "CritterModel.h"
#include <map>
#include <string>

class CritterClassPanel;   // forward declaration

class CritterGui {
public:
    static const std::string CRITTER_FONT_FAMILY;
    static const std::string TITLE;
    static const int ANIMATION_DELAY;   // ms between animation frames
    static const int BABY_FONT_SIZE;
    static const int CRITTER_FONT_SIZE;
    static const int GRID_LINE_COLOR;
    static const int SQUARE_SIZE;
    static const int SQUARE_X_OFFSET;
    static const int SQUARE_Y_OFFSET;
    static const int STATUS_FONT_SIZE;

    CritterGui(CritterModel* model);
    void show();

private:
    void drawCanvas();
    void drawShadowedString(const std::string& s, const std::string& color, int x, int y);
    int getDrawX(int x) const;
    int getDrawY(int y) const;
    int getModelX(int x) const;
    int getModelY(int y) const;
    void doEnabling();
    void go();
    void handleClick(const sgl::GMouseEvent& event);
    void handleModelEvent(ModelEvent event);
    void handleMove(const sgl::GMouseEvent& event);
    void reset();
    void stop();
    void tick();
    void toggleDebug();
    void updateClassCounts();

    sgl::GWindow* _window;
    sgl::GButton* _gb_go;
    sgl::GButton* _gb_stop;
    sgl::GButton* _gb_tick;
    sgl::GButton* _gb_reset;
    sgl::GLabel* _gl_status;
    sgl::GCheckBox* _gcb_debug;
    std::map<std::string, CritterClassPanel*> _classPanels;
    CritterModel* _model;
    bool _isAnimating;
};

class CritterClassPanel {
public:
    CritterClassPanel(CritterModel* model, const std::string& className);
    sgl::GInteractor* getInteractor() const;
    void setEnabled(bool enabled);
    void update(const CritterState& state, bool isWinning = false);

    CritterModel* _model;
    std::string _className;
    sgl::GBorder* _gborder;
    sgl::GContainer* _gcontainer;
    sgl::GButton* _gb_remove;
    sgl::GLabel* _gl_status;
    std::string _background;
};

void guiMain();

#endif // _CRITTERGUI_H
