#pragma once

#include "Ray.h"
#include "Color.h"

struct HitRecord;

class Material
{
public:
	virtual bool scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const Color& c) : m_color(c) {}

	bool scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override;

private:
	Color m_color;
};

class Metal : public Material
{
public:
	Metal(const Color& c, float fuzz) : m_color(c), m_fuzz(fuzz < 1 ? fuzz : 1) {}

	bool scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override;

private:
	Color m_color;
	float m_fuzz;
};

class Dielectric : public Material
{
public:
	Dielectric(float refractIndex) : m_refractIndex(refractIndex) {}

	bool scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override;

	static double reflectance(double cosine, double ref_idx) {
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

private:
	float m_refractIndex;
};
