#pragma once

#include <glm/glm.hpp>
#include "Ray.h"

class Camera
{
public:
	Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 vup, float vfov, float aspectRatio);

    Ray getRay(float u, float v) const;
private:
	glm::vec3 m_origin;
	glm::vec3 m_lowerLeftCorner;
	glm::vec3 m_horizontal;
	glm::vec3 m_vertical;
};
