#include <iostream>

#include "M3L/Rendering/Transform3D.hpp"

namespace m3l
{
    Transform3D::Transform3D()
    {
        m_matrix.identity();
    }

    Transform3D::Transform3D(const Matrix<4, 4> &_matrix)
        : m_matrix(_matrix)
    {
    }

    Transform3D::Transform3D(const Point3<float> &_pos, const Point3<float> &_rot, const Point3<float> &_scale)
    {
        m_matrix = buildPosition(_pos) * buildRotation(_rot) * buildScale(_scale);
    }

    Transform3D Transform3D::operator*(const Transform3D &_rt) const
    {
        return Transform3D(m_matrix * _rt.m_matrix);
    }

    Transform3D &Transform3D::operator*=(const Transform3D &_rt)
    {
        m_matrix *= _rt.m_matrix;
        return *this;
    }

    Point3<float> Transform3D::operator*(const Point3<float> &_pt) const
    {
        Matrix<4, 1> matrix;

        matrix[0][0] = _pt.x;
        matrix[1][0] = _pt.y;
        matrix[2][0] = _pt.z;
        matrix[3][0] = 1;

        Matrix<4, 1> result = m_matrix * matrix;
        float w = result[3][0];

        return { result[0][0] / w, result[1][0] / w, result[2][0] / w };
    }

    Matrix<4, 4> Transform3D::buildPosition(const Point3<float> &_pos) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        matrix[0][3] = _pos.x;
        matrix[1][3] = _pos.y;
        matrix[2][3] = _pos.z;
        std::cout << "transfo internal pos:" << std::endl << matrix << std::endl;
        return matrix;
    }

    Matrix<4, 4> Transform3D::buildScale(const Point3<float> &_scale) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        matrix[0][0] = _scale.x;
        matrix[1][1] = _scale.y;
        matrix[2][2] = _scale.z;
        std::cout << "transfo internal scale:" << std::endl << matrix << std::endl;
        return matrix;
    }

    Matrix<4, 4> Transform3D::buildRotation(const Point3<float> &_rot) const
    {
        Point3<float> rot = _rot * M_PI / 180;

        return buildXRotation(rot.x) * buildYRotation(rot.y) * buildZRotation(rot.z);
    }

    Matrix<4, 4> Transform3D::buildXRotation(float _rot) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        if (_rot) {
            matrix[1][1] = std::cos(_rot);
            matrix[1][2] = -std::sin(_rot);
            matrix[2][1] = std::sin(_rot);
            matrix[2][2] = std::cos(_rot);
            std::cout << "transfo internal rotatio X:" << std::endl << matrix << std::endl;
        }
        return matrix;
    }

    Matrix<4, 4> Transform3D::buildYRotation(float _rot) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        if (_rot) {
            matrix[0][0] = std::cos(_rot);
            matrix[0][2] = std::sin(_rot);
            matrix[3][0] = -std::sin(_rot);
            matrix[3][2] = std::cos(_rot);
            std::cout << "transfo internal rotatio Y:" << std::endl << matrix << std::endl;
        }
        return matrix;
    }

    Matrix<4, 4> Transform3D::buildZRotation(float _rot) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        if (_rot) {
            matrix[0][0] = std::cos(_rot);
            matrix[0][1] = -std::sin(_rot);
            matrix[1][0] = std::sin(_rot);
            matrix[1][1] = std::cos(_rot);
            std::cout << "transfo internal rotatio Z:" << std::endl << matrix << std::endl;
        }
        return matrix;
    }
}