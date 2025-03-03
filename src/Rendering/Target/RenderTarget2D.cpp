#include <cstring>

#include "M3L/Rendering/Target/RenderTarget2D.hpp"
#include "M3L/Rendering/PolyTri.hpp"
#include "M3L/Maths/Maths.hpp"

namespace m3l
{
    RenderTarget2D::~RenderTarget2D()
    {
        if (m_dib)
            DeleteObject(m_dib);
    }

    uint8_t RenderTarget2D::getBpp() const
    {
        return m_bpp;
    }

    void RenderTarget2D::draw(const IDrawable2D & _elem, RenderState2D _state)
    {
        _elem.draw(*this, _state);
    }

    void RenderTarget2D::draw(const Vertex2D *_vtx, size_t _size, VertexArray::Type _type, RenderState2D _state)
    {
        std::vector<Vertex2D> cache(_vtx, _vtx + _size);

        for (Vertex2D &_vertex : cache)
            _vertex.pos = _state.transform * _vertex.pos;

        switch (_type) {
            case VertexArray::Type::Point:
                for (size_t it = 0; it < _size; it++)
                    setPixel(cache[it].pos.as<uint32_t>(), cache[it].clr);
                break;
            case VertexArray::Type::Lines:
            case VertexArray::Type::LineStrip:
                for (size_t it = 1; it < _size; it++)
                    drawLine(cache[it - 1], cache[it]);
                if (_type == VertexArray::Type::LineStrip)
                    drawLine(cache[_size - 1], cache[0]);
                break;
            case VertexArray::Type::Triangle:
            case VertexArray::Type::TriangleStrip:
                const size_t delta = (_type == VertexArray::Type::Triangle) ? 3 : 1;

                for (size_t it = 0; it + 3 <= _size; it += delta) {
                    // caluclate minimal range of the drawing on y axes
                    int32_t ystart = static_cast<int32_t>(std::max(std::min({ cache[it].pos.y, cache[it + 1].pos.y, cache[it + 2].pos.y }), 0.f));
                    int32_t yend = static_cast<int32_t>(std::min(std::max({ cache[it].pos.y, cache[it + 1].pos.y, cache[it + 2].pos.y }), static_cast<float>(getSize().y)));

                    for (; ystart < yend; ystart++)
                        drawTriangle(cache.data() + it, ystart, triRange(cache.data() + it, ystart), _state.texture);
                }
                break;
        }
    }

    void RenderTarget2D::create(uint32_t _x, uint32_t _y, uint8_t _bpp)
    {
        HDC hdc = GetDC(NULL);

        m_bpp = _bpp;
        m_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        m_bmi.bmiHeader.biWidth = static_cast<int32_t>(_x);
        m_bmi.bmiHeader.biHeight = -static_cast<int32_t>(_y);
        m_bmi.bmiHeader.biPlanes = 1;
        m_bmi.bmiHeader.biBitCount = m_bpp;
        m_bmi.bmiHeader.biCompression = BI_RGB;
        if (m_dib)
            DeleteObject(m_dib);
        m_dib = CreateDIBSection(hdc, &m_bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&m_data), NULL, 0);
        ReleaseDC(NULL, hdc);
    }

    void RenderTarget2D::clear(const Color &_clr)
    {
        uint32_t clr = CLR(_clr);
        size_t size = getSize().x * getSize().y * (m_bpp / 8);

        for (size_t it = 0; it < size; it += sizeof(uint32_t))
            std::memcpy(m_data + it, &clr, sizeof(uint32_t));
    }

    const uint8_t *RenderTarget2D::getData() const
    {
        return m_data;
    }

    void RenderTarget2D::drawLine(const Vertex2D &_start, const Vertex2D &_end)
    {
        Vector2<int32_t> size = getSize().as<int32_t>();
        Point2<int32_t> in_start{ std::max(0, std::min(static_cast<int32_t>(_start.pos.x), size.x)), std::max(0, std::min(static_cast<int32_t>(_start.pos.y), size.y)) };
        Point2<int32_t> in_end{ std::max(0, std::min(static_cast<int32_t>(_end.pos.x), size.x)), std::max(0, std::min(static_cast<int32_t>(_end.pos.y), size.y)) };
        Vector2<int32_t> derivate = in_start - in_end;
        Vector2<int32_t> derivate_abs{ std::abs(derivate.x), std::abs(derivate.y) };
        int32_t sx = (derivate.x >= 0) ? -1 : 1;
        int32_t sy = (derivate.y >= 0) ? -1 : 1;

        if (derivate.x == 0 && derivate.y == 0)
            return;

        if (derivate_abs.x > derivate_abs.y) {
            int32_t delta = 2 * derivate_abs.y - derivate_abs.x;
            for (Point2<uint32_t> pos = in_start.as<uint32_t>(); pos.x != in_end.x; pos.x += sx) {
                if (delta > 0) {
                    pos.y += sy;
                    delta -= 2 * derivate_abs.x;
                }
                delta += 2 * derivate_abs.y;
                setPixel(pos, _start.clr);
            }
        }
        else {
            int32_t delta = 2 * derivate_abs.x - derivate_abs.y;
            for (Point2<uint32_t> pos = in_start.as<uint32_t>(); pos.y != in_end.y; pos.y += sy) {
                if (delta > 0) {
                    pos.x += sx;
                    delta -= 2 * derivate_abs.y;
                }
                delta += 2 * derivate_abs.x;
                setPixel(pos, _start.clr);
            }
        }
    }

    void RenderTarget2D::drawTriangle(const Vertex2D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture * _txtr)
    {
        using ColorProcess = Color (*)(const Vertex2D *, float, float, float, const Texture *);

        float total_area = area(_vtx[0].pos, _vtx[1].pos, _vtx[2].pos);
        float ratio1 = 0;
        float ratio2 = 0;
        float ratio3 = 0;
        Point2<uint32_t> size = getSize() - 1;
        ColorProcess getColor;

        if (_txtr == nullptr) {
            getColor = [] (const Vertex2D *_vtx, float _ratio1, float _ratio2, float _ratio3, const Texture * _txtr) {
                std::ignore = _txtr;

                return Color{ static_cast<uint8_t>(_vtx[1].clr.R * _ratio1 + _vtx[2].clr.R * _ratio2 + _vtx[0].clr.R * _ratio3),
                    static_cast<uint8_t>(_vtx[1].clr.G * _ratio1 + _vtx[2].clr.G * _ratio2 + _vtx[0].clr.G * _ratio3),
                    static_cast<uint8_t>(_vtx[1].clr.B * _ratio1 + _vtx[2].clr.B * _ratio2 + _vtx[0].clr.B * _ratio3),
                    static_cast<uint8_t>(_vtx[1].clr.A * _ratio1 + _vtx[2].clr.A * _ratio2 + _vtx[0].clr.A * _ratio3) };
            };
        } else {
            getColor = [](const Vertex2D* _vtx, float _ratio1, float _ratio2, float _ratio3, const Texture* _txtr) {
                Point2<float> pos = _vtx[1].txtrPos * _ratio1 + _vtx[2].txtrPos * _ratio2 + _vtx[0].txtrPos * _ratio3;
                return _txtr->getPixel(pos.as<uint32_t>());
            };
        }
        // caluclate minimal range of the drawing on x axes
        float xstart = static_cast<float>(std::max(_range.x, 0U));
        float xend = static_cast<float>(std::min(_range.y, size.x));

        for (Point2<float> px = { xstart, static_cast<float>(_line) }; px.x <= xend; px.x++) {
            // calculating mapping of the texture
            ratio1 = area(_vtx[2].pos, _vtx[0].pos, px) / total_area;
            ratio2 = area(_vtx[0].pos, _vtx[1].pos, px) / total_area;
            ratio3 = 1 - ratio1 - ratio2;
            setPixel(px.as<uint32_t>(), getColor(_vtx, ratio1, ratio2, ratio3, _txtr));
        }
    }

    void RenderTarget2D::setPixel(const Point2<uint32_t> &_pos, Color _clr)
    {
        uint32_t clr = CLR(_clr);

        std::memcpy(m_data + (_pos.y * getSize().x + _pos.x) * static_cast<uint32_t>(m_bpp / 8), &clr, sizeof(uint32_t));
    }
}