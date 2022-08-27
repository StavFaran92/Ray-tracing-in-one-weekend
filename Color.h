#pragma once

#define CLAMP_COLOR(c) \
if(c < 0) \
	c = 0; \
else if(c > 1) \
	c = 1;
#define CLAMP_COLORS(r, g, b) \
	CLAMP_COLOR(r) \
	CLAMP_COLOR(g) \
	CLAMP_COLOR(b) \

class Color
{
public:
	Color(float r, float g, float b)
		: m_r(r), m_g(g), m_b(b) 
	{}

	Color operator*=(const float u)
	{
		m_r *= u;
		m_g *= u;
		m_b *= u;

		CLAMP_COLORS(m_r, m_g, m_b);

		return *this;
	}

	Color operator+=(const Color& other)
	{
		m_r += other.m_r;
		m_g += other.m_g;
		m_b += other.m_b;

		CLAMP_COLORS(m_r, m_g, m_b);

		return *this;
	}

	Color operator-=(const Color& other)
	{
		m_r -= other.m_r;
		m_g -= other.m_g;
		m_b -= other.m_b;

		CLAMP_COLORS(m_r, m_g, m_b);

		return *this;
	}

	float r() const { return m_r; }
	float g() const { return m_g; }
	float b() const { return m_b; }

	void getAsUnsignedChar(unsigned char& r, unsigned char& g, unsigned char& b) const;

private:
	float m_r = 0;
	float m_g = 0;
	float m_b = 0;
};

inline Color operator*(const Color& c, const float u)
{
	auto r = c.r() * u;
	auto g = c.g() * u;
	auto b = c.b() * u;

	CLAMP_COLORS(r, g, b);

	return Color(r, g, b);
}

inline Color operator*(const float u, const Color& c)
{
	return c * u;
}

inline Color operator+(const Color& c1, const Color& c2)
{
	auto r = c1.r() + c2.r();
	auto g = c1.g() + c2.g();
	auto b = c1.b() + c2.b();


	CLAMP_COLORS(r, g, b);

	return Color(r,g,b);
}