#pragma once

#include "M3L/System/Maths/Point3.hpp"
#include "M3L/System/Maths/Matrix.hpp"
#include "Tool/Export.hpp"

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

            friend std::ostream& operator<<(std::ostream& _os, const Transform3D& _transfo) {
                _os << _transfo.m_matrix;
                return _os;
            }

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