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

    uint32_t applyAlpha(uint32_t _new, uint32_t _old)
    {
        uint32_t clr{};
        float old_alpha = CLR_RATIO_ALPHA(_old);
        float new_alpha = CLR_RATIO_ALPHA(_new);

        CLR_SET_ALPHA(clr, static_cast<uint8_t>((1 - (1 - old_alpha) * (1 - new_alpha)) * 255.f));
        float new_ratio = new_alpha / CLR_RATIO_ALPHA(clr);
        float old_ratio = old_alpha * (1 - new_alpha) / CLR_GET_ALPHA(clr);

        CLR_SET_RED(clr, static_cast<uint8_t>(CLR_GET_RED(_new) * new_ratio + CLR_GET_RED(_old) * old_ratio));
        CLR_SET_GREEN(clr, static_cast<uint8_t>(CLR_GET_GREEN(_new) * new_ratio + CLR_GET_GREEN(_old) * old_ratio));
        CLR_SET_BLUE(clr, static_cast<uint8_t>(CLR_GET_BLUE(_new) * new_ratio + CLR_GET_BLUE(_old) * old_ratio));
        return clr;
    }
}