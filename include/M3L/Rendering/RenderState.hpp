#pragma once

#include "M3L/Rendering/Transformable2D.hpp"
#include "M3L/Rendering/Transformable3D.hpp"
#include "M3L/Rendering/Texture.hpp"

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