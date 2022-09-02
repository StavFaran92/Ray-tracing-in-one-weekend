#include "Color.h"
#include <cmath>

#define CLAMP_COLOR(c) \
if(c < 0) \
	c = 0; \
else if(c > 1) \
	c = 1;
#define CLAMP_COLORS(r, g, b) \
	CLAMP_COLOR(r) \
	CLAMP_COLOR(g) \
	CLAMP_COLOR(b) \

void Color::getAsUnsignedChar(unsigned char& r, unsigned char& g, unsigned char& b) const
{
    r = static_cast<unsigned char>(m_r * 255.999f);
    g = static_cast<unsigned char>(m_g * 255.999f);
    b = static_cast<unsigned char>(m_b * 255.999f);
}

void Color::applyGammaCorrection(float factor)
{
    m_r = powf(m_r, 1 / factor);
    m_g = powf(m_g, 1 / factor);
    m_b = powf(m_b, 1 / factor);
}

Color Color::operator*=(const float u)
{
	m_r *= u;
	m_g *= u;
	m_b *= u;

	CLAMP_COLORS(m_r, m_g, m_b);

	return *this;
}

Color Color::operator+=(const Color& other)
{
	m_r += other.m_r;
	m_g += other.m_g;
	m_b += other.m_b;

	CLAMP_COLORS(m_r, m_g, m_b);

	return *this;
}

Color Color::operator-=(const Color& other)
{
	m_r -= other.m_r;
	m_g -= other.m_g;
	m_b -= other.m_b;

	CLAMP_COLORS(m_r, m_g, m_b);

	return *this;
}

Color operator*(const Color& c, const float u)
{
	auto r = c.r() * u;
	auto g = c.g() * u;
	auto b = c.b() * u;

	CLAMP_COLORS(r, g, b);

	return Color(r, g, b);
}

Color operator*(const float u, const Color& c)
{
	return c * u;
}

Color operator+(const Color& c1, const Color& c2)
{
	auto r = c1.r() + c2.r();
	auto g = c1.g() + c2.g();
	auto b = c1.b() + c2.b();


	CLAMP_COLORS(r, g, b);

	return Color(r, g, b);
}

Color operator*(const Color& c1, const Color& c2)
{
	auto r = c1.r() * c2.r();
	auto g = c1.g() * c2.g();
	auto b = c1.b() * c2.b();


	CLAMP_COLORS(r, g, b);

	return Color(r, g, b);
}