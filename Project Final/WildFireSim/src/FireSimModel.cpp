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

#include "FireSimModel.h"
#include "Burning.h"
#include "Burnt.h"
#include "Countermeasure.h"
#include "Fire.h"
#include "FireBreak.h"
#include "FireRetardant.h"
#include "Fuel.h"
#include "Grass.h"
#include "Meter.h"
#include "OldForest.h"
#include "YoungForest.h"

const vector<vector<int>> FireSimModel::POSITION_OFFSETS = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}};

const double FireSimModel::GRASS_COMBUSTION_TEMP = 300;
const double FireSimModel::YOUNGFOREST_COMBUSTION_TEMP = 500;
const double FireSimModel::OLDFOREST_COMBUSTION_TEMP = 600;
const double FireSimModel::FR_COMBUSTION_TEMP = 1000;

FireSimModel::FireSimModel(string fileName) {
    vector<vector<Meter *>> *loadWorld = new vector<vector<Meter *>>();
    ifstream input;
    input.open(fileName);
    input >> worldSize;
    // Loop through rows and columns of the given world size and populate
    // world with model objects.
    for (int row = 0; row < worldSize; row++) {
        vector<Meter *> currentRow;
        for (int col = 0; col < worldSize; col++) {
            string token;
            input >> token;
            Meter *newMeter = createMeter(token);
            currentRow.push_back(newMeter);
        }
        loadWorld->push_back(currentRow);
    }
    world = loadWorld;
}

Meter *FireSimModel::createMeter(string token) {
    if (token == "GS") {
        return new Grass(70, 0, NONE, GRASS_COMBUSTION_TEMP);
    } else if (token == "YF") {
        return new YoungForest(70, 0, NONE, YOUNGFOREST_COMBUSTION_TEMP);
    } else if (token == "OF") {
        return new OldForest(70, 0, NONE, OLDFOREST_COMBUSTION_TEMP);
    } else if (token == "FR") {
        return new FireRetardant(70, 0, NONE);
    } else if (token == "FB") {
        return new FireBreak(70, 0, NONE);
    } else if (token == "FI") {
        return new Burning(1000, 0, NONE);
    }
    return nullptr;
}

vector<vector<Meter *>> *FireSimModel::createWorld(int worldSize) {
    vector<vector<Meter *>> *world = new vector<vector<Meter *>>();
    for (int col = 0; col < worldSize; col++) {
        vector<Meter *> current;
        for (int row = 0; row < worldSize; row++) {
            current.push_back(nullptr);
        }
        world->push_back(current);
    }
    return world;
}

Meter *FireSimModel::get(int row, int col) const {
    return world->at(row)[col];
}

int FireSimModel::getWorldSize() const {
    return worldSize;
}

void FireSimModel::setWindProps(Direction direction, double windSpeed) {
    // Loop through model objects and set the wind direction and wind speed
    // properties.
    for (int row = 0; row < getWorldSize(); row++) {
        for (int col = 0; col < getWorldSize(); col++) {
            Meter *meter = world->at(row)[col];
            meter->setWindDirection(direction);
            meter->setWindSpeed(windSpeed);
        }
    }
}

void FireSimModel::cleanupMeters(vector<vector<int>> coords) {
    for (vector<int> coord : coords) {
        Meter *meter = world->at(coord[0])[coord[1]];
        delete meter;
    }
}

double FireSimModel::getTotalSpread(int row, int col) {
    vector<Direction> directions = {NORTH, EAST, SOUTH, WEST};
    double spreadFactor = 0;
    // Loop through directions to get spread values from neighboring positions.
    for (Direction d : directions) {
        int rowOffset = getDirectionOffset(d)[0];
        int colOffset = getDirectionOffset(d)[1];
        // Check if neiboring position is within the world.
        if (row + rowOffset >= 0 && col + colOffset >= 0 &&
            row + rowOffset < getWorldSize() && col + colOffset < getWorldSize()) {
            Meter *neighbor = world->at(row + rowOffset)[col + colOffset];
            // Get spread value from neighboring position in direction of current the
            // meter/position.
            spreadFactor += neighbor->spread(getOppositDirection(d));
        }
    }
    return spreadFactor;
}

void FireSimModel::tick() {
    vector<vector<Meter *>> *newWorld = createWorld(getWorldSize());
    vector<vector<int>> metersToDelete;
    for (int row = 0; row < getWorldSize(); row++) {
        for (int col = 0; col < getWorldSize(); col++) {
            Meter *meter = world->at(row)[col];
            if (meter != nullptr) {
                double spreadFactor = getTotalSpread(row, col);
                meter->update(spreadFactor);

                // TODO: we can do this more elegantly, perhaps with some binary enum flag stuff
                // For now, just ||ing them all

                // If model object type is one that can combust (Grass, YoungForest, OldForest, &
                // FireRetardant) and the object is at or above the combustion temperature, replace
                // the object with a Burning object.
                if ((meter->getType() == GRASS ||
                     meter->getType() == YOUNGFOREST ||
                     meter->getType() == OLDFOREST ||
                     meter->getType() == FIRERETARDANT) &&
                    meter->atCombustion()) {
                    newWorld->at(row)[col] = new Burning(meter->getTemperature(),
                                                         meter->getWindSpeed(),
                                                         meter->getWindDirection());

                    metersToDelete.push_back({row, col});
                    // If the model object type is Burning and fuelRemaining of the object is 0,
                    // replace the object with a Burnt object.
                } else if (meter->getType() == BURNING && meter->getFuelRemaining() == 0) {
                    newWorld->at(row)[col] = new Burnt(meter->getTemperature(),
                                                       meter->getWindSpeed(),
                                                       meter->getWindDirection());
                    metersToDelete.push_back({row, col});
                } else {
                    newWorld->at(row)[col] = meter;
                }
            }
        }
    }
    // Delete all objects that have been replaced.
    cleanupMeters(metersToDelete);
    delete world;
    world = newWorld;
}

ostream &operator<<(ostream &out, FireSimModel *model) {
    if (model->getWorldSize() > 0) {
        for (int row = 0; row < model->getWorldSize(); row++) {
            out << "[";
            out << model->get(row, 0)->toString();
            for (int col = 1; col < model->getWorldSize(); col++) {
                out << ", ";
                out << model->get(row, col)->toString();
            }
            out << "]" << endl;
        }
    }
    return out;
}
