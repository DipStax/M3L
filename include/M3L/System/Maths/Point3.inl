#include "M3L/System/Maths/Point3.hpp"

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

    template<NumericType T>
    template<NumericType _T>
    Point3<_T> Point3<T>::as(const Point3<T>& _pt)
    {
        return Point3<_T>{ static_cast<_T>(_pt.x), static_cast<_T>(_pt.y), static_cast<_T>(_pt.z) };
    }

    template<NumericType T>
    template<NumericType _T>
    Point3<_T> Point3<T>::as() const
    {
        return Point3<T>::as<_T>(*this);
    }

    template<NumericType T>
    template<NumericType _T>
    Point2<_T> Point3<T>::as2() const
    {
        if constexpr (std::is_same_v<_T, T>)
            return { x, y };
        else
            return { static_cast<_T>(x), static_cast<_T>(y) };
    }

    template<NumericType _T>
    std::ostream &operator<<(std::ostream &_os, const Point3<_T> &_pt)
    {
        _os << "{ " << _pt.x << ", " << _pt.y << ", " << _pt.z << " }";
        return _os;
    }
}