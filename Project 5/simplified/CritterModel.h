// Allison Obourn 
// CS 132, Winter 2023
// Lecture 21

// The CritterWorld represents the world where the critters live and move around.
// It is set to a particular width and height and critters can be located in 
// any of its squares. When they move their location in the grid changes. The
// grid stores the current state of the world at any moment in time. 

#ifndef _critter_world_h_
#define _critter_world_h_ 

#include <vector>
#include "Critter.h"

using namespace std;

// the number of each critter type to initially put on the board
const int CRITTER_COUNT = 2;

// the types of critters to place on the board
const vector<string> CRITTER_TYPES = {"Stone", "Butterfly"};

// The width and height of the world grid
const int WORLD_SIZE = 10;


class CritterModel {
public:
    // creates a new world that is size wide and size tall. Fills this grid with
    // pointers to 10 Critters of each type placed in random locations and the
    // rest of the spaces with nullptr
    CritterModel();

    // creates and returns a pointer to a new critter of the passed in type
    Critter* createCritter(int type);

    // takes references to the current row and column that the critter occupies and the 
    // direction it is going to move and alters the row and column to store this new
    // position. If the critter walks off the grid it will appear on the opposite side
    // as if it walked around a sphere
    void getNewPosition(int& row, int& col, Direction d);

    // returns a pointer to the critter currently at the passed in location. If no
    // critter is there returns nullptr
    Critter* get(int row, int col);
    
    // replaces the current world grid with a new grid with all of the critters 
    // in the position that they would be in after moving one in the direction 
    // their getMove returns.
    void tick();

    // adds CRITTER_COUNT of each of the types of critters in CRITTER_TYPES to
    // the world grid in random positions. 
    void createCritters();
private:
    // creates a vector of vectors, the passed in number wide and the passed in 
    // number tall, containing nullptr in every location and returns a pointer to it.
    vector<vector<Critter*>>* createGrid();

    // the grid of rows and columns that stores pointers to Critters, representing
    // their current positions in the world.
    vector<vector<Critter*>>* world;
};

// overrides << for a pointer to a vector of vectors of pointers to critters
// outputs it with one inner vector per line surrounded by []
ostream& operator <<(ostream& out, vector<vector<Critter*>>* list);

// overrides the << operator for vectors of pointers to critters.
// prints the vector on one line surrounded by []. nullptr is represented
// as - and critters as their toString 
ostream& operator <<(ostream& out, vector<Critter*>& list);