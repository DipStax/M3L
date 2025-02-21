#include <cmath>

#include "M3L/Rendering/Transformable2D.hpp"

namespace m3l
{
    Transform2D::Transform2D()
    {
        m_matrix.identity();
    }

    Transform2D::Transform2D(const Matrix<4, 4> &_matrix)
        : m_matrix(_matrix)
    {
    }

    Transform2D::Transform2D(float _xsc, float _ysc, float _xss, float _yss, float _px, float _py)
    {
        m_matrix[0] = { _xsc, _xss, 0, 0 };
        m_matrix[1] = { _yss, _ysc, 0, 0 };
        m_matrix[2] = { 0, 0, 1, 0};
        m_matrix[3] = { _px, _py, 0, 1};
    }

    Transform2D Transform2D::operator*(const Transform2D &_rt) const
    {
        return Transform2D(m_matrix * _rt.m_matrix);
    }

    Transform2D &Transform2D::operator*=(const Transform2D &_rt)
    {
        m_matrix *= _rt.m_matrix;
        return *this;
    }

    Point2<float> Transform2D::operator*(const Point2<float> &_pt) const
    {
        return {
            m_matrix[0][0] * _pt.x + m_matrix[1][0] * _pt.y + m_matrix[3][0],
            m_matrix[0][1] * _pt.x + m_matrix[1][1] * _pt.y + m_matrix[3][1]
        };
    }

    void Transformable2D::setPosition(float _x, float _y)
    {
        setPosition({ _x, _y });
    }

    void Transformable2D::setPosition(const Point2<float> &_pos)
    {
        m_pos = _pos;
        m_update = true;
    }

    void Transformable2D::move(float _x, float _y)
    {
        move({ _x, _y });
    }

    void Transformable2D::move(const Point2<float> &_move)
    {
        m_pos += _move;
        m_update = true;
    }

    const Point2<float> &Transformable2D::getPosition() const
    {
        return m_pos;
    }

    Point2<float> Transformable2D::getPosition()
    {
        return m_pos;
    }

    void Transformable2D::setOrigin(float _x, float _y)
    {
        setOrigin({ _x, _y });
    }

    void Transformable2D::setOrigin(const Point2<float> &_orig)
    {
        m_origin = _orig;
        m_update = true;
    }

    const Point2<float> &Transformable2D::getOrigin() const
    {
        return m_origin;
    }

    Point2<float> Transformable2D::getOrigin()
    {
        return m_origin;
    }

    void Transformable2D::setScale(float _rh, float _rw)
    {
        setScale({ _rh, _rw });
    }

    void Transformable2D::setScale(const Point2<float> &_scale)
    {
        m_scale = _scale;
        m_update = true;
    }

    Point2<float> Transformable2D::getScale()
    {
        return m_scale;
    }

    const Point2<float> &Transformable2D::getScale() const
    {
        return m_scale;
    }


    void Transformable2D::setRotatio(float _rot)
    {
        m_rotation = _rot;
        m_update = true;
    }

    void Transformable2D::rotate(float _rot)
    {
        m_rotation += _rot;
        m_update = true;
    }

    float Transformable2D::getRotation() const
    {
        return m_rotation;
    }

    Transform2D Transformable2D::getTransform() const
    {
        if (m_update) {
            float angle = -(m_rotation * M_PI) / 180;
            float cosine = std::cos(angle);
            float sine = std::sin(angle);
            float sxc = m_scale.x * cosine;
            float syc = m_scale.y * cosine;
            float sxs = m_scale.x * sine;
            float sys = m_scale.y * sine;
            float tx = -m_origin.x * sxc - m_origin.y * sys + m_pos.x;
            float ty = m_origin.x * sxs - m_origin.y * syc + m_pos.y;

            m_transform = Transform2D(sxc, syc, -sxs, sys, tx, ty);

            m_update = false;
        }
        return m_transform;
    }
}