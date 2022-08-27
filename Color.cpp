#include "Color.h"
#include <cmath>

void Color::getAsUnsignedChar(unsigned char& r, unsigned char& g, unsigned char& b) const
{
    r = static_cast<unsigned char>(m_r * 255.999f);
    g = static_cast<unsigned char>(m_g * 255.999);
    b = static_cast<unsigned char>(m_b * 255.999);
}

void Color::applyGammaCorrection(float factor)
{
    m_r = powf(m_r, 1 / factor);
    m_g = powf(m_g, 1 / factor);
    m_b = powf(m_b, 1 / factor);
}
