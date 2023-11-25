/*
 * Critters
 * The model of all critters in the simulation.
 * The main work is done by the update method, which moves all critters
 * and initiates the various fights and interactions between them.
 *
 * DO NOT MODIFY THIS FILE!
 *
 * @version 2021/04/11
 * - initial C++ version for 21sp
 */

#include "CritterModel.h"
#include "Nursery.h"
#include "gexceptions.h"
#include <algorithm>
#include <exception>
#include <iomanip>
#include <random>
#include <sstream>
#include <stdexcept>

static std::string className(Critter* critter) {
    if (!critter) {
        return "nullptr";
    }
    // return sgl::exceptions::demangle(typeid(*critter).name());
    return critter->getType();
}

static std::string to_string(Critter* critter) {
    if (critter) {
        std::string hashCode = "X";
        return "{" + className(critter) + ", \"" + critter->toString() + "\", id " + hashCode + "}";
    } else {
        return "nullptr";
    }
}


std::ostream& operator <<(std::ostream& out, const Point& point) {
    return out << "(x=" << point.x << ", y=" << point.y << ")";
}

std::string to_string(const Point& point) {
    std::ostringstream out;
    out << point;
    return out.str();
}

CritterState::CritterState() :
        className(""),
        critter(nullptr),
        daddy(nullptr),
        mate(nullptr),
        count(0),
        initialCount(0),
        kills(0),
        deaths(0),
        moves(0),
        foodEaten(0),
        foodPenalty(0),
        matePenalty(0) {
    // empty
}

bool CritterState::isAsleep() const {
    return foodPenalty > 0;
}

bool CritterState::isBaby() const {
    return daddy && moves < CritterModel::MATING_PENALTY;
}

bool CritterState::isMating() const {
    return mate && matePenalty > 0;
}

void CritterState::reset() {
    count = 0;
    deaths = 0;
    foodEaten = 0;
    foodPenalty = 0;
    initialCount = 0;
    kills = 0;
    moves = 0;
    mate = nullptr;
    matePenalty = 0;
    daddy = nullptr;
}

int CritterState::total() const {
    return count + kills + foodEaten;
}

const std::string CritterModel::EMPTY = " ";
const std::string CritterModel::WOLF_CLASS_NAME = "Wolf";
const int CritterModel::DEFAULT_CRITTER_COUNT = 25;
const int CritterModel::DEFAULT_WIDTH = 60;
const int CritterModel::DEFAULT_HEIGHT = 50;
const int CritterModel::MATING_PENALTY = 20;
const int CritterModel::CRITTER_GLUTTON_COUNT = 1;
const int CritterModel::CRITTER_CLASS_GLUTTON_COUNT = 0;
const int CritterModel::CRITTER_MOVE_FATIGUE_COUNT = 0;
const int CritterModel::INT_PARAM_MAX = 9;
const int CritterModel::GLUTTON_PENALTY = 20;
const bool CritterModel::RANDOMIZE_GLUTTON_PENALTY = true;
const int CritterModel::FOOD_RESPAWN_INTERVAL = 50;
const std::string CritterModel::FOOD = ".";
const int CritterModel::FOOD_PERCENTAGE = 5;
const std::string CritterModel::FOOD_COLOR = "black";
const bool CritterModel::DISPLAY_BABIES = true;

Square::Square() :
        critter(nullptr),
        display(CritterModel::EMPTY),
        color(""),
        food(false) {
    // empty
}


CritterModel::CritterModel(int width, int height)
    : _width(width),
      _height(height),
      _moveCount(0),
      _partialIndex(0),
      _infoPoint({0, 0}),
      _debug(false) {
    // check for invalid model size
    if (width <= 0) {
        width = DEFAULT_WIDTH;
    }
    if (height <= 0) {
        height = DEFAULT_HEIGHT;
    }

    _board.reserve(width);
    for (int x = 0; x < width; x++) {
        std::vector<Square> v;
        for (int y = 0; y < height; y++) {
            v.push_back(Square());
        }
        _board.push_back(v);
    }

    createRandomFood();
    updateDisplay(NEW);
}

void CritterModel::add(Critter* critter) {
    add(critter, randomOpenLocation());
}

void CritterModel::add(Critter* critter, const Point& location, bool isInitial) {
    if (!critter) {
        throw std::runtime_error("CritterModel::add: null critter passed");
    }
    if (totalCritterCount() >= _width * _height) {
        throw std::runtime_error("CritterModel::add: too many critters");
    }

    // count # of critters of each class
    std::string type = className(critter);
    if (_classStateMap.find(type) == _classStateMap.end()) {
        // first of its kind; add class entry
        _classStateMap[type] = CritterState();
        _classStateMap[type].className = type;
    }
    _classStateMap[type].count++;
    if (isInitial) {
        _classStateMap[type].initialCount++;
    }

    // place critter on board
    _critterList.push_back(critter);
    _locationMap[critter] = location;
    _board[location.x][location.y].critter = critter;


    // count various things about each critter object
    _critterStateMap[critter] = CritterState();
    _critterStateMap[critter].className = type;
    _critterStateMap[critter].critter = critter;

    // update the critter's internal fields
    critter->__setModelSize(_width, _height);
    critter->__setLocation(location.x, location.y);

    updateDisplay(ADD);
}

void CritterModel::addObserver(ModelEventListener listener) {
    if (!listener) {
        throw std::runtime_error("CritterModel::addObserver: null listener");
    }
    _observers.push_back(listener);
}

void CritterModel::createRandomFood() {
    // clear out any previous food
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            _board[x][y].food = false;
        }
    }

    // randomly fill some fraction of all squares
    int squaresToFill = FOOD_PERCENTAGE * _width * _height / 100;
    for (int i = 0; i < squaresToFill; i++) {
        int randomX = rand() % _width;
        int randomY = rand() % _height;
        _board[randomX][randomY].food = true;
    }
}

Critter* CritterModel::fight(
        Critter* critter1,
        Critter* critter2,
        const std::string& /*critter1toString*/,
        const std::string& /*critter2toString*/) {
    // * I have to call .toString() again on the critters because it might
    // have changed since I last stored it (such as if they fight, eat, etc.)
    std::string critter2toString2 = critter2->toString();
    Attack weapon1 = critter1->fight(critter2toString2);

    std::string critter1toString2 = critter1->toString();
    Attack weapon2 = critter2->fight(critter1toString2);

    printDebug("      " + to_string(critter1) + " chooses " + to_string(weapon1));
    printDebug("      " + to_string(critter2) + " chooses " + to_string(weapon2));


    Critter* winner = nullptr;

    // special case: if one of the animals is sleeping, it dies
    std::string className1 = className(critter1);
    std::string className2 = className(critter2);
    if (className1 == className2) {
        throw std::runtime_error("BUG: Should not get here. Two "
                + className1 + "s fighting. This should not happen!");
    }
    CritterState& classState1 = _classStateMap[className1];
    CritterState& classState2 = _classStateMap[className2];

    CritterState& state1 = _critterStateMap[critter1];
    CritterState& state2 = _critterStateMap[critter2];
    if (((classState1.isAsleep() || state1.isAsleep()) && (classState2.isAsleep() || state2.isAsleep())) ||
            (state1.isMating() && state2.isMating())) {
        // shouldn't get here
        throw std::runtime_error("BUG: Fight between two sleeping/mating critters. This should not happen!");
    } else if (classState1.isAsleep() || state1.isAsleep() || state1.isMating()) {
        winner = critter2;
    } else if (classState2.isAsleep() || state2.isAsleep() || state2.isMating()) {
        winner = critter1;
    } else {
        // let's randomly decide that if both animals forfeit, player 1 wins
        if (weapon1 == weapon2) {
            // tie
            winner = rand() % 2 == 0 ? critter1 : critter2;
        } else if ((weapon2 == FORFEIT)
                || (weapon1 == ROAR && weapon2 == SCRATCH)
                || (weapon1 == SCRATCH && weapon2 == POUNCE)
                || (weapon1 == POUNCE && weapon2 == ROAR)) {
            // player 1 wins
            winner = critter1;
        } else {
            // player 2 wins
            winner = critter2;
        }
    }

    // inform the critters that they have won/lost
    winner->onWin();
    Critter* loser = (winner == critter1) ? critter2 : critter1;
    loser->onLose();

    // if the loser was mating, inform the mate to go back to normal
    CritterState& loserState = (winner == critter1) ? state2 : state1;
    if (loserState.isMating()) {
        loserState.matePenalty = 0;
        CritterState& mateState = _critterStateMap[loserState.mate];
        mateState.matePenalty = 0;
        loserState.mate->onMateEnd();
    }

    return winner;
}

std::vector<std::string> CritterModel::getClassNames() const {
    std::vector<std::string> names;
    for (auto it = _classStateMap.begin(); it != _classStateMap.end(); it++) {
        names.push_back(it->first);
    }
    return names;
}

const CritterState& CritterModel::getClassState(const std::string& className) const {
    return _classStateMap.at(className);
}

std::string CritterModel::getColor(int x, int y) const {
    if (!isOnBoard(x, y)) {
        return "";
    }
    return _board[x][y].color;
}

int CritterModel::getHeight() const {
    return _height;
}

std::string CritterModel::getString(int x, int y) const {
    if (!isOnBoard(x, y)) {
        return EMPTY;
    }
    return _board[x][y].display;
}

void CritterModel::getOpenNeighbors(const Point& location, std::vector<Point>& neighbors) const {
    // pick random place for a baby to appear
    for (int x = location.x - 1; x <= location.x + 1; x++) {
        for (int y = location.y - 1; y <= location.y + 1; y++) {
            int realX = (x + _width) % _width;
            int realY = (y + _height) % _height;
            if (!_board[realX][realY].critter) {
                neighbors.push_back({realX, realY});
            }
        }
    }
}

int CritterModel::getWidth() const {
    return _width;
}

std::string CritterModel::getWinningClassName() const {
    int max = 0;
    std::string maxClassName = "";
    for (std::string className : getClassNames()) {
        int total = _classStateMap.at(className).total();
        if (total > max) {
            max = total;
            maxClassName = className;
        } else if (total == max) {
            // combine the names just to make it not match
            maxClassName += "," + className;
        }
    }
    return maxClassName;
}

bool CritterModel::isBaby(int x, int y) const {
    return isOnBoard(x, y)
            && _board[x][y].critter
            && _critterStateMap.at(_board[x][y].critter).isBaby();
}

bool CritterModel::isDebug() const {
    return _debug;
}

bool CritterModel::isOnBoard(int x, int y) const {
    return 0 <= x && x < _width && 0 <= y && y < _height;
}

void CritterModel::movePoint(Point& p, Direction direction) const {
    if (direction == NORTH) {
        p.y = (p.y - 1 + _height) % _height;
    } else if (direction == SOUTH) {
        p.y = (p.y + 1) % _height;
    } else if (direction == EAST) {
        p.x = (p.x + 1) % _width;
    } else if (direction == WEST) {
        p.x = (p.x - 1 + _width) % _width;
    } // else direction == Critter.CENTER
}

void CritterModel::notifyObservers(ModelEvent event) const {
    for (ModelEventListener listener : _observers) {
        listener(event);
    }
}

void CritterModel::printDebug(const std::string& s, bool endLine) {
    if (_debug) {
        std::cout << s;
        if (endLine) {
            std::cout << std::endl;
        } else {
            std::cout.flush();
        }
    }
}

Point CritterModel::randomOpenLocation() const {
    if (_critterList.size() >= _width * _height) {
        throw std::runtime_error("CritterModel::randomOpenLocation: too many critters");
    }

    Point p = {0, 0};
    do {
        p.x = rand() % _width;
        p.y = rand() % _height;
    } while (_board[p.x][p.y].critter);
    return p;
}

void CritterModel::removeAll(const std::string& className, bool permanent) {
    for (int i = _critterList.size() - 1; i >= 0; i--) {
        Critter* critter = _critterList[i];
        if (critter->getType() == className) {
            _critterList.erase(_critterList.begin() + i);
            if (_locationMap.find(critter) == _locationMap.end()) {
                continue;
            }
            Point loc = _locationMap[critter];
            _locationMap.erase(critter);
            if (_board[loc.x][loc.y].critter == critter) {
                _board[loc.x][loc.y].critter = nullptr;
            }
        }
    }

    if (permanent) {
        _classStateMap.erase(className);
    }

    updateDisplay(REMOVE_ALL);
}

void CritterModel::reset() {
    // remove/reset all existing animals from the game
    for (Critter* critter : _critterList) {
        _critterStateMap.erase(critter);
        if (_locationMap.find(critter) != _locationMap.end()) {
            Point location = _locationMap[critter];
            _locationMap.erase(critter);
            if (_board[location.x][location.y].critter == critter) {
                _board[location.x][location.y].critter = nullptr;
            }
        }

        // notify the critter that it was reset
        critter->onReset();

        _critterList.clear();

        for (auto it = _classStateMap.begin(); it != _classStateMap.end(); it++) {
            std::string className = it->first;

            // wipe the class entry for this animal type
            CritterState& classState = it->second;

            // remove all animals of this type
            int count = classState.initialCount;
            removeAll(className, /* permanent */ false);
            classState.reset();

            // notify the class that it was reset, if method exists
            // TODO: call resetAll static method on critter class
            // idea: maybe class calls a static method on model to register a handler

            // add them back
            for (int i = 0; i < count; i++) {
                // Critter* critter =
                // add(critter);
            }
        }
    }

    createRandomFood();

    // reset class-based state (hmm, is this redundant with the above?)
    for (auto it = _critterStateMap.begin(); it != _critterStateMap.end(); it++) {
        it->second.reset();
    }
    _moveCount = 0;

    notifyObservers(RESET);
}

void CritterModel::setDebug(bool debug) {
    this->_debug = debug;
}

int CritterModel::totalCritterCount() const {
    return _locationMap.size();
}

void CritterModel::update() {
    if (_partialIndex == 0) {
        _moveCount++;
        printDebug();
        printDebug("Begin overall move #" + std::to_string(_moveCount));

        // reorder the list to be fair about move/collision order
        // TODO
        // Collections.shuffle(critterList);
    }

    if (_debug) {
        printDebug("Begin move #" + std::to_string(_moveCount) + " for critter #"
                   + std::to_string(_partialIndex + 1) + " of "
                   + std::to_string(_critterList.size()));
        updateCritter(_partialIndex);
        _partialIndex = (_partialIndex + 1) % _critterList.size();
    } else {
        // move each critter to its new position
        for (int i = _partialIndex; i < _critterList.size(); i++) {
            i = updateCritter(i);
        }
        _partialIndex = 0;
    }

    // update each animal class's state (not used much anymore)
    updateCritterClassStates();

    // now process all individual critter animals' state
    updateCritterIndividualStates();

    // respawn new f2ood periodically
    if (_moveCount % FOOD_RESPAWN_INTERVAL == 0 && (!_debug || _partialIndex == 0)) {
        Point open = randomOpenLocation();
        printDebug("  creating new food at " + to_string(open));
        _board[open.x][open.y].food = true;
    }

    updateDisplay(UPDATE);
}

int CritterModel::updateCritter(int i) {
    Critter* critter1 = _critterList[i];
    std::string className1 = className(critter1);
    CritterState& classState1 = _classStateMap[className1];
    CritterState& critterState1 = _critterStateMap[critter1];
    Point& location = _locationMap[critter1];

    printDebug("  " + to_string(_critterList[_partialIndex]) + " at " + to_string(location));

    // fill the Critter's inherited fields with info about the game state
    critter1->__setLocation(location.x, location.y);
    critter1->__setNeighbor(CENTER, _board[location.x][location.y].display);
    for (Direction dir : { CENTER, NORTH, EAST, SOUTH, WEST }) {
        _infoPoint.x = location.x;
        _infoPoint.y = location.y;
        movePoint(_infoPoint, dir);
        critter1->__setNeighbor(dir, _board[_infoPoint.x][_infoPoint.y].display);
    }

    if (classState1.isAsleep() || critterState1.isAsleep()
            || classState1.isMating() || critterState1.isMating()) {
        // this critter doesn't get to move; he is sleeping
        // from eating too much food or something
        printDebug("    asleep or mating; skipping");
        return i;
    }

    // move the critter
    _board[location.x][location.y].critter = nullptr;
    std::string critter1ToString = _board[location.x][location.y].display;
    _board[location.x][location.y].display = EMPTY;

    printDebug("    calling getMove ... ", /* endLine */ false);
    Direction move = CENTER;
    move = critter1->getMove();   // get actual move
    printDebug("returned " + to_string(move));

    Point desiredNewLocation = location;
    movePoint(desiredNewLocation, move);

    // see if anybody else is in the square critter1 moved onto
    Critter* critter2 = _board[desiredNewLocation.x][desiredNewLocation.y].critter;
    Critter* winner = critter1;
    std::string winnerToString = critter1ToString;

    if (!critter2) {
        movePoint(location, move);
        printDebug("    moving critter to " + to_string(location));
        critter1->__setLocation(location.x, location.y);
    } else {
        std::string className2 = className(critter2);
        if (className1 == className2) {
            // if two critters from same species want to move together, mate!
            // (also don't actually move the moving animal; leave them still)
            CritterState& critterState2 = _critterStateMap[critter2];
            if (!critterState1.mate && !critterState2.mate) {
                // they fall in love!
                printDebug("    mating begins at " + to_string(location)
                           + " between " + to_string(critter1)
                           + " and " + to_string(critter2));

                critterState1.mate = critter2;
                critterState2.mate = critter1;
                critterState1.matePenalty = MATING_PENALTY;
                critterState2.matePenalty = MATING_PENALTY;

                // notify the critters that they be gettin' it on
                critter1->onMate();
                critter2->onMate();
            }
        } else {
            // square is occupied by an enemy animal; fight!
            movePoint(location, move);
            printDebug("    moving critter to " + to_string(location));

            critter1->__setLocation(location.x, location.y);
            std::string critter2ToString = _board[location.x][location.y].display;

            printDebug("    fight with " + to_string(critter2));
            winner = fight(critter1, critter2, critter1ToString, critter2ToString);

            Critter* loser = (winner == critter1) ? critter2 : critter1;
            printDebug("      winner=" + to_string(winner));

            _locationMap.erase(loser);
            int indexToRemove = -1;
            if (winner == critter1) {
                auto pos = std::find(_critterList.begin(), _critterList.end(), critter2);
                if (pos != _critterList.end()) {
                    indexToRemove = std::distance(_critterList.begin(), pos);
                }
                winnerToString = critter1ToString;
            } else {
                indexToRemove = i;
                winnerToString = critter2ToString;
            }
            if (indexToRemove >= 0) {
                _critterList.erase(_critterList.begin() + indexToRemove);
                if (indexToRemove <= i) {
                    i--;  // so we won't skip a critter by mistake
                }
            }

            // TODO: update the grid and display fields if necessary
            // put null color, "." on location of loser
            // problem: if winner is still there, should put his color/toString,
            // but then we'll get them again when we call updateDisplay...
            // should only call them once per update

            // decrement various counters for each critter type
            if (winner && loser) {
                std::string winnerClassName = className(winner);
                std::string loserClassName = className(loser);
                _classStateMap[loserClassName].deaths++;
                _classStateMap[loserClassName].count--;
                if (winnerClassName != loserClassName) {
                    _classStateMap[winnerClassName].kills++;
                }
            }
            // else: a bug? fight not implemented?

            loser->__setAlive(false);
        }
    }
    _board[location.x][location.y].critter = winner;
    _board[location.x][location.y].display = winnerToString;

    if (winner == critter1) {
        // critter is still alive
        critterState1.moves++;
        if (CRITTER_MOVE_FATIGUE_COUNT > 0 && critterState1.moves % CRITTER_MOVE_FATIGUE_COUNT == 0) {
            critterState1.foodPenalty = GLUTTON_PENALTY;
            // printDebug("    moved too much; falling asleep for "
            //            + std::to_string(GLUTTON_PENALTY) + " moves");
            critter1->__setAwake(false);
            critter1->onSleep();
        } else if (_board[location.x][location.y].food) {
            // check whether this critter should eat food
            printDebug("    food found; calling eat ... ");
            bool critterEat = false;
            critterEat = critter1->eat();
            printDebug("returned " + std::string(critterEat ? "true" : "false"));
            if (critterEat) {
                _board[location.x][location.y].food = false;
                classState1.foodEaten++;
                if (_critterStateMap.find(critter1) == _critterStateMap.end()) {
                    throw std::runtime_error("Unknown critter! (this should not happen)");
                }
                critterState1.foodEaten++;

                // possibly penalize the critter for eating too much
                if (CRITTER_GLUTTON_COUNT > 0 && critterState1.foodEaten % CRITTER_GLUTTON_COUNT == 0) {
                    int penalty = GLUTTON_PENALTY;
                    if (RANDOMIZE_GLUTTON_PENALTY) {
                        // somewhere between 1 and 2*GLUTTON_PENALTY
                        penalty = rand() % (2 * GLUTTON_PENALTY) + 1;
                    }
                    critterState1.foodPenalty = penalty;

                    printDebug("    ate too much; falling asleep for "
                               + std::to_string(penalty) + " moves");
                    critter1->__setAwake(false);
                    critter1->onSleep();
                }

                // possibly penalize the species as a whole for eating too much
                if (CRITTER_CLASS_GLUTTON_COUNT > 0 && classState1.foodEaten % CRITTER_CLASS_GLUTTON_COUNT == 0) {
                    classState1.foodPenalty = GLUTTON_PENALTY;
                    printDebug("    class ate too much; falling asleep for "
                               + std::to_string(GLUTTON_PENALTY) + " moves");
                    critter1->__setAwake(false);
                    critter1->onSleep();
                }
            }
        }
    }

    return i;
}

void CritterModel::updateCritterClassStates() {
    // any sleeping classes come one step closer to waking up
    for (auto it = _classStateMap.begin(); it != _classStateMap.end(); it++) {
        CritterState& state = it->second;
        if (state.isAsleep()) {
            state.foodPenalty--;
            if (!state.isAsleep()) {
                // notify all the critters that they've woken up
                printDebug("  waking up all critters of type " + state.className);
                for (Critter* critter : _critterList) {
                    if (className(critter) == state.className) {
                        printDebug("    waking up " + to_string(critter));
                        critter->__setAwake(true);
                        critter->onWakeUp();
                    }
                }
            }
        }
    }
}

void CritterModel::updateCritterIndividualStates() {
    // (I make a copy of the map values so I won't get a modification error
    // if I add a baby to the game board in the middle of the foreach loop)
    for (auto it = _critterStateMap.begin(); it != _critterStateMap.end(); it++) {
        CritterState& state = it->second;
        if (state.isAsleep()) {
            // any sleeping animals come one step closer to waking up
            state.foodPenalty--;

            // wake him up, if neither he nor his species is asleep
            if (state.isAsleep()) {
                printDebug("  " + std::to_string(state.foodPenalty)
                           + " moves until wakeup for " + to_string(state.critter));
            } else if (_classStateMap.find(state.className) != _classStateMap.end()
                    && !_classStateMap[state.className].isAsleep()) {
                printDebug("  waking up " + to_string(state.critter));
                state.critter->__setAwake(true);
                state.critter->onWakeUp();
            }
        }
        if (state.isMating()) {
            state.matePenalty--;
            if (state.isMating()) {
                printDebug("  " + std::to_string(state.matePenalty)
                           + " moves until done mating for "
                           + to_string(state.critter) + " and "
                           + to_string(state.mate));
            } else {
                // new baby born!
                CritterState& state2 = _critterStateMap[state.mate];

                // critter 1 and 2 should be next to each other
                Point& location1 = _locationMap[state.critter];
                Point& location2 = _locationMap[state2.critter];

                // pick a random location for the baby to be born
                // (prefer a random spot that borders the parents)
                std::vector<Point> neighbors;
                getOpenNeighbors(location1, neighbors);
                getOpenNeighbors(location2, neighbors);
                std::shuffle(neighbors.begin(), neighbors.end(), std::random_device());
                Point babyLocation = neighbors.empty() ? randomOpenLocation() : neighbors[0];

                printDebug("  done mating for " + to_string(state.critter)
                           + " and " + to_string(state.mate));
                printDebug("    baby born at " + to_string(babyLocation));

                // make the baby
                Critter* baby = Nursery::makeBabyCritter(state.className);
                add(baby, babyLocation, /* isInitial */ false);
                _critterStateMap[baby].daddy = state.critter;

                // notify the critters that the boom shaka laka is over
                state.matePenalty = 0;
                state2.matePenalty = 0;
                state.critter->onMateEnd();
                state2.critter->onMateEnd();
            }
        }
    }
}

void CritterModel::updateDisplay(ModelEvent event) {
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            updateDisplaySquare(x, y);
        }
    }
    notifyObservers(event);
}

void CritterModel::updateDisplaySquare(int x, int y) {
    if (!_board[x][y].critter) {
        if (_board[x][y].food) {
            _board[x][y].display = FOOD;
            _board[x][y].color = FOOD_COLOR;
        } else {
            _board[x][y].display = EMPTY;
            _board[x][y].color = "";
        }
    } else {
        _board[x][y].display = _board[x][y].critter->toString();
        _board[x][y].color = _board[x][y].critter->getColor();
    }
}

std::ostream& operator <<(std::ostream& out, const CritterModel& model) {
    for (int y = 0; y < model._height; y++) {
        for (int x = 0; x < model._width; x++) {
            out << model._board[x][y].display;
        }
        out << std::endl;
    }
    return out;
}
