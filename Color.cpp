#include "Color.h"

void Color::getAsUnsignedChar(unsigned char& r, unsigned char& g, unsigned char& b) const
{
    r = static_cast<unsigned char>(m_r * 255.999f);
    g = static_cast<unsigned char>(m_g * 255.999);
    b = static_cast<unsigned char>(m_b * 255.999);
}
