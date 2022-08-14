#pragma once
#include "Ray.h"

struct HitRecord {
    glm::vec3 p;
    glm::vec3 normal;
    double t;
};

class Hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};