#pragma once

#include "M3L/System/Maths/Point2.hpp"

namespace m3l
{
    template<NumericType T>
    struct Point3
    {
        T x = 0;
        T y = 0;
        T z = 0;

        // operator arithmetic
        Point3<T> operator+(const Point3<T> &_pos) const;
        Point3<T> operator-(const Point3<T> &_pos) const;
        Point3<T> operator*(const Point3<T> &_pos) const;
        Point3<T> operator/(const Point3<T> &_pos) const;

        Point3<T> operator+(const T &_val) const;
        Point3<T> operator-(const T &_val) const;
        Point3<T> operator*(const T &_val) const;
        Point3<T> operator/(const T &_val) const;

        // operator assignement
        Point3<T> &operator+=(const Point3<T> &_pos);
        Point3<T> &operator-=(const Point3<T> &_pos);
        Point3<T> &operator*=(const Point3<T> &_pos);
        Point3<T> &operator/=(const Point3<T> &_pos);

        Point3<T> &operator+=(const T &_val);
        Point3<T> &operator-=(const T &_val);
        Point3<T> &operator*=(const T &_val);
        Point3<T> &operator/=(const T &_val);

        bool operator==(const Point3<T> &_pos);
        bool operator!=(const Point3<T> &_pos);

        template<NumericType _T>
        static Point3<_T> as(const Point3<T> &_pt);
        template<NumericType _T>
        Point3<_T> as() const;

        template<NumericType _T = T>
        Point2<_T> as2() const;

        template<NumericType _T>
        friend std::ostream &operator<<(std::ostream &_os, const Point3<_T> &_pt);
    };

    template<NumericType T>
    using Vector3 = Point3<T>;
}

#include "M3L/System/Maths/Point3.inl"