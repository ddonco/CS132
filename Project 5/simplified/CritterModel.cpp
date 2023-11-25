// Allison Obourn 
// CS 132, Winter 2023
// Lecture 20

// Implementation of the critter model functions

#include <iostream>
#include "CritterModel.h"
#include "Butterfly.h"
#include "Stone.h"


CritterModel::CritterModel() {
    // creates a vector grid that is WORLD_SIZE by WORLD_SIZE and fills each
    // spot in it with null
    world = createGrid(); 

    // populates the grid with critters 
    createCritters();
}

// returns a pointer to the critter currently at the passed in location. If no
// critter is there returns nullptr
Critter* CritterModel::get(int row, int col) {
    return world->at(row)[col];
}

// takes the name of a critter type as a parameter and returns a 
// pointer to a new instance of that critter. If that critter type
// isn't in CRITTER_TYPES it returns null
Critter* CritterModel::createCritter(int type) {
    if(CRITTER_TYPES[type] == "Stone") {
        return new Stone();
    } else if (CRITTER_TYPES[type] == "Butterfly") {
        return new Butterfly();
    }
    return nullptr;
}


// creates and returns a pointer to a grid of critter pointers. The grid
// will be square and WORLD_SIZE tall and wide. Every spot in it will contain
// nullptr
vector<vector<Critter*>>* CritterModel::createGrid() {
    vector<vector<Critter*>>* world = new vector<vector<Critter*>>();
    for(int col = 0; col < WORLD_SIZE; col++) {
        vector<Critter*> current;
        for(int row = 0; row < WORLD_SIZE; row++) {
            current.push_back(nullptr);
        }
        world->push_back(current);
    }
    return world;
}


// takes references to the current row and column that the critter occupies and the 
// direction it is going to move and alters the row and column to store this new
// position. If the critter walks off the grid it will appear on the opposite side
// as if it walked around a sphere
void CritterModel::getNewPosition(int& row, int& col, Direction d) {
    // mod by the world size so we reapear when we walk off the grid
    if(d == NORTH) {
        row = (row - 1 + WORLD_SIZE) % WORLD_SIZE;                  
    } else if(d == SOUTH) {
        row = (row + 1) % WORLD_SIZE;
    } else if(d == EAST) {
        col = (col + 1) % WORLD_SIZE;
    } else if(d == WEST) {
        col = (col - 1 + WORLD_SIZE) % WORLD_SIZE;
    }
}



// replaces the current world grid with a new grid with all of the critters 
// in the position that they would be in after moving one in the direction 
// their getMove returns.
void CritterModel::tick() {       
    vector<vector<Critter*>>* newWorld = createGrid();  
    for(int row = 0; row < WORLD_SIZE; row++) {
        for(int col = 0; col < WORLD_SIZE; col++) {
            // gets the critter at the current spot
            Critter* critter = world->at(row)[col];
            // only move our critter if there is a critter
            if(critter != nullptr) {
                // remove from old grid
                world->at(row)[col] = nullptr; 
                // get the direction the critter should move next and alter the 
                // row and column to be that new position
                Direction d = critter->getMove();
                getNewPosition(row, col, d);
                // place the critter in the new location in the new world
                newWorld->at(row)[col] = critter;
                
            }
        }
    }
    // replace the old world with the new one
    delete world;
    world = newWorld;  
}


// adds CRITTER_COUNT of each of the types of critters in CRITTER_TYPES to
// the world grid in random positions.
void CritterModel::createCritters() {
    for(int j = 0; j < CRITTER_TYPES.size(); j++) {
        for(int i = 0; i < CRITTER_COUNT; i++) {  
            int x = rand() % WORLD_SIZE;
            int y = rand() % WORLD_SIZE;
            if(world->at(x)[y] == nullptr) {
                world->at(x)[y] = createCritter(j);
            }
        }
    }
}


// overrides << for a pointer to a vector of vectors of pointers to critters
// outputs it with one inner vector per line surrounded by []
ostream& operator <<(ostream& out, vector<vector<Critter*>>* list) {
    out << "[";
    if(list->size() > 0) {
        out << list->at(0);
        for(int i = 1; i < list->size(); i++) {
            out << endl << list->at(i);
        }
    }
    out << "]" << endl;
    return out;
}



// overrides the << operator for vectors of pointers to critters.
// prints the vector on one line surrounded by []. nullptr is represented
// as - and critters as their toString
ostream& operator <<(ostream& out, vector<Critter*>& list) {
    out << "[";
    for(int i = 0; i < list.size(); i++) {
        if(list[i] == nullptr) {
            out << "- ";
        } else {
            out << list[i]->toString() << " ";
        }
    }
    out << "]" << endl;
    return out;
}