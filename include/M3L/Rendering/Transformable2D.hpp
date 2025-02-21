#pragma once

#include "M3L/Maths/Point2.hpp"
#include "M3L/Maths/Matrix.hpp"

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

    class M3L_API Transformable2D
    {
        public:
            Transformable2D() = default;
            virtual ~Transformable2D() = default;

            void setPosition(float _x, float _y);
            void setPosition(const Point2<float> &_pos);
            void move(float _x, float _y);
            void move(const Point2<float> &_move);
            [[nodiscard]] const Point2<float> &getPosition() const;
            [[nodiscard]] Point2<float> getPosition();

            void setOrigin(float _x, float _y);
            void setOrigin(const Point2<float> &_orig);
            [[nodiscard]] const Point2<float> &getOrigin() const;
            [[nodiscard]] Point2<float> getOrigin();

            void setScale(float _rh, float _rw);
            void setScale(const Point2<float> &_scale);
            [[nodiscard]] const Point2<float> &getScale() const;
            [[nodiscard]] Point2<float> getScale();

            void setRotatio(float _rot);
            void rotate(float _rot);
            [[nodiscard]] float getRotation() const;

            [[nodiscard]] Transform2D getTransform() const;

        protected:
            [[nodiscard]] Point2<float> projetPoint(const Point2<float> &_pt);

        private:
            mutable bool m_update = false;
            mutable Transform2D m_transform;

            Point2<float> m_pos{ 0, 0 };
            Point2<float> m_scale{ 1, 1 };
            Point2<float> m_origin{ 0, 0 };
            float m_rotation = 0.f;
    };
}