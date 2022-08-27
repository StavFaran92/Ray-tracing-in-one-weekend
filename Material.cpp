#include "Material.h"

#include "Hittable.h"
#include "Utils.h"

bool Lambertian::scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const
{
	auto scatterDir = hitRecord.normal * .8f + getUnitSphereRandomVec() * .2f;
	scatteredRay = Ray(hitRecord.point, scatterDir);
	attenuation = m_color;

	return true;
}

bool Metal::scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const
{
	glm::vec3 reflected = glm::reflect(rayInput.direction(), hitRecord.normal);
	scatteredRay = Ray(hitRecord.point, reflected);
	attenuation = m_color;

	return glm::dot(scatteredRay.direction(), hitRecord.normal) > 0;
}
