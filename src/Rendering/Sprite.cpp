#include "M3L/Rendering/Sprite.hpp"
#include "M3L/Rendering/RenderTarget.hpp"

namespace m3l
{
    Sprite::Sprite()
    {
        processRect();
    }

    void Sprite::setTexture(Texture &_img)
    {
        m_txtr = _img;

        processRect();
    }

    void Sprite::setPosition(float _x, float _y)
    {
        setPosition({ _x, _y });
    }

    void Sprite::setPosition(const Point2<float> &_pos)
    {
        m_pos = _pos;
        processRect();
    }

    Point2<float> Sprite::getPosition() const
    {
        return m_pos;
    }

    void Sprite::setScale(float _rh, float _rw)
    {
        setScale({ _rh, _rw });
    }

    void Sprite::setScale(const Point2<float> &_scale)
    {
        m_scale = _scale;
        processRect();
    }

    Point2<float> Sprite::getScale() const
    {
        return m_scale;
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

    void Sprite::draw(RenderTarget &_target, const Texture *_txtr) const
    {
        std::ignore = _txtr;

        _target.draw(m_vertex, &m_txtr);
    }

    void Sprite::processRect()
    {
        Point2<float> size = m_txtr.getSize().as<float>();

        m_rect = { m_pos, size * m_scale };
        buildVertex();
    }

    void Sprite::buildVertex()
    {
        // known bug:
        // - when inversing the pos of the addition for vertex 2 and 4
        // - when inversing m_rect.size for vertex 2 and 4
        m_vertex.clear();
        m_vertex.append({ m_rect.pos, { 0, 0 } });
        m_vertex.append({ { m_rect.pos.x + m_rect.size.x, m_rect.pos.y }, { m_rect.size.x, 0 } });
        m_vertex.append({ m_rect.pos + m_rect.size, m_rect.size });
        m_vertex.append({ { m_rect.pos.x, m_rect.pos.y + m_rect.size.y }, { 0, m_rect.size.y } });
    }
}