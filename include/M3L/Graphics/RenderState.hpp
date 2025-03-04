#pragma once

#include "M3L/Graphics/2D/Transform.hpp"
#include "M3L/Graphics/3D/Transform.hpp"
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