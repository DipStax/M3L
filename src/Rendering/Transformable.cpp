#include "M3L/Rendering/Transformable.hpp"

namespace m3l
{
    void Transformable::setPosition(float _x, float _y)
    {
        m_pos.y = _x;
        m_pos.y = _y;
    }

    void Transformable::setPosition(const Point2<float> &_pos)
    {
        m_pos = _pos;
    }

    void Transformable::move(float _x, float _y)
    {
        m_pos.x += _x;
        m_pos.y += _y;
    }

    void Transformable::move(const Point2<float> &_move)
    {
        m_pos += _move;
    }

    const Point2<float> &Transformable::getPosition() const
    {
        return m_pos;
    }

    Point2<float> &Transformable::getPosition()
    {
        return m_pos;
    }

    void Transformable::setScale(float _rh, float _rw)
    {
        m_scale.x = _rh;
        m_scale.y = _rw;
    }

    void Transformable::setScale(const Point2<float> &_scale)
    {
        m_scale = _scale;
    }

    Point2<float> &Transformable::getScale()
    {
        return m_scale;
    }

    const Point2<float> &Transformable::getScale() const
    {
        return m_scale;
    }


    void Transformable::setRotatio(float _rot)
    {
        m_rotation = _rot;
    }

    void Transformable::rotate(float _rot)
    {
        m_rotation += _rot;
    }

    float Transformable::getRotation() const
    {
        return m_rotation;
    }
}