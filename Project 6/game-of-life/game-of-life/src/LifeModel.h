/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #6, 02/24/23

LifeModel represents a "Game of Life" simulation where cells can grow or die depending
on the number of neighboring cells there are to any given cell. Live cells are represented
by an "X", and empty positions are drawn as a "-".
*/

#ifndef _LIFEMODEL_H
#define _LIFEMODEL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class LifeModel {
public:
    // A vector of vector of ints representing position offsets to be used when checking
    // the neighboring positions of any given position in the model.
    static const vector<vector<int>> OFFSETS;

    /*
    The LifeModel constructor takes a file name string for a file which will be used to initialize
    the game of life. The first line of the file is an integer representing the number of rows
    in the model. The second line of the file is an integer representing the number of columns.
    The remaining lines represent the positions of all live cells at their initial positions.
    Parameters:
        fileName    string      The file name for an initialization file.
    */
    LifeModel(string fileName);
    /*
    getRows returns the number of rows in the LifeModel.
    Parameters:
        none
    Returns:
        rows    int     The number of rows.
    */
    int getRows();
    /*
    geCols returns the number of columns in the LifeModel.
    Parameters:
        none
    Returns:
        cols    int     The number of columns.
    */
    int getCols();
    /*
    isAlive returns a boolean value representing whether or not a given position in the
    model contains a live cell. True indicates a live cell at the provided position.
    Parameters:
        row     int     A row position in the model.
        col     int     A column position in the model.
    Returns:
        alive   bool    True if the provided position contains a live cell.
    */
    bool isAlive(int row, int col);
    /*
    update will advance the model one time step causing cells to die and generate according
    to the rules of the game of life.
    Parameters:
        none
    Returns:
        none
    */
    void update();

private:
    // The game of life model represented as a vector of vector of boolean values.
    vector<vector<bool>> world;
};

/*
Operator override for << is used to print the model to the console. "X" are live cells,
"-" are empty positions.
Parameters:
    none
Returns:
    none
*/
ostream &operator<<(ostream &out, LifeModel lm);

#endif