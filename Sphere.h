#pragma once

#include "Hittable.h"
#include "Ray.h"

class Sphere : public Hittable {
public:
    Sphere() {}
    Sphere(glm::vec3 center, double r) : m_center(center), m_radius(r) {};

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

public:
    glm::vec3 m_center;
    float m_radius;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    glm::vec3 oc = r.origin() - m_center;
    auto a = glm::dot(r.direction(), r.direction());
    auto b_half = glm::dot(r.direction(), oc);
    auto c = glm::dot(oc, oc) - m_radius * m_radius;
    float discriminant = b_half * b_half - a * c;
    if (discriminant < 0)
        return false;

    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-b_half - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-b_half + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - m_center) / m_radius;

    return true;
}