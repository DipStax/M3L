#include "M3L/Graphics/Color.hpp"

namespace m3l
{
    Color Color::operator*(float &_ratio) const
    {
        Color clr = *this;

        clr.R *= _ratio;
        clr.G *= _ratio;
        clr.B *= _ratio;
        clr.A *= _ratio;
        return clr;
    }

    std::ostream &operator<<(std::ostream &_os, const Color &_clr)
    {
        _os << "{ " << static_cast<uint16_t>(_clr.R) << ", " << static_cast<uint16_t>(_clr.G)
            << ", " << static_cast<uint16_t>(_clr.B) << ", " << static_cast<uint16_t>(_clr.A) << " }";
        return _os;
    }
}