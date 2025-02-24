#pragma once

#include "M3L/Maths/Point3.hpp"
#include "M3L/Maths/Matrix.hpp"

namespace m3l
{
    class Transform3D
    {
        public:
            Transform3D();
            Transform3D(const Point3<float> &_pos, const Point3<float> &_rot, const Point3<float> &_scale);

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