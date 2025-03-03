#pragma once

#include <vector>

#include "M3L/Graphics/Vertex.hpp"
#include "M3L/Graphics/IDrawable2D.hpp"

namespace m3l
{
    class M3L_API VertexArray : public IDrawable2D
    {
        public:
            enum class Type
            {
                Point,
                Lines,
                LineStrip,
                Triangle,
                TriangleStrip
            };

            VertexArray(size_t _n = 0);
            VertexArray(Type _type, size_t _n = 0);
            ~VertexArray() = default;

            void setType(Type _type);
            [[nodiscard]] Type getType() const;

            void resize(size_t _n);
            void append(const Vertex2D &_px);

            [[nodiscard]] size_t size() const;

            [[nodiscard]] Vertex2D &operator[](size_t _idx);

            [[nodiscard]] Vertex2D *data();
            [[nodiscard]] const Vertex2D *data() const;

            void clear();

        protected:
            void draw(RenderTarget2D &_target, RenderState2D _state) const;

        private:
            std::vector<Vertex2D> m_pos;
            Type m_type = Type::Point;
    };
}