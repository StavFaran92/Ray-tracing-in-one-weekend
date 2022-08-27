#pragma once

#include <glm/glm.hpp>
#include "Ray.h"

class Camera
{
public:
	Camera()
	{
        // Image
        const auto aspect_ratio = 16.0 / 9.0;
        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        m_origin = glm::vec3(0, 0, 0);
        m_horizontal = glm::vec3(viewport_width, 0, 0);
        m_vertical = glm::vec3(0, viewport_height, 0);
        m_lowerLeftCorner = m_origin - m_horizontal / 2.f - m_vertical / 2.f - glm::vec3(0, 0, focal_length);
	}

    Ray getRay(float u, float v) const;
private:
	glm::vec3 m_origin;
	glm::vec3 m_lowerLeftCorner;
	glm::vec3 m_horizontal;
	glm::vec3 m_vertical;
};
