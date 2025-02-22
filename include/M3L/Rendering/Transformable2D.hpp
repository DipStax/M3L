#pragma once

#include "M3L/Rendering/Transform2D.hpp"

namespace m3l
{
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