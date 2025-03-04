#pragma once

#include "M3L/Graphics/VertexArray.hpp"
#include "M3L/Graphics/Rect.hpp"
#include "M3L/Graphics/2D/IDrawable.hpp"
#include "M3L/Graphics/Texture.hpp"
#include "M3L/Graphics/2D/Transformable.hpp"

namespace m3l
{
    class M3L_API Sprite : public Transformable2D, public IDrawable2D
    {
        public:
            Sprite();
            ~Sprite() = default;

            void setTexture(Texture &_img);

            void setTxtrRect(Rect _rect);
            [[nodiscard]] Rect getTxtrRect() const;

        protected:
            void draw(RenderTarget2D &_target, RenderState2D _state) const override;

        private:
            void buildVertex();

            Texture *m_txtr = nullptr;

            VertexArray m_vertex{};

            Rect m_rect;
    };
}