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
	Color() {}

	Color(float r, float g, float b)
		: m_r(r), m_g(g), m_b(b) 
	{}

	Color operator*=(const float u);

	Color operator+=(const Color& other);

	Color operator-=(const Color& other);

	float r() const { return m_r; }
	float g() const { return m_g; }
	float b() const { return m_b; }

	void getAsUnsignedChar(unsigned char& r, unsigned char& g, unsigned char& b) const;

	void applyGammaCorrection(float factor);

private:
	float m_r = 0;
	float m_g = 0;
	float m_b = 0;
};

Color operator*(const Color& c, const float u);

Color operator*(const float u, const Color& c);

Color operator+(const Color& c1, const Color& c2);

Color operator*(const Color& c1, const Color& c2);
