#ifndef NEWMAP_H
#define NEWMAP_H

#include <iostream>
#include <fstream>
#include <string>
#include "PerlinNoise.h"
#include <ctime>
#include <cstdlib>


using namespace std;

class NewMap {
public:
    NewMap(string fileName, int size);
};

#endif // NEWMAP_H
