#ifndef _Tile_h
#define _Tile_h
#include "gwindow.h"
#include <string>
using namespace std;
using namespace sgl;

class Tile {
public:
    Tile(int x, int y, int w, int h, string color);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    string getColor() const;
    bool contains(int x, int y);
    void draw(GWindow &window);
    void print() const;

private:
    int x;
    int y;
    int w;
    int h;
    string color;
};

#endif