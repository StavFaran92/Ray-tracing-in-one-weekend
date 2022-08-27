#include "Sphere.h"

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
    rec.point = r.at(rec.t);
    glm::vec3 outwardNormal = (rec.point - m_center) / m_radius;
    rec.setFaceNormal(r, outwardNormal);
    rec.material = m_material;

    return true;
}