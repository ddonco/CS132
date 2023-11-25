/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #2, 01/20/23

The TileManager class is used to store tiles objects in a tiles vector, manipulate
the order of the tiles in the vector, and draw the tiles on a GWindow. The
TileManager also provides methods to highlight a tile with a thick yellow border,
remove tiles, add tiles, and clear all tiles.
*/

#include "TileManager.h"
#define HIGHLIGHT_COLOR "yellow"
#define HIGHLIGHT_THICKNESS 10
using namespace std;

/*
TileManager constuctor.
*/
TileManager::TileManager() {}

/*
addBottom is used to add a tile to the tiles vector of the TileManager. The tile
is added to the beginning of the vector such that it will be drawn first.
Parameters:
    rect    Tile    A tile to be added to the beginning of the tiles vector.
Returns:
    None
*/
void TileManager::addBottom(const Tile &rect) {
    this->tiles.insert(this->tiles.begin(), rect);
}

/*
addTop is used to add a tile to the tiles vector of the TileManager. The tile
is added to the end of the vector such that it will be drawn last.
Parameters:
    rect    Tile    A tile to be added to the end of the tiles vector.
Returns:
    None
*/
void TileManager::addTop(const Tile &rect) {
    this->tiles.insert(this->tiles.end(), rect);
}

/*
drawAll is used to draw all tiles on a window. The tile border color is set to black
and the border line width is set to 1 such that any time the tiles are drawn/redrawn
they will have their default appearance.
Parameters:
    window      GWindow     A window onto which the tiles are drawn.
Returns:
    None
*/
void TileManager::drawAll(GWindow &window) {
    window.setColor("black");
    window.setLineWidth(1);
    for (int i = 0; i < this->tiles.size(); i++) {
        this->tiles[i].draw(window);
    }
}

/*
clear is used to clear all tiles from the tiles vector.
Parameters:
    None
Returns:
    None
*/
void TileManager::clear() {
    this->tiles.clear();
}

/*
highlight is used to draw a wide yellow border around a tile. The tile to be highlighted
is the top most tile containing the passed in x and y coordinates.
Parameters:
    x       int     The x coordinate of a point.
    y       int     The y coordinate of a point.
    window  GWindow The window on which the highlighted borders are drawn.
Returns:
    None
*/
void TileManager::highlight(int x, int y, GWindow &window) {
    bool found = false;
    for (int i = this->tiles.size() - 1; i >= 0 && found == false; i--) {
        if (this->tiles[i].contains(x, y)) {
            window.setColor("yellow");
            window.setLineWidth(10);
            int rectX = this->tiles[i].getX() - HIGHLIGHT_THICKNESS / 2;
            int rectY = this->tiles[i].getY() - HIGHLIGHT_THICKNESS / 2;
            int rectW = this->tiles[i].getWidth() + HIGHLIGHT_THICKNESS / 2;
            int rectH = this->tiles[i].getHeight() + HIGHLIGHT_THICKNESS / 2;
            window.drawRect(rectX, rectY, rectW, rectH);
            found = true;
        }
    }
}

/*
raise is used to move a tile to the end of the tiles vector, the tile to be moved is
the top most tile containing the passed in x and y coordinates.
Parameters:
    x       int     The x coordinate of a point.
    y       int     The y coordinate of a point.
Returns:
    None
*/
void TileManager::raise(int x, int y) {
    bool found = false;
    for (int i = this->tiles.size() - 1; i >= 0 && found == false; i--) {
        if (this->tiles[i].contains(x, y)) {
            this->tiles.push_back(this->tiles[i]);
            this->tiles.erase(this->tiles.begin() + i, this->tiles.begin() + i + 1);
            found = true;
        }
    }
}

/*
lower is used to move a tile to the beginning of the tiles vector, the tile to be moved is
the top most tile containing the passed in x and y coordinates.
Parameters:
    x       int     The x coordinate of a point.
    y       int     The y coordinate of a point.
Returns:
    None
*/
void TileManager::lower(int x, int y) {
    bool found = false;
    for (int i = this->tiles.size() - 1; i >= 0 && found == false; i--) {
        if (this->tiles[i].contains(x, y)) {
            Tile moveTile = this->tiles[i];
            this->tiles.erase(this->tiles.begin() + i, this->tiles.begin() + i + 1);
            this->tiles.insert(this->tiles.begin(), moveTile);
            found = true;
        }
    }
}

/*
remove is used to delete a tile from the tiles vector, the tile to be removed is
the top most tile containing the passed in x and y coordinates.
Parameters:
    x       int     The x coordinate of a point.
    y       int     The y coordinate of a point.
Returns:
    None
*/
void TileManager::remove(int x, int y) {
    bool found = false;
    for (int i = this->tiles.size() - 1; i >= 0 && found == false; i--) {
        if (this->tiles[i].contains(x, y)) {
            this->tiles.erase(this->tiles.begin() + i, this->tiles.begin() + i + 1);
            found = true;
        }
    }
}

/*
removeAll is used to delete all tile from the tiles vector that containe the passed
in x and y coordinates.
Parameters:
    x       int     The x coordinate of a point.
    y       int     The y coordinate of a point.
Returns:
    None
*/
void TileManager::removeAll(int x, int y) {
    for (int i = this->tiles.size() - 1; i >= 0; i--) {
        if (this->tiles[i].contains(x, y)) {
            this->tiles.erase(this->tiles.begin() + i, this->tiles.begin() + i + 1);
        }
    }
}