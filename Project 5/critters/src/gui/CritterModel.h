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

#ifndef _CRITTERMODEL_H
#define _CRITTERMODEL_H

#include "Critter.h"
#include "crittertypes.h"
#include <functional>
#include <iostream>
#include <map>
#include <vector>

struct Point {
public:
    int x;
    int y;
};
std::ostream& operator <<(std::ostream& out, const Point& point);
std::string to_string(const Point& point);

struct CritterState {
public:
    CritterState();
    bool isAsleep() const;
    bool isBaby() const;
    bool isMating() const;
    void reset();
    int total() const;

    std::string className;
    Critter* critter;
    Critter* daddy;
    Critter* mate;
    int count;
    int initialCount;
    int kills;
    int deaths;
    int moves;
    int foodEaten;
    int foodPenalty;
    int matePenalty;
};

struct Square {
public:
    Square();
    Critter* critter;
    std::string display;
    std::string color;
    bool food;
};

enum ModelEvent {
    ADD, MOVE, NEW, REMOVE_ALL, RESET, UPDATE
};

typedef std::function<void(ModelEvent)> ModelEventListener;

class CritterModel {
public:
    static const std::string EMPTY; // how to display empty squares
    static const std::string WOLF_CLASS_NAME;
    static const int DEFAULT_CRITTER_COUNT;
    static const int DEFAULT_WIDTH;
    static const int DEFAULT_HEIGHT;

    static const int MATING_PENALTY;
    static const int CRITTER_GLUTTON_COUNT;
    static const int CRITTER_CLASS_GLUTTON_COUNT;
    static const int CRITTER_MOVE_FATIGUE_COUNT;
    static const int INT_PARAM_MAX;
    static const int GLUTTON_PENALTY;
    static const bool RANDOMIZE_GLUTTON_PENALTY;
    static const int FOOD_RESPAWN_INTERVAL;
    static const std::string FOOD;                 // how will food be drawn?
    static const int FOOD_PERCENTAGE;              // what % squares have food?
    static const std::string FOOD_COLOR;
    static const bool DISPLAY_BABIES;              // if true, temporarily show babies in lowercase

    CritterModel(int width = -1, int height = -1);
    void add(Critter* critter);
    void addObserver(ModelEventListener listener);
    std::vector<std::string> getClassNames() const;
    const CritterState& getClassState(const std::string& className) const;
    std::string getColor(int x, int y) const;
    int getHeight() const;
    std::string getString(int x, int y) const;
    int getWidth() const;
    std::string getWinningClassName() const;
    bool isBaby(int x, int y) const;
    bool isDebug() const;
    bool isOnBoard(int x, int y) const;
    void removeAll(const std::string& className, bool permanent = true);
    void reset();
    void setDebug(bool debug);
    void update();

private:
    void add(Critter* critter, const Point& location, bool isInitial = true);
    void createRandomFood();
    Critter* fight(Critter* critter1, Critter* critter2,
                   const std::string& critter1toString,
                   const std::string& critter2toString);
    void getOpenNeighbors(const Point& location, std::vector<Point>& neighbors) const;
    void movePoint(Point& p, Direction direction) const;
    void notifyObservers(ModelEvent event) const;
    void printDebug(const std::string& s = "", bool endLine = true);
    Point randomOpenLocation() const;
    int totalCritterCount() const;
    int updateCritter(int i);
    void updateCritterClassStates();
    void updateCritterIndividualStates();
    void updateDisplay(ModelEvent event);
    void updateDisplaySquare(int x, int y);

    int _width;
    int _height;
    int _moveCount;
    int _partialIndex;
    Point _infoPoint;
    bool _debug;
    std::vector<std::vector<Square>> _board;
    std::vector<Critter*> _critterList;
    std::vector<ModelEventListener> _observers;
    std::map<Critter*, Point> _locationMap;
    std::map<std::string, CritterState> _classStateMap;
    std::map<Critter*, CritterState> _critterStateMap;

    friend std::ostream& operator <<(std::ostream& out, const CritterModel& model);
};

std::ostream& operator <<(std::ostream& out, const CritterModel& model);

#endif // _CRITTERMODEL_H
