#pragma once

#include "M3L/Rendering/VertexArray.hpp"
#include "M3L/Rendering/Rect.hpp"
#include "M3L/Rendering/IDrawable.hpp"
#include "M3L/Rendering/Texture.hpp"
#include "M3L/Rendering/Transformable.hpp"

namespace m3l
{
    class M3L_API Sprite : public Transformable, public IDrawable
    {
        public:
            Sprite();
            ~Sprite() = default;

            void setTexture(Texture &_img);

            void setTxtrRect(Rect _rect);
            [[nodiscard]] Rect getTxtrRect() const;

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const override;

        private:
            void buildVertex();
            void processRect();

            Texture *m_txtr = nullptr;

            VertexArray m_vertex{};

            Rect m_rect;
    };
}