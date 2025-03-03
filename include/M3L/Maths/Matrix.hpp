#pragma once

#include <array>
#include <ostream>

namespace m3l
{
    template<size_t Y, size_t X, class T = float>
    class Matrix : public std::array<std::array<T, X>, Y>
    {
        public:
            Matrix();
            ~Matrix() = default;

            void identity();

            void clear();

            template<size_t Z>
            Matrix<Y, Z, T> operator*(const Matrix<X, Z, T>& _matrix) const;

            Matrix<Y, X, T> operator*=(const Matrix<Y, X, T> &_matrix);

            template<size_t _Y, size_t _X, class _T>
            friend std::ostream &operator<<(std::ostream &_os, const Matrix<_Y, _X, _T> &_mat);
    };
}


#include "M3L/Maths/Matrix.inl"