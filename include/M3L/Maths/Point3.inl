#include "M3L/Maths/Point3.hpp"

namespace m3l
{
    template<NumericType T>
    Point3<T> Point3<T>::operator+(const Point3<T> &_pos) const
    {
        return { x + _pos.x, y + _pos.y, z + _pos.z };
    }

    template<NumericType T>
    Point3<T> Point3<T>::operator-(const Point3<T> &_pos) const
    {
        return { x - _pos.x, y - _pos.y, z - _pos.z };
    }

    template<NumericType T>
    Point3<T> Point3<T>::operator*(const Point3<T> &_pos) const
    {
        return { x * _pos.x, y * _pos.y, z * _pos.z };
    }

    template<NumericType T>
    Point3<T> Point3<T>::operator/(const Point3<T> &_pos) const
    {
        return { x / _pos.x, y / _pos.y, z / _pos.z };
    }

    template<NumericType T>
    Point3<T> Point3<T>::operator+(const T &_val) const
    {
        return { x + _val, y + _val, z + _val };
    }

    template<NumericType T>
    Point3<T> Point3<T>::operator-(const T & _val) const
    {
        return { x - _val, y - _val, z - _val };
    }

    template<NumericType T>
    Point3<T> Point3<T>::operator*(const T & _val) const
    {
        return { x * _val, y * _val, z * _val };
    }

    template<NumericType T>
    Point3<T> Point3<T>::operator/(const T & _val) const
    {
        return { x / _val, y / _val, z / _val };
    }

    template<NumericType T>
    Point3<T> &Point3<T>::operator+=(const Point3<T> &_pos)
    {
        x += _pos.x;
        y += _pos.y;
        z += _pos.z;
        return *this;
    }

    template<NumericType T>
    Point3<T> &Point3<T>::operator-=(const Point3<T> &_pos)
    {
        x -= _pos.x;
        y -= _pos.y;
        z -= _pos.z;
        return *this;
    }

    template<NumericType T>
    Point3<T> &Point3<T>::operator*=(const Point3<T> &_pos)
    {
        x *= _pos.x;
        y *= _pos.y;
        z *= _pos.z;
        return *this;
    }

    template<NumericType T>
    Point3<T> &Point3<T>::operator/=(const Point3<T> &_pos)
    {
        x /= _pos.x;
        y /= _pos.y;
        z /= _pos.z;
        return *this;
    }

    template<NumericType T>
    Point3<T> &Point3<T>::operator+=(const T &_val)
    {
        x += _val;
        y += _val;
        z += _val;
        return *this;
    }

    template<NumericType T>
    Point3<T> &Point3<T>::operator-=(const T &_val)
    {
        x -= _val;
        y -= _val;
        z -= _val;
        return *this;
    }

    template<NumericType T>
    Point3<T> &Point3<T>::operator*=(const T &_val)
    {
        x *= _val;
        y *= _val;
        z *= _val;
        return *this;
    }

    template<NumericType T>
    Point3<T> &Point3<T>::operator/=(const T &_val)
    {
        x /= _val;
        y /= _val;
        z /= _val;
        return *this;
    }

    template<NumericType T>
    bool Point3<T>::operator==(const Point3<T> &_pos)
    {
        return x == _pos.x && y == _pos.y && z == _pos.z;
    }

    template<NumericType T>
    bool Point3<T>::operator!=(const Point3<T> &_pos)
    {
        return x != _pos.x && y != _pos.y && z != _pos.z;
    }

    template<NumericType _T>
    std::ostream &operator<<(std::ostream &_os, const Point3<_T> &_pt)
    {
        _os << "{ " << _pt.x << ", " << _pt.y << ", " << _pt.z << " }";
        return _os;
    }

    template<NumericType T>
    Point2<T> Point3<T>::as2() const
    {
        return { x, y };
    }
}