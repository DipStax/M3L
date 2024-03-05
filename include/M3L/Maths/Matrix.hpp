#pragma once

#include <array>
#include <ostream>

namespace m3l
{
    template<size_t Y, size_t X>
    class Matrix : public std::array<std::array<float, X>, Y>
    {
        public:
            Matrix();
            ~Matrix() = default;

            void identity();

            void clear();

            template<size_t Z>
            Matrix<Y, Z> operator*(const Matrix<X, Z> &_matrix);

            template<size_t _Y, size_t _X>
            friend std::ostream &operator<<(std::ostream &_os, const Matrix<_Y, _X> &_mat);
    };
}


#include "M3L/Maths/Matrix.inl"