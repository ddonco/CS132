#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(int randSeed):randSeed(randSeed),initSeed(randSeed){}

int PerlinNoise::bigRand() {
    return randSeed = (randSeed * 1103515245 + 12345);
}

double PerlinNoise::smooth(double a, double b, double weight) const{
    double diff = b - a;
    //return diff * weight + a;
    return diff * (3.0 - weight * 2.0) * weight * weight + a;
    //return diff * ((weight * (weight * 6.0 - 15.0) + 10.0) * weight * weight * weight) + a;
}

vec2D PerlinNoise::randomVec(int x, int y){
    randSeed = initSeed;
    unsigned a = x, b = y;
    a *= bigRand();
    b ^= a << uHalfBits | a >> uBits-uHalfBits;
    b *= bigRand();
    a ^= b << uHalfBits | b >> uBits-uHalfBits;
    a *= bigRand();
    double random = a * (M_PI / (INT_MAX / 2 + 1));
    vec2D vec;
    vec.x = cos(random);
    vec.y = sin(random);
    return vec;
}

double PerlinNoise::dotProdRandVec(int gridX, int gridY, double x, double y){
    vec2D vec = randomVec(gridX, gridY);

    //distances
    double dx = x - gridX;
    double dy = y - gridY;

    //dot product
    return dx * vec.x + dy * vec.y;
}

void PerlinNoise::newSeed(int randSeed) {
    this->randSeed = randSeed;
    this->initSeed = randSeed;
}
double PerlinNoise::valAtPos(double x, double y, double zoom){
    x /= zoom;
    y /= zoom;
    int x0 = (int)floor(x);
    int x1 = x0 + 1;
    int y0 = (int)floor(y);
    int y1 = y0 + 1;

    double sx = x - (double)x0;
    double sy = y - (double)y0;
    double n0, n1, ix0, ix1, value;

    n0 = dotProdRandVec(x0, y0, x, y);
    n1 = dotProdRandVec(x1, y0, x, y);
    ix0 = smooth(n0, n1, sx);

    n0 = dotProdRandVec(x0, y1, x, y);
    n1 = dotProdRandVec(x1, y1, x, y);
    ix1 = smooth(n0, n1, sx);

    value = smooth(ix0, ix1, sy);
    return (value * 0.5) + 0.5;
}
