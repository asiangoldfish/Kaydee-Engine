/**
 * Random number generator module
 *
 * @file main.cpp
 * @author your name (you@domain.com)
 */

#ifndef RNG_H
#define RNG_H

#include <random>
#include <iostream>

float
rng()
{
    // Setup random number generator
    std::random_device rnddev;
    std::mt19937 gen(rnddev());
    std::uniform_real_distribution<float> dist(0.f, 1.f);

    float myRandomNumber = dist(gen);

    return myRandomNumber;
}

float
rng(float low, float high)
{
    return rng() * (high - low) + low;
}

#endif