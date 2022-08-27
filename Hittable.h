#pragma once
#include "Ray.h"

struct HitRecord {
    glm::vec3 point;
    glm::vec3 normal;
    double t;
    bool isFrontFace;

    inline void setFaceNormal(const Ray& r, const glm::vec3& outwardNormal)
    {
        isFrontFace = glm::dot(r.direction(), outwardNormal) < 0;
        normal = isFrontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};