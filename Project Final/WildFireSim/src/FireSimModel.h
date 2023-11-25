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

#ifndef _FIRESIMMODEL_H
#define _FIRESIMMODEL_H

#include <fstream>
#include <iostream>
#include <string>

#include "Meter.h"
#include "Utilities.h"

using namespace std;

class FireSimModel {
public:
    // POSITION_OFFSETS is a vector if {row, col} vectors representing neighbor
    // offsets from any given position in the world.
    static const vector<vector<int>> POSITION_OFFSETS;
    // Grass combustion temperature;
    static const double GRASS_COMBUSTION_TEMP;
    // YoungForest combustion temperature;
    static const double YOUNGFOREST_COMBUSTION_TEMP;
    // OldForest combustion temperature;
    static const double OLDFOREST_COMBUSTION_TEMP;
    // FireRetardant combustion temperature;
    static const double FR_COMBUSTION_TEMP;


    /**
     * @brief FireSimModel constructor takes a file name to load a starting model by first reading
    the model size from the file, followed by the position of each class instance in the
    model.
     * @param fileName string A model text file used to load a starting mod
     */
    FireSimModel(string fileName);

    /**
     * @brief get Returns the pointer at a particular row and column position of the model
     * @param row A row in the model.
     * @param col A col in the model.
     * @return A pointer to a Meter, or subclass, object.
     */
    Meter *get(int row, int col) const;

    /**
     * @brief getWorldSize returns the size of the model. The model is a square, so this size reflects
    both the row and column dimensions.
     * @return The row/column size of the model.
     */
    int getWorldSize() const;

    /**
     * @brief setWindProps used to set the wind direction and wind speed for all model objects. This is
    primarily used to update model objects after initialization of the model.
     * @param direction Wind direction.
     * @param windSpeed Wind speed.
     */
    void setWindProps(Direction direction, double windSpeed);


    /**
     * @brief tick used to advance the model forward one time step and update each position in the model.
     */
    void tick();

private:
    // The number of positions in the world in both the x and y directions.
    int worldSize;
    // A grid of rows and columns that stores pointers to Meter objects which represent
    // a square meter in the model world.
    vector<vector<Meter *>> *world;

    /*
    createMeter is used to map a string abreviation to one of the available model classes.
    Abreviation to class mappings are as follows:
        Grass = GS
        YF = YoungForest
        OF = OldForest
        FR = FireRetardant
        FB = FireBreak
        FI = Burning
    Parameters:
        token       string      A string abreviation of a model class.
    Returns:
        object      *Meter      A pointer to a Meter, or subclass, object.
    */
    Meter *createMeter(string token);

    /*
    createWorld is used to create a vector of vectors with height and width equal to
    the passed in worldSize parameter. Each position in the model is initialized
    with a nullptr. This method returns a pointer to the generated world.
    Parameters:
        worldSize   int     The model world size for both the x and y directions.
    Returns:
        world       vector<vector<Meter *>>     A world model consisting of a vector of
                                                vector of Meter pointers.
    */
    vector<vector<Meter *>> *createWorld(int worldSize);
    /*
    getTotalSpread is used to loop through the possible neighboring positions of the given row, col
    position and sum of the spread values of these positions in the direction of the given
    position.
    */
    double getTotalSpread(int row, int col);
    /*
    cleanupMeters is used to delete Meter, or subclass, objects from the world using the row,
    column coordinates of the objects.
    Parameters:
        coords      vector<vector<int>>     A vector of row, column coordinates of objects in the
                                            world that will be deleted.
    Returns:
        none
    */
    void cleanupMeters(vector<vector<int>> coords);
};

/*
Operator overload for << to send a string representation of a FireSimModel to an ostream.
*/
ostream &operator<<(ostream &out, FireSimModel *model);

#endif
