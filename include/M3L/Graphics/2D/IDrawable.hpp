#pragma once

#include "M3L/Graphics/RenderState.hpp"

namespace m3l
{
    class RenderTarget2D;

    class IDrawable2D
    {
        protected:
            friend class RenderTarget2D;

            virtual void draw(RenderTarget2D &_target, RenderState2D _state = RenderState2D()) const = 0;
    };
}