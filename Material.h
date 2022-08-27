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
	Metal(const Color& c) : m_color(c) {}

	bool scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override;

private:
	Color m_color;
};
