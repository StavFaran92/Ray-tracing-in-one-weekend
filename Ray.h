#pragma once

#include "glm/glm.hpp"

class Ray {
public:
    Ray() 
        :orig(glm::vec3(0,0,0)), dir(glm::vec3(0, 0, 0))
    {};

    Ray(const glm::vec3& origin, const glm::vec3& direction)
        : orig(origin), dir(direction)
    {}

    inline glm::vec3 origin() const { return orig; }
    inline glm::vec3 direction() const { return dir; }

    glm::vec3 at(float t) const;

public:
    glm::vec3 orig;
    glm::vec3 dir;
};