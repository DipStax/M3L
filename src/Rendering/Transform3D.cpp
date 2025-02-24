#include "M3L/Rendering/Transform3D.hpp"

namespace m3l
{
    Transform3D::Transform3D()
    {
        m_matrix.identity();
    }

    Transform3D::Transform3D(const Point3<float> &_pos, const Point3<float> &_rot, const Point3<float> &_scale)
    {
        m_matrix = buildPosition(_pos) * buildRotation(_rot) * buildScale(_scale);
    }

    Matrix<4, 4> Transform3D::buildPosition(const Point3<float> &_pos) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        matrix[0][3] = _pos.x;
        matrix[1][3] = _pos.y;
        matrix[2][3] = _pos.z;
        return matrix;
    }

    Matrix<4, 4> Transform3D::buildScale(const Point3<float> &_scale) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        matrix[0][0] = _scale.x;
        matrix[1][1] = _scale.y;
        matrix[2][2] = _scale.z;
        return matrix;
    }

    Matrix<4, 4> Transform3D::buildRotation(const Point3<float> &_rot) const
    {
        return buildXRotation(_rot.x) * buildYRotation(_rot.y) * buildZRotation(_rot.z);
    }

    Matrix<4, 4> Transform3D::buildXRotation(float _rot) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        matrix[1][1] = std::cos(_rot);
        matrix[1][2] = -std::sin(_rot);
        matrix[2][1] = std::sin(_rot);
        matrix[2][2] = std::cos(_rot);
        return matrix;
    }

    Matrix<4, 4> Transform3D::buildYRotation(float _rot) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        matrix[0][0] = std::cos(_rot);
        matrix[0][2] = std::sin(_rot);
        matrix[3][0] = -std::sin(_rot);
        matrix[3][2] = std::cos(_rot);
        return matrix;
    }

    Matrix<4, 4> Transform3D::buildZRotation(float _rot) const
    {
        Matrix<4, 4> matrix{};

        matrix.identity();
        matrix[0][0] = std::cos(_rot);
        matrix[0][1] = -std::sin(_rot);
        matrix[1][0] = std::sin(_rot);
        matrix[1][1] = std::cos(_rot);
        return matrix;
    }
}