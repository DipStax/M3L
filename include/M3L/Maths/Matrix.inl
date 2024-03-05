#include "M3L/Maths/Matrix.hpp"

namespace m3l
{
    template<size_t Y, size_t X>
    Matrix<Y, X>::Matrix()
    {
        clear();
    }

    template<size_t Y, size_t X>
    void Matrix<Y, X>::identity()
    {
        clear();
        for (size_t it = 0; it < std::min(Y, X); it++)
            (*this)[it][it] = 1;
    }

    template<size_t Y, size_t X>
    void Matrix<Y, X>::clear()
    {
        for (auto& _y : (*this))
            _y.fill(0);
    }

    template<size_t Y, size_t X>
    template<size_t Z>
    Matrix<Y, Z> Matrix<Y, X>::operator*(const Matrix<X, Z> &_matrix)
    {
        Matrix<Y, Z> mat;

        for (size_t y = 0; y < Y; y++)
            for (size_t x = 0; x < Z; x++)
                for (size_t it = 0; it < X; it++)
                    mat[y][x] += (*this)[y][it] * _matrix[it][x];
        return mat;
    }

    template<size_t _Y, size_t _X>
    std::ostream& operator<<(std::ostream& _os, const Matrix<_Y, _X>& _mat) {
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