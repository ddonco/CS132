/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #2, 01/20/23

The Tile class is used to build and draw tile objects on a GWindow. It also has a
contains method to check if a tile contains any given (x, y) point.
*/

#include "Tile.h"
#include <iostream>

using namespace std;
using namespace sgl;

/*
Tile constructor, top left corner of the tile is specified by the x and y properties,
tile width and height are specified by the w and h properties, tile color is specified
using the color property.
Properties:
    x       int     Tile top left x coordinate.
    y       int     Tile top left y coordinate.
    w       int     Tile width.
    h       int     Tile height.
    color   string  Tile color.
*/
Tile::Tile(int x, int y, int w, int h, string color) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->color = color;
}

/*
getX returns the x coordinate of the tile.
Parameters:
    None
Returns:
    x       int     Tile x coordinate.
*/
int Tile::getX() const {
    return this->x;
}

/*
getY returns the y coordinate of the tile.
Parameters:
    None
Returns:
    y       int     Tile x coordinate.
*/
int Tile::getY() const {
    return this->y;
}

/*
getwidth returns the width of the tile.
Parameters:
    None
Returns:
    width   int     Tile width.
*/
int Tile::getWidth() const {
    return this->w;
}

/*
getHeight returns the height of the tile.
Parameters:
    None
Returns:
    height  int     Tile height.
*/
int Tile::getHeight() const {
    return this->h;
}

/*
getColor returns the color of the tile.
Parameters:
    None
Returns:
    color   int     Tile color.
*/
string Tile::getColor() const {
    return this->color;
}

/*
contains is used to check if a point lies within a tile.
Parameters:
    x           int     The x coordinate of a point.
    y           int     The y coordinate of a point.
Returns:
    contains    bool    True if the point lies within a tile.
*/
bool Tile::contains(int x, int y) {
    return (x >= this->x && x < this->x + this->w &&
            y >= this->y && y < this->y + this->h);
}

/*
draw is used to draw a tile on a window, the window to be drawn on is passed
in as a reference parameter.
Parameters:
    window      GWindow     A window on which a tile will be drawn.
Returns:
    None
*/
void Tile::draw(GWindow &window) {
    window.setFillColor(this->color);
    window.fillRect(this->x, this->y, this->w, this->h);
}

/*
print is used to print a string representation of a properties tiles.
Parameters:
    None
Returns:
    None
*/
void Tile::print() const {
    cout << "x = " << this->x;
    cout << ", y = " << this->y;
    cout << ", width = " << this->w;
    cout << ", height = " << this->h;
    cout << ", color = " << this->color << endl;
}