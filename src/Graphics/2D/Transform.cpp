#include "M3L/Graphics/2D/Transform.hpp"

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

}