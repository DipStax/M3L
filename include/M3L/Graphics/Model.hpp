#pragma once

#include "M3L/Graphics/3D/Object.hpp"
#include "M3L/Graphics/3D/Target/RenderTarget.hpp"
#include "M3L/Graphics/3D/Transformable.hpp"

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