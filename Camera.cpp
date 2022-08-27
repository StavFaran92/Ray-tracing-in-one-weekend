#include "Camera.h"

Ray Camera::getRay(float u, float v) const
{
	return Ray(m_origin, m_lowerLeftCorner+ u * m_horizontal + v * m_vertical - m_origin);
}
