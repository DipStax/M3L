#include "M3L/Graphics/2D/Rectangle.hpp"

namespace m3l
{
    Rectangle2D::Rectangle2D(float _x, float _y)
        : m_size({ _x, _y })
    {
        buildVertex();
    }

    Rectangle2D::Rectangle2D(const Vector2<float> &_size)
        : m_size(_size)
    {
        buildVertex();
    }

    void Rectangle2D::setSize(float _x, float _y)
    {
        setSize({ _x, _y });
    }

    void Rectangle2D::setSize(const Vector2<float> &_size)
    {
        m_size = _size;
        buildVertex();
    }

    void Rectangle2D::setColor(const Color &_clr)
    {
        m_clr = _clr;
    }

    Color Rectangle2D::getColor() const
    {
        return m_clr;
    }

    void Rectangle2D::draw(RenderTarget2D &_target, RenderState2D _state) const
    {
        _state.transform *= getTransform();

        _target.draw(m_vertex.data(), m_vertex.size(), VertexArray::Type::TriangleStrip, _state);
    }

    void Rectangle2D::buildVertex()
    {
        m_vertex.clear();
        m_vertex.append({ { 0, 0 }, { 0, 0 }, m_clr });
        m_vertex.append({ { m_size.x, 0 }, { 0, 0 }, m_clr });
        m_vertex.append({ { 0, m_size.y }, { 0, 0 }, m_clr });
        m_vertex.append({ m_size, { 0, 0 }, m_clr });
    }
}