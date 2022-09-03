#include "Material.h"

#include "Hittable.h"
#include "Utils.h"

bool Lambertian::scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const
{
	auto scatterDir = hitRecord.normal + getUnitSphereRandomVec();

	if (nearZero(scatterDir))
		scatterDir = hitRecord.normal;

	scatteredRay = Ray(hitRecord.point, scatterDir);
	attenuation = m_color;

	return true;
}

bool Metal::scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const
{
	glm::vec3 reflected = glm::reflect(rayInput.direction(), hitRecord.normal);
	scatteredRay = Ray(hitRecord.point, reflected + m_fuzz * getUnitSphereRandomVec());
	attenuation = m_color;

	return glm::dot(scatteredRay.direction(), hitRecord.normal) > 0;
}

bool Dielectric::scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const
{
	attenuation = Color(1.f, 1.f, 1.f);
	float refractRatio = hitRecord.isFrontFace ? (1.f / m_refractIndex) : m_refractIndex;

	glm::vec3 unitDir = glm::normalize(rayInput.direction());

	double cos_theta = fmin(glm::dot(-unitDir, hitRecord.normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refract = refractRatio * sin_theta > 1.0;
	glm::vec3 direction;

	if (cannot_refract || reflectance(cos_theta, refractRatio) > randomDouble())
		direction = glm::reflect(unitDir, hitRecord.normal);
	else
		direction = glm::refract(unitDir, hitRecord.normal, refractRatio);

	scatteredRay = Ray(hitRecord.point, direction);

	return true;
}
