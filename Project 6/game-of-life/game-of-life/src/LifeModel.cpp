/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #6, 02/24/23

LifeModel represents a "Game of Life" simulation where cells can grow or die depending
on the number of neighboring cells there are to any given cell. Live cells are represented
by an "X", and empty positions are drawn as a "-".
*/
#include "LifeModel.h"

const vector<vector<int>> LifeModel::OFFSETS = {
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {0, -1},
    {1, -1}};

LifeModel::LifeModel(string fileName) {
    ifstream input;
    input.open(fileName);
    int rows;
    int columns;
    input >> rows;
    input >> columns;

    // Iterate through the initialization file and create a world of live cells
    // and empty positions.
    for (int r = 0; r < rows; r++) {
        vector<bool> v;
        for (int c = 0; c < columns; c++) {
            char cell;
            input >> cell;
            if (toupper(cell) == 'X') {
                v.push_back(true);
            } else {
                v.push_back(false);
            }
        }
        world.push_back(v);
    }
}

int LifeModel::getRows() {
    return this->world.size();
}

int LifeModel::getCols() {
    return this->world[0].size();
}

bool LifeModel::isAlive(int row, int col) {
    if (row <= this->getRows() && col <= this->getCols()) {
        return this->world[row][col];
    }
    return false;
}

void LifeModel::update() {
    // Create a new world which will be filled with the updated cell positions from
    // the old world.
    vector<vector<bool>> newWorld;
    int rowSize = this->getRows();
    int columnSize = this->getCols();
    for (int r = 0; r < rowSize; r++) {
        vector<bool> v;
        for (int c = 0; c < columnSize; c++) {
            // Count all neighboring cells by looping through neighbor positions.
            int neighborCount = 0;
            for (vector<int> offset : LifeModel::OFFSETS) {
                // Check if the potential neighbor position exists within the world.
                if (r + offset[0] >= 0 && c + offset[1] >= 0 &&
                    r + offset[0] < rowSize && c + offset[1] < columnSize) {
                    neighborCount += this->isAlive(r + offset[0], c + offset[1]);
                }
            }
            // If 2 neighbors, cell is stable.
            if (neighborCount == 2) {
                v.push_back(this->world[r][c]);
                // If 3 neighbors, new cell.
            } else if (neighborCount == 3) {
                v.push_back(true);
                // Else 1 or fewer neighbors OR 4 or more neighbors, cell dies
            } else {
                v.push_back(false);
            }
        }
        newWorld.push_back(v);
    }
    // Reassign world to the new world.
    this->world = newWorld;
}

ostream &operator<<(ostream &out, LifeModel lm) {
    int rowSize = lm.getRows();
    int columnSize = lm.getCols();
    for (int r = 0; r < rowSize; r++) {
        for (int c = 0; c < columnSize; c++) {
            if (lm.isAlive(r, c)) {
                out << "X";
            } else {
                out << "-";
            }
        }
        out << endl;
    }
    return out;
}