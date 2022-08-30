#include "Camera.h"
#include "Constants.h"

Camera::Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 vup, float vfov, float aspectRatio)
{
    auto theta = degrees_to_radians(vfov);
    auto h = tanf(theta / 2);
    auto viewport_height = 2.0f * h;
    auto viewport_width = aspectRatio * viewport_height;

    auto w = glm::normalize(pos - lookAt);
    auto u = glm::normalize(glm::cross(vup, w));
    auto v = glm::cross(w, u);

    auto focal_length = 1.0;

    m_origin = pos;
    m_horizontal = viewport_width * u;
    m_vertical = viewport_height * v;
    m_lowerLeftCorner = m_origin - m_horizontal / 2.f - m_vertical / 2.f - w;
}

Ray Camera::getRay(float u, float v) const
{
	return Ray(m_origin, m_lowerLeftCorner+ u * m_horizontal + v * m_vertical - m_origin);
}
