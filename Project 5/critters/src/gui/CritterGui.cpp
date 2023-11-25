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

#include "CritterGui.h"
#include "gcolor.h"
#include "gfont.h"
#include "gobjects.h"
#include "gtypes.h"

#include "Critter.h"
#include "Nursery.h"
#include <algorithm>
#include <cctype>
#include <exception>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

// TODO: mouse movement, show debug info about square
// TODO: mouse drag a critter?

// class CritterGui implementation

/*static*/ const std::string CritterGui::CRITTER_FONT_FAMILY = "Monospaced";
/*static*/ const std::string CritterGui::TITLE = "CS 132 Critters";
/*static*/ const int CritterGui::ANIMATION_DELAY = 100;
/*static*/ const int CritterGui::BABY_FONT_SIZE = 10;
/*static*/ const int CritterGui::CRITTER_FONT_SIZE = 12;
/*static*/ const int CritterGui::GRID_LINE_COLOR = 0xaaaaaa;
/*static*/ const int CritterGui::SQUARE_SIZE = 14;
/*static*/ const int CritterGui::SQUARE_X_OFFSET = 2;
/*static*/ const int CritterGui::SQUARE_Y_OFFSET = 3;
/*static*/ const int CritterGui::STATUS_FONT_SIZE = 9;

CritterGui::CritterGui(CritterModel* model)
        : _window(nullptr),
          _gb_go(nullptr),
          _gb_stop(nullptr),
          _gb_tick(nullptr),
          _gb_reset(nullptr),
          _gl_status(nullptr),
          _gcb_debug(nullptr),
          _model(model),
          _isAnimating(false) {
    if (!_model) {
        throw std::runtime_error("CritterGui::constructor: null model");
    }
    _model->addObserver([this](ModelEvent event) {
        this->handleModelEvent(event);
    });

    _window = new sgl::GWindow(/* visible */ false);
    _window->setBackground(0xa2deb9);
    _window->setFont(CRITTER_FONT_FAMILY + "-" + std::to_string(CRITTER_FONT_SIZE));
    _window->setRegionVerticalAlignment(sgl::GWindow::REGION_EAST, sgl::ALIGN_TOP);
    _window->setRegionHorizontalAlignment(sgl::GWindow::REGION_SOUTH, sgl::ALIGN_LEFT);
    _window->setMouseListener([this](sgl::GEvent event) {
        sgl::GMouseEvent mouseEvent(event);
        if (mouseEvent.getType() == sgl::MOUSE_MOVED) {
            this->handleMove(mouseEvent);
        } else if (mouseEvent.getType() == sgl::MOUSE_PRESSED) {
            this->handleClick(mouseEvent);
        }
    });

    _gb_go = new sgl::GButton("&Go");
    _gb_go->setActionListener([this]() {
        this->go();
    });
    _window->addToRegion(_gb_go, sgl::GWindow::Region::REGION_SOUTH);

    _gb_stop = new sgl::GButton("&Stop");
    _gb_stop->setActionListener([this]() {
        this->stop();
    });
    _window->addToRegion(_gb_stop, sgl::GWindow::Region::REGION_SOUTH);

    _gb_tick = new sgl::GButton("&Tick");
    _gb_tick->setActionListener([this]() {
        this->tick();
    });
    _window->addToRegion(_gb_tick, sgl::GWindow::Region::REGION_SOUTH);

    _gb_reset = new sgl::GButton("&Reset");
    _gb_reset->setActionListener([this]() {
        this->reset();
    });
    _window->addToRegion(_gb_reset, sgl::GWindow::Region::REGION_SOUTH);

    _gcb_debug = new sgl::GCheckBox("&Debug", /* checked */ _model->isDebug());
    _gcb_debug->setActionListener([this] {
        this->toggleDebug();
    });
    _window->addToRegion(_gcb_debug, sgl::GWindow::Region::REGION_SOUTH);

    _gl_status = new sgl::GLabel(" ");
    _window->addToRegion(_gl_status, sgl::GWindow::Region::REGION_SOUTH);

    // sets borders to light gray
    sgl::GContainer* con = _gl_status->getContainer();
    con->setBackground(0xdddddd);

    updateClassCounts();

    _window->setExitOnClose(true);
    _window->setTitle(TITLE);

    // note on window size:
    // ought to be able to just set to proper w/h, but for some reason it's too small.
    // for now, hack and use larger fixed size.
    // int canvasWidth = SQUARE_SIZE * _model->getWidth() + SQUARE_X_OFFSET * 2;
    // int canvasHeight = SQUARE_SIZE * (_model->getHeight() + 1) + SQUARE_Y_OFFSET * 2;
    // _window->setCanvasSize(canvasWidth, canvasHeight);
    _window->setSize(1000, 760);

    // _window->setResizable(false);
    _window->setAutoRepaint(false);
    // _window->pack();

    doEnabling();

    _window->center();
}

void CritterGui::doEnabling() {
    _gb_go->setEnabled(!_isAnimating);
    _gb_stop->setEnabled(_isAnimating);
    _gb_tick->setEnabled(!_isAnimating);
    _gb_reset->setEnabled(!_isAnimating);

    for (auto it = _classPanels.begin(); it != _classPanels.end(); it++) {
        CritterClassPanel* classPanel = it->second;
        classPanel->setEnabled(!_isAnimating);
    }
}

void CritterGui::drawCanvas() {
    //std::cout << "drawCanvas() begin" << std::endl;
    _window->clearCanvas();
    // _window->setColor(sgl::GColor::CYAN);
    // _window->fillRect(0, 0, _window->getCanvasWidth(), _window->getCanvasHeight());
    _window->setColor(sgl::GColor::BLACK);
    _window->drawRect(0, 0, getDrawX(_model->getWidth()), getDrawY(_model->getHeight()));
    for (int x = 0; x < _model->getWidth(); x++) {
        for (int y = 0; y < _model->getHeight(); y++) {
            int drawX = getDrawX(x);
            int drawY = getDrawY(y);
            if (_model->isDebug()) {
                _window->setColor(GRID_LINE_COLOR);
                _window->drawRect(drawX, drawY, SQUARE_SIZE, SQUARE_SIZE);
            }

            std::string critterString = _model->getString(x, y);
            if (_model->isBaby(x, y)) {
                for (int i = 0; i < critterString.length(); i++) {
                    critterString[i] = tolower(critterString[i]);
                }
                _window->setFont(CRITTER_FONT_FAMILY + "-" + std::to_string(BABY_FONT_SIZE));
            }

            if (!critterString.empty() && critterString != CritterModel::EMPTY) {
                std::string color = _model->getColor(x, y);
                if (color.empty()) {
                    color = "black";
                }
                drawShadowedString(critterString, color, drawX, drawY);
            }

            if (_model->isBaby(x, y)) {
                _window->setFont(CRITTER_FONT_FAMILY + "-" + std::to_string(CRITTER_FONT_SIZE));
            }
        }
    }
    _window->repaint();
}

void CritterGui::drawShadowedString(const std::string& s, const std::string& color, int x, int y) {
    _window->setColor(sgl::GColor::BLACK);
    _window->drawString(s, x + 1, y + 1);
    _window->setColor(color);
    _window->drawString(s, x, y);
}

// Implementation note: getDrawX/Y must perform the inverse calculation
// compared to getModelX/Y. If you change one, change the other to match.
int CritterGui::getDrawX(int x) const {
    return x * SQUARE_SIZE + SQUARE_X_OFFSET;
}

int CritterGui::getDrawY(int y) const {
    return (y + 1) * SQUARE_SIZE + SQUARE_Y_OFFSET;
}

int CritterGui::getModelX(int x) const {
    return (x - SQUARE_X_OFFSET) / SQUARE_SIZE;
}

int CritterGui::getModelY(int y) const {
    return ((y - SQUARE_Y_OFFSET) / SQUARE_SIZE) - 1;
}

void CritterGui::go() {
    if (!_isAnimating) {
        _isAnimating = true;
        doEnabling();
        _window->setTimerListener(ANIMATION_DELAY, [this] {
            this->tick();
        });
    }
}

void CritterGui::handleClick(const sgl::GMouseEvent& event) {
    std::cout << "mouse click: " << event << std::endl;
}

void CritterGui::handleModelEvent(ModelEvent event) {
    switch (event) {
        case REMOVE_ALL:
        case RESET:
            drawCanvas();
            updateClassCounts();
            doEnabling();
            break;
        default:
            break;
    }
}

void CritterGui::handleMove(const sgl::GMouseEvent& event) {
    int modelX = getModelX(static_cast<int>(event.getX()));
    int modelY = getModelY(static_cast<int>(event.getY()));
    if (!_model->isOnBoard(modelX, modelY) || !_gl_status) {
        return;
    }
    // TODO
//    _gl_status->setText("(" + std::to_string(modelX) + ", " +
//                        std::to_string(modelY) + ")");
}

void CritterGui::reset() {
    _model->reset();
}

void CritterGui::show() {
    _window->show();
    drawCanvas();
}

void CritterGui::stop() {
    if (_isAnimating) {
        _isAnimating = false;
        _window->removeTimerListener();
        doEnabling();
    }
}

void CritterGui::tick() {
    _model->update();
    drawCanvas();
    updateClassCounts();
}

void CritterGui::toggleDebug() {
    bool debug = _gcb_debug->isChecked();
    _model->setDebug(debug);
    doEnabling();
}

void CritterGui::updateClassCounts() {
    // remove any unneeded class panels
    std::vector<std::string> modelClassNames = _model->getClassNames();
    std::vector<std::string> classPanelsToRemove;
    for (auto it = _classPanels.begin(); it != _classPanels.end(); it++) {
        std::string className = it->first;
        if (std::find(modelClassNames.begin(), modelClassNames.end(), className) == modelClassNames.end()) {
            classPanelsToRemove.push_back(className);
        }
    }
    for (std::string className : classPanelsToRemove) {
        CritterClassPanel* classPanel = _classPanels[className];
        _classPanels.erase(className);
        _window->removeFromRegion(classPanel->getInteractor(), sgl::GWindow::REGION_EAST);
    }

    // add any missing class panels
    std::string winningClassName = _model->getWinningClassName();
    for (std::string className : modelClassNames) {
        CritterClassPanel* classPanel = nullptr;
        if (_classPanels.find(className) == _classPanels.end()) {
            // new class; add an east pane about it
            classPanel = new CritterClassPanel(_model, className);
            _window->addToRegion(classPanel->getInteractor(), sgl::GWindow::REGION_EAST);
            _classPanels[className] = classPanel;
        } else {
            classPanel = _classPanels[className];
        }
        if (!classPanel) {
            continue;
        }

        const CritterState& state = _model->getClassState(className);
        classPanel->update(state, /* isWinning */ winningClassName == className);
    }
}


// class CritterClassPanel implementation

CritterClassPanel::CritterClassPanel(CritterModel* model, const std::string& className)
    : _model(model),
      _className(className),
      _gborder(nullptr),
      _gcontainer(nullptr),
      _gb_remove(nullptr),
      _gl_status(nullptr) {
    _gcontainer = new sgl::GContainer(sgl::GContainer::LAYOUT_FLOW_VERTICAL);
    _gl_status = new sgl::GLabel(className);
    _gcontainer->add(_gl_status);
    _gb_remove = new sgl::GButton("Remove");
    sgl::GFont::changeFontSize(_gb_remove, -2);
    _gb_remove->setActionListener([this] {
        _model->removeAll(_className, /* permanent */ true);
    });
    _gcontainer->add(_gb_remove);
    _gborder = new sgl::GBorder(_gcontainer, className);
    // sgl::GFont::changeFontSize(_gborder, CritterGui::FONT_SIZE);
    sgl::GFont::boldFont(_gborder);
    // _gborder->setBorderColor("blue");
    _gl_status->setFont("Monospaced-" + std::to_string(CritterGui::STATUS_FONT_SIZE));
}

sgl::GInteractor* CritterClassPanel::getInteractor() const {
    return _gborder;
}

void CritterClassPanel::setEnabled(bool enabled) {
    _gb_remove->setEnabled(enabled);
}

static std::string padNbsp(int n, int width) {
    std::string s = std::to_string(n);
    std::string result = s;
    for (int i = 0, w = width - s.length(); i < w; i++) {
        result = "&nbsp;" + result;
    }
    return result;
}

void CritterClassPanel::update(const CritterState& state, bool isWinning) {
    std::ostringstream out;
    out << "<html><code>" << std::endl
        << padNbsp(state.count, 4) << " alive (-" << padNbsp(state.deaths, 2) << ")<br>" << std::endl
        << "+" << padNbsp(state.kills, 3) << " kills<br>" << std::endl
        << "+" << padNbsp(state.foodEaten, 3) << " food"
        // << "<b>=" << padNbsp(state.total(), 3) << " TOTAL</b>" << std::endl
        << "</code></html>";
    _gl_status->setText(out.str());
    _gborder->setTitle(_className + ": " + std::to_string(state.total()));
    _gborder->setBackground(isWinning ? "yellow" : "#00ffffff");   // transparent
}


// free functions implementation

void guiMain() {
    CritterModel* model = new CritterModel(60, 50);
    // model.setDebug(true);

    // fill model with critters
    std::vector<std::string> classNames = Nursery::getAvailableCritterTypes();
    int count = Nursery::getDefaultCritterCount();
    for (std::string className : classNames) {
        for (int i = 0; i < count; i++) {
            Critter* critter = Nursery::makeBabyCritter(className);
            model->add(critter);
        }
    }

    CritterGui* gui = new CritterGui(model);
    gui->show();
}
