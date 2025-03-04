#pragma once

#include <ostream>

#include "Tool/Export.hpp"

#define CLR(_clr)           (static_cast<uint32_t>(_clr.A) << 24) | (static_cast<uint32_t>(_clr.R) << 16) | (static_cast<uint32_t>(_clr.G) << 8) | _clr.B

#define CLR_GET_RGB(_clr)           (_clr & 0xFFFFFF)
#define CLR_GET_BLUE(_clr)          (_clr & 0xFF)
#define CLR_GET_GREEN(_clr)         ((_clr >> 8) & 0xFF)
#define CLR_GET_RED(_clr)           ((_clr >> 16) & 0xFF)
#define CLR_GET_ALPHA(_clr)         ((_clr >> 24) & 0xFF)

#define CLR_SET_BLUE(_clr, _blue)   _clr = (_blue & 0xFF)           | (_clr & 0xFFFFFF00) 
#define CLR_SET_GREEN(_clr, _green) _clr = ((_green & 0xFF) << 8)   | (_clr & 0xFFFF00FF) 
#define CLR_SET_RED(_clr, _red)     _clr = ((_red & 0xFF) << 16)    | (_clr & 0xFF00FFFF) 
#define CLR_SET_ALPHA(_clr, _alpha) _clr = ((_alpha & 0xFF) << 24)  | (_clr & 0x00FFFFFF) 

#define CLR_RATIO_ALPHA(_clr)       (static_cast<float>(CLR_GET_ALPHA(_clr)) / 255.f)

namespace m3l
{
    struct M3L_API Color
    {
        uint8_t R = 0;
        uint8_t G = 0;
        uint8_t B = 0;
        uint8_t A = 255;

        Color operator*(float &_ratio) const;
    };

    M3L_API std::ostream &operator<<(std::ostream &_os, const Color &_clr);

    uint32_t applyAlpha(uint32_t _new, uint32_t _old);
}