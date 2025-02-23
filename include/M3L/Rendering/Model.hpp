#pragma once

#include "M3L/Rendering/Object3D.hpp"
#include "M3L/Rendering/Target/RenderTarget3D.hpp"
#include "M3L/Rendering/Transformable3D.hpp"

namespace m3l
{
    class M3L_API Model : public Transformable3D, public IDrawable3D
    {
        public:
            Model() = default;
            Model(Object3D &_obj, Texture &_txtr);

            void setObject(Object3D &_obj);
            void setTexture(Texture &_txtr);

            void displayEdge(bool _enable, bool _withtxtr = false);

        protected:
            void draw(RenderTarget3D &_target, RenderState3D _state) const;

        private:
            bool m_edge = false;
            bool m_withtxtr = false;

            Object3D *m_obj = nullptr;
            Texture *m_txtr = nullptr;
    };
}