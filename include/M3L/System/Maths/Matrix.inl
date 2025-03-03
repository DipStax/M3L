#include "M3L/System/Maths/Matrix.hpp"

namespace m3l
{
    template<size_t Y, size_t X, class T>
    Matrix<Y, X, T>::Matrix()
    {
        clear();
    }

    template<size_t Y, size_t X, class T>
    void Matrix<Y, X, T>::identity()
    {
        clear();
        for (size_t it = 0; it < std::min(Y, X); it++)
            (*this)[it][it] = 1;
    }

    template<size_t Y, size_t X, class T>
    void Matrix<Y, X, T>::clear()
    {
        for (auto& _y : (*this))
            _y.fill(0);
    }

    template<size_t Y, size_t X, class T>
    template<size_t Z>
    Matrix<Y, Z, T> Matrix<Y, X, T>::operator*(const Matrix<X, Z, T> &_matrix) const
    {
        Matrix<Y, Z, T> mat;

        for (size_t y = 0; y < Y; y++)
            for (size_t x = 0; x < Z; x++)
                for (size_t it = 0; it < X; it++)
                    mat[y][x] += (*this)[y][it] * _matrix[it][x];
        return mat;
    }

    template<size_t Y, size_t X, class T>
    Matrix<Y, X, T> Matrix<Y, X, T>::operator*=(const Matrix<Y, X, T>& _matrix)
    {
        *this = *this * _matrix;
        return *this;
    }

    template<size_t _Y, size_t _X, class _T>
    std::ostream& operator<<(std::ostream& _os, const Matrix<_Y, _X, _T>& _mat) {
        _os << "[ ";
        for (size_t y = 0; y < _Y; y++) {
            _os << "[ ";
            for (size_t x = 0; x < _X; x++) {
                _os << _mat[y][x];
                if (x != _X - 1)
                    _os << ",";
                _os << " ";
            }
            _os << "]";
            if (y != _Y - 1)
                _os << std::endl;
        }
        return _os;
    }
}