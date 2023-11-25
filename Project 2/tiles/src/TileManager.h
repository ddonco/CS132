#ifndef _TileManager_h
#define _TileManager_h
#include "Tile.h"
#include <vector>

using namespace std;
using namespace sgl;

class TileManager {
public:
    TileManager();
    void addBottom(const Tile &rect);
    void addTop(const Tile &rect);
    void drawAll(GWindow &window);
    void clear();
    void highlight(int x, int y, GWindow &window);
    void raise(int x, int y);
    void lower(int x, int y);
    void remove(int x, int y);
    void removeAll(int x, int y);

private:
    vector<Tile> tiles;
};

#endif