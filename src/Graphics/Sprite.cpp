#include "M3L/Graphics/Sprite.hpp"
#include "M3L/Graphics/2D/Target/RenderTarget.hpp"

namespace m3l
{
    Sprite::Sprite()
    {
        buildVertex();
    }

    void Sprite::setTexture(Texture &_img)
    {
        m_txtr = &_img;
        m_rect = { { 0, 0 }, (m_txtr) ? m_txtr->getSize().as<float>() : Point2<float>(0.f , 0.f) };
        buildVertex();
    }

    void Sprite::setTxtrRect(Rect _rect)
    {
        m_rect = _rect;
        buildVertex();
    }

    Rect Sprite::getTxtrRect() const
    {
        return m_rect;
    }

    void Sprite::draw(RenderTarget2D &_target, RenderState2D _state) const
    {
        _state.texture = m_txtr;
        _state.transform *= getTransform();

        _target.draw(m_vertex.data(), m_vertex.size(), VertexArray::Type::TriangleStrip, _state);
    }

    void Sprite::buildVertex()
    {
        m_vertex.clear();
        m_vertex.append({ { 0, 0 }, m_rect.pos });
        m_vertex.append({ { m_rect.size.x, 0 }, { m_rect.pos.x + m_rect.size.x, m_rect.pos.y } });
        m_vertex.append({ { 0, m_rect.size.y }, { m_rect.pos.x, m_rect.pos.y + m_rect.size.y } });
        m_vertex.append({ m_rect.size, m_rect.pos + m_rect.size });
    }
}