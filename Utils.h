#pragma once


#include <cstdlib>
#include <glm/glm.hpp>
#include "Constants.h"

inline double randomDouble() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * randomDouble();
}

template<typename T>
inline T clamp(T x, T min, T max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline glm::vec3 getUnitSphereRandomVec()
{
    while (true)
    {
        glm::vec3 v(randomDouble(-1,1), randomDouble(-1, 1), randomDouble(-1, 1));
        if (glm::length(v) >= 1)
            continue;
        return glm::normalize(v);
        
    }
}
