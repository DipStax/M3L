#include "M3L/Graphics/Transformable3D.hpp"

namespace m3l
{
    void Transformable3D::setPosition(float _x, float _y, float _z)
    {
        setPosition({ _x, _y, _z});
    }

    void Transformable3D::setPosition(const Point3<float> &_pos)
    {
        m_pos = _pos;
        m_update = true;
    }

    void Transformable3D::move(float _x, float _y, float _z)
    {
        move({ _x, _y, _z});
    }

    void Transformable3D::move(const Point3<float> &_pos)
    {
        m_pos += _pos;
        m_update = true;
    }

    const Point3<float> &Transformable3D::getPosition() const
    {
        return m_pos;
    }

    Point3<float> Transformable3D::getPosition()
    {
        return m_pos;
    }

    void Transformable3D::setScale(float _x, float _y, float _z)
    {
        setScale({ _x, _y, _z});
    }

    void Transformable3D::setScale(const Point3<float> &_scale)
    {
        m_scale = _scale;
        m_update = true;
    }

    void Transformable3D::scale(float _x, float _y, float _z)
    {
        scale({ _x, _y, _z});
    }

    void Transformable3D::scale(const Point3<float> &_scale)
    {
        m_scale *= _scale;
        m_update = true;
    }

    const Point3<float> &Transformable3D::getScale() const
    {
        return m_scale;
    }

    Point3<float> Transformable3D::getScale()
    {
        return m_scale;
    }

    void Transformable3D::setRotation(float _x, float _y, float _z)
    {
        setRotation({ _x, _y, _z});
    }

    void Transformable3D::setRotation(const Point3<float> &_rotation)
    {
        m_rotation = _rotation;
        m_update = true;
    }

    void Transformable3D::rotate(float _x, float _y, float _z)
    {
        rotate({ _x, _y, _z});
    }

    void Transformable3D::rotate(const Point3<float> &_rotation)
    {
        m_rotation += _rotation;
        m_update = true;
    }

    const Point3<float> &Transformable3D::getRotation() const
    {
        return m_rotation;
    }

    Point3<float> Transformable3D::getRotation()
    {
        return m_rotation;
    }

    Transform3D Transformable3D::getTransform() const
    {
        if (m_update) {
            m_transform = Transform3D(m_pos, m_rotation, m_scale);
            m_update = false;
        }
        return m_transform;
    }
}