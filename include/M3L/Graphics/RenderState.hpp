#pragma once

#include "M3L/Graphics/Transformable2D.hpp"
#include "M3L/Graphics/Transformable3D.hpp"
#include "M3L/Graphics/Texture.hpp"

namespace m3l
{
    struct BaseRenderState
    {
        Texture *texture;
    };

    struct RenderState2D : BaseRenderState
    {
        Transform2D transform{};
    };

    struct RenderState3D : BaseRenderState
    {
        bool vertexOnly = false;
        Transform3D transform;
    };
}