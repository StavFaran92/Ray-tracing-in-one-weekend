#include "Blend.h"

void Blend::add(Color c)
{
	m_r += c.r();
	m_g += c.g();
	m_b += c.b();
	m_NumOfSamples++;
}

Color Blend::get()
{
	return Color(m_r / m_NumOfSamples, m_g / m_NumOfSamples, m_b / m_NumOfSamples);
}
