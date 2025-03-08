#pragma once

#include "M3L/Graphics/Rect.hpp"
#include "M3L/Graphics/2D/Transformable.hpp"
#include "M3L/Graphics/VertexArray.hpp"
#include "M3L/Graphics/Color.hpp"
#include "M3L/Graphics/2D/Target/RenderTarget.hpp"

namespace m3l
{
    class M3L_API Rectangle2D : public Transformable2D, public IDrawable2D
    {
        public:
            Rectangle2D(float _x, float _y);
            Rectangle2D(const Vector2<float> &_size);
            ~Rectangle2D() = default;

            void setSize(float _x, float _y);
            void setSize(const Vector2<float> &_size);
            [[nodiscard]] Vector2<float> getSize() const;

            void setColor(const Color &_clr);
            [[nodiscard]] Color getColor() const;

        protected:
            void draw(RenderTarget2D &_target, RenderState2D _state) const;

        private:
            void buildVertex();

            Color m_clr{ 0, 0, 0, 255 };
            Point2<float> m_size;
            VertexArray m_vertex{};
    };
}