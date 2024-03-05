#pragma once

#include <vector>
#include <Windows.h>

#include "M3L/Rendering/IDrawable3D.hpp"
#include "M3L/Rendering/VertexArray.hpp"
#include "M3L/Rendering/Camera.hpp"

namespace m3l
{
    class M3L_API RenderTarget
    {
        public:
            void setCamera(const Camera &_cam);

            void setBpp(uint8_t _bpp);
            [[nodiscard]] uint8_t getBpp() const;

            // 32 rendering
            void draw(const IDrawable &_elem, const Texture *_txtr = nullptr);
            void draw(const Vertex *_vtx, size_t _size, const Texture *_txtr);
            void draw(const Vertex *_vtx, size_t _size, VertexArray::Type _type);

            // 3d rendering
            void draw(const IDrawable3D &_elem, const Texture *_txtr = nullptr);
            void draw(const Vertex3D *_vtx, size_t _size, const Texture *_txtr);
            void draw(const Vertex3D *_vtx, size_t _size, VertexArray::Type _type);

            [[nodiscard]] virtual Point2<uint32_t> getSize() const = 0;
            [[nodiscard]] Camera &getCamera();

            void clear(const Color &_clr = { 0, 0, 0, 255 });

        protected:
            RenderTarget() = default;

            void create(uint32_t _x, uint32_t _y, const Camera& _cam, uint8_t _bpp = 32);
            void create(uint32_t _x, uint32_t _y, uint8_t _bpp = 32);

            [[nodiscard]] uint8_t *getData() const;

        private:
            void setPixel(const Point2<uint32_t> &_pos, Color _clr, float _depth = 0.f);
            void drawLine(const Point2<uint32_t> &_first, const Point2<uint32_t> &_sec);
            void triRangeApply(const Vertex *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture *_txtr);
            void triRangeApply(const Vertex* _vtx, int32_t _line, const Point2<uint32_t>& _range);
            void triRangeApply(const Vertex3D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture * _txtr);

            Camera m_cam;
            HBITMAP m_dib;
            std::vector<float> m_depth;
            uint8_t *m_data = nullptr;
            uint8_t m_bpp;
    };
}