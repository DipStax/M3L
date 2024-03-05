#pragma once

#include "M3L/Rendering/Texture.hpp"

namespace m3l
{
    class RenderTarget;

    class IDrawable3D
    {
        protected:
            friend class RenderTarget;

            virtual void draw(RenderTarget &_target, const Texture *_txtr) const = 0;
    };
}