#pragma once

#include "M3L/Rendering/RenderTarget.hpp"

namespace m3l
{
    class M3L_API RenderTexture : public RenderTarget
    {
        public:
            RenderTexture() = default;
            ~RenderTexture() = default;

            void create(uint32_t _x, uint32_t _y);

            [[nodiscard]] Texture getTexture() const;
            [[nodiscard]] Point2<uint32_t> getSize() const;

        private:
            Point2<uint32_t> m_size;
    };
}