#pragma once

#include "M3L/Rendering/Transformable2D.hpp"
#include "M3L/Rendering/Texture.hpp"

namespace m3l
{
    struct BaseRenderState
    {
        Texture *texture;
    };

    struct RenderState2D : BaseRenderState
    {
        Transform2D transfo{};
    };

    struct RenderState3D : BaseRenderState
    {
        bool vertexOnly = false;
        // Transformable3D transfo;
    };
}