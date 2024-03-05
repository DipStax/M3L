#pragma once

#include <vector>

#include "M3L/Rendering/Vertex.hpp"
#include "M3L/Rendering/IDrawable.hpp"

namespace m3l
{
    class M3L_API VertexArray : public IDrawable
    {
        public:
            enum class Type
            {
                Point,
                Lines,
                LineStrip,
                Polygone
            };

            VertexArray(size_t _n = 0);
            ~VertexArray() = default;

            void setType(Type _type);
            [[nodiscard]] Type getType() const;

            void resize(size_t _n);
            void append(const Vertex &_px);

            [[nodiscard]] size_t size() const;

            [[nodiscard]] Vertex &operator[](size_t _idx);

            [[nodiscard]] Vertex *data();
            [[nodiscard]] const Vertex *data() const;

            void clear();

        protected:
            void draw(RenderTarget &_target, const Texture *_txtr) const;

        private:
            std::vector<Vertex> m_pos;
            Type m_type = Type::Point;
    };
}