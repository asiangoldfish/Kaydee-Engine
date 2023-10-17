#pragma once

/**
 * Random number generator module
 *
 * @file main.cpp
 * @author your name (you@domain.com)
 */

#include <random>
#include <iostream>

namespace Random {
    float rng()
    {
        // Setup random number generator
        static std::random_device rnddev;
        static std::mt19937 gen(rnddev());
        static std::uniform_real_distribution<float> dist(0.f, 1.f);

        return dist(gen);

    }

    float rng(float low, float high)
    {
        return rng() * (high - low) + low;
    }
}
