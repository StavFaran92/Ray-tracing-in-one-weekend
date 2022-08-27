#pragma once

#include <vector>

#include "Color.h"

class Blend
{
public:
	void add(Color c);
	Color get();
private:
	int m_NumOfSamples = 0;
	float m_r = 0;
	float m_g = 0;
	float m_b = 0;
};
