/**
 * @file PerlinNoise.h
 * @brief A Class for generating Perlin noise. Largely based upon the wikipedia example.
 * @author Lucas Henderson & various wikipedia users (see page history)
 * @date 3/11/2023
 *
 *  https://en.wikipedia.org/wiki/Perlin_noise#Implementation
 *  Differences:
 *  * Has been refactored into a class
 *  * Uses a seedable PRNG
 */

#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <cmath>
#include <cstdlib>
#include <limits.h>


/**
 * Pair of Double coordinates
 */

typedef struct vec2D{
    double x, y;
} vec2D;

class PerlinNoise {
public:
    /**
     * @brief PerlinNoise Constructs a new Perlin noise generator with the provided seed
     * @param randSeed The seed to use for noise generation
     */
    PerlinNoise(int randSeed);
    /**
     * @brief newSeed Sets a new seed for the noise generation
     * @param randSeed The new seed to use for noise generation
     */
    void newSeed(int randSeed);
    /**
     * @brief valAtPos calculates the value at a given point on the Perlin noise field, at a given
     * zoom level
     * @param x The x coordinate at which to calculate the value
     * @param y The y coordinate at which to calculate the value
     * @param zoom The scaling factor; Lower = busier/noisier patterns, higher = smoother patterns
     *
     * @return A value between 0.0 and 1.0; however the current implemntation tends to range from about
     * .25 to .75
     */
    double valAtPos(double x, double y, double zoom);
private:
    /**
     * @brief randSeed The random seed's current value
     */
    int randSeed;
    /**
     * @brief initSeed The initial random seed
     */
    int initSeed;
    /**
     * @brief bigRand Unix-style PRNG, because MS-Style 32768 maximum is undesirable, and cross-
     * platform consistency is nice
     * @return A (pseudo)-random value between 0 and 2147483647
     */
    int bigRand();

    /**
     * @brief smooth Interpolates between two values with a provided weight
     * @param a The first value
     * @param b The second value
     * @param weight The weight to use for interpolation between the two values
     * @return
     */
    double smooth(double a, double b, double weight) const;

    /**
     * @brief randomVec Generates a random vector based upon the internal PRNG and the provided X/Y coords
     * @param x The X coordinate
     * @param y The Y coordinate
     * @return
     */
    vec2D randomVec(int x, int y);

    /**
     * @brief dotProdRandVec Provides the dot-product of the grid/precise coordinates and a random
     * vector
     * @param gridX The X grid coordinate
     * @param gridY The Y grid coordinate
     * @param x The precise X coordinate
     * @param y The precise Y coordinate
     * @return The calculated dot-product.
     */
    double dotProdRandVec(int gridX, int gridY, double x, double y);
    /**
     * @brief uBits the bit size of an unsigned int for the platform
     */
    const unsigned uBits = 8 * sizeof(unsigned);
    /**
     * @brief uHalfBits Half the bit size of an unsigned int; used for bit-shifting purposes.
     */
    const unsigned uHalfBits = 4 * sizeof(unsigned);
};

#endif // PERLINNOISE_H
