#pragma once

#include <vector>

#include "Color.h"

class Blend
{
public:
	void addColor(Color c);
	Color getBlend();
private:
	int m_NumOfSamples = 0;
	float m_r = 0;
	float m_g = 0;
	float m_b = 0;
};
