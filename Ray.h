#pragma once

#include "glm/glm.hpp"

class Ray {
public:
    Ray() = delete;
    Ray(const glm::vec3& origin, const glm::vec3& direction)
        : orig(origin), dir(direction)
    {}

    glm::vec3 origin() const { return orig; }
    glm::vec3 direction() const { return dir; }

    glm::vec3 at(float t) const {
        return orig + dir * t;
    }

public:
    glm::vec3 orig;
    glm::vec3 dir;
};