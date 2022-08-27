#pragma once

#include "Hittable.h"
#include "Ray.h"

class Sphere : public Hittable {
public:
    Sphere() = delete;
    Sphere(glm::vec3 center, double r) : m_center(center), m_radius(r) {};

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

private:
    glm::vec3 m_center;
    float m_radius;
};