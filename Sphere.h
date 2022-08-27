#pragma once

#include <memory>

#include "Hittable.h"
#include "Ray.h"
#include "Material.h"

class Sphere : public Hittable {
public:
    Sphere() = delete;
    Sphere(glm::vec3 center, double r, std::shared_ptr<Material> material) : m_center(center), m_radius(r), m_material(material) {};

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

private:
    glm::vec3 m_center;
    float m_radius;
    std::shared_ptr<Material> m_material;
};