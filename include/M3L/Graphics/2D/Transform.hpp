#pragma once

#include "M3L/System/Maths/Matrix.hpp"
#include "M3L/System/Maths/Point2.hpp"

namespace m3l
{
    class M3L_API Transform2D
    {
        public:
            Transform2D();
            Transform2D(const Matrix<4, 4> &_matrix);
            Transform2D(float _xsc, float _ysc, float _xss, float _yss, float _px, float _py);
            ~Transform2D() = default;

            Transform2D operator*(const Transform2D &_rt) const;
            Transform2D &operator*=(const Transform2D &_rt);
            Point2<float> operator*(const Point2<float> &_pt) const;

        private:
            Matrix<4, 4> m_matrix;
    };
}