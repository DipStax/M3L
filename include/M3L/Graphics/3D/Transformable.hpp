#pragma once

#include "M3L/Graphics/Transform3D.hpp"

namespace m3l
{
    class M3L_API Transformable3D
    {
        public:
            Transformable3D() = default;
            virtual ~Transformable3D() = default;

            void setPosition(float _x, float _y, float _z);
            void setPosition(const Point3<float> &_pos);
            void move(float _x, float _y, float _z);
            void move(const Point3<float> &_move);
            [[nodiscard]] const Point3<float> &getPosition() const;
            [[nodiscard]] Point3<float> getPosition();

            void setScale(float _rh, float _rw, float _rd);
            void setScale(const Point3<float> &_scale);
            void scale(float _rh, float _rw, float _rd);
            void scale(const Point3<float> &_scale);
            [[nodiscard]] const Point3<float> &getScale() const;
            [[nodiscard]] Point3<float> getScale();

            void setRotation(float _rx, float _ry, float _rz);
            void setRotation(const Point3<float> &_rotation);
            void rotate(float _rx, float _ry, float _rz);
            void rotate(const Point3<float> &_rotation);
            [[nodiscard]] const Point3<float> &getRotation() const;
            [[nodiscard]] Point3<float> getRotation();

            [[nodiscard]] Transform3D getTransform() const;

        private:
            mutable bool m_update = false;
            mutable Transform3D m_transform;

            Point3<float> m_pos{ 0, 0, 0 };
            Point3<float> m_scale{ 1, 1, 1 };
            Point3<float> m_rotation{ 0, 0, 0 };
    };
}