#pragma once

#include "M3L/Rendering/VertexArray.hpp"
#include "M3L/Rendering/Rect.hpp"
#include "M3L/Rendering/IDrawable.hpp"
#include "M3L/Rendering/Texture.hpp"

namespace m3l
{
    class M3L_API Sprite : public IDrawable
    {
        public:
            Sprite();
            ~Sprite() = default;

            void setTexture(Texture &_img);

            void setPosition(float _x, float _y);
            void setPosition(const Point2<float> &_pos);
            [[nodiscard]] Point2<float> getPosition() const;

            void setScale(const Point2<float> &_scale);
            void setScale(float _rh, float _rw);
            [[nodiscard]] Point2<float> getScale() const;

            void setTxtrRect(Rect _rect);
            [[nodiscard]] Rect getTxtrRect() const;

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const override;

        private:
            void buildVertex();
            void processRect();

            Texture m_txtr{};

            VertexArray m_vertex{};

            Rect m_rect;
            Point2<float> m_pos = { 0.f, 0.f };
            Point2<float> m_scale = { 1, 1 };
    };
}