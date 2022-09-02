#pragma once

class Color
{
public:
	Color()
		: m_r(0), m_g(0), m_b(0) 
	{}

	Color(float r, float g, float b)
		: m_r(r), m_g(g), m_b(b) 
	{}

	Color operator*=(const float u);

	Color operator+=(const Color& other);

	Color operator-=(const Color& other);

	inline float r() const { return m_r; }
	inline float g() const { return m_g; }
	inline float b() const { return m_b; }

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
