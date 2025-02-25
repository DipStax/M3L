#pragma once

#include "M3L/Maths/Point3.hpp"
#include "M3L/Maths/Matrix.hpp"

namespace m3l
{
    class M3L_API Transform3D
    {
        public:
            Transform3D();
            Transform3D(const Matrix<4, 4> &_matrix);
            Transform3D(const Point3<float> &_pos, const Point3<float> &_rot, const Point3<float> &_scale);

            Transform3D operator*(const Transform3D &_rt) const;
            Transform3D &operator*=(const Transform3D &_rt);
            Point3<float> operator*(const Point3<float> &_pt) const;

        private:
            Matrix<4, 4> buildPosition(const Point3<float> &_pos) const;

            Matrix<4, 4> buildScale(const Point3<float> &_scale) const;

            Matrix<4, 4> buildRotation(const Point3<float> &_rot) const;
            Matrix<4, 4> buildXRotation(float _rot) const;
            Matrix<4, 4> buildYRotation(float _rot) const;
            Matrix<4, 4> buildZRotation(float _rot) const;

            Matrix<4, 4> m_matrix;
    };
}