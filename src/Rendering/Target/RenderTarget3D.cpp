#include <cstring>

#include "M3L/Maths/Maths.hpp"
#include "M3L/Rendering/Target/RenderTarget3D.hpp"
#include "M3L/Rendering/PolyTri.hpp"

namespace m3l
{
    RenderTarget3D::~RenderTarget3D()
    {
        if (m_dib)
            DeleteObject(m_dib);
    }

    void RenderTarget3D::setCamera(const Camera &_cam)
    {
        m_cam = _cam;
    }

    const Camera &RenderTarget3D::getCamera() const
    {
        return m_cam;
    }

    Camera &RenderTarget3D::getCamera()
    {
        return m_cam;
    }

    void RenderTarget3D::setBpp(uint8_t _bpp)
    {
        m_bpp = _bpp;
    }

    uint8_t RenderTarget3D::getBpp() const
    {
        return m_bpp;
    }

    void RenderTarget3D::draw(const IDrawable3D &_elem, RenderState3D _state)
    {
        _elem.draw(*this, _state);
    }

    void RenderTarget3D::create(uint32_t _x, uint32_t _y, const Camera &_cam, uint8_t _bpp)
    {
        m_cam = _cam;
        create(_x, _y, _bpp);
    }

    void RenderTarget3D::create(uint32_t _x, uint32_t _y, uint8_t _bpp)
    {
        HDC hdc = GetDC(NULL);
        BITMAPINFO bmi;

        m_bpp = _bpp;
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = _x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(_y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = m_bpp;
        bmi.bmiHeader.biCompression = BI_RGB;
        if (m_dib)
            DeleteObject(m_dib);
        m_dib = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&m_data), NULL, 0);
        ReleaseDC(NULL, hdc);
        m_depth.clear();
        m_depth.resize(_x * _y);
        std::fill(m_depth.begin(), m_depth.end(), std::numeric_limits<float>::lowest());
    }

    void RenderTarget3D::clear(const Color &_clr)
    {
        uint32_t clr = CLR(_clr);
        size_t size = getSize().x * getSize().y * (m_bpp / 8);

        for (size_t it = 0; it < size; it += sizeof(uint32_t))
            std::memcpy(m_data + it, &clr, sizeof(uint32_t));
        std::fill(m_depth.begin(), m_depth.end(), std::numeric_limits<float>::lowest());
    }

    const uint8_t *RenderTarget3D::getData() const
    {
        return m_data;
    }

    void RenderTarget3D::draw(const Vertex3D *_vtx, size_t _size, VertexArray::Type _type, RenderState3D _state)
    {
        std::vector<Vertex3D> cache(_vtx, _vtx + _size);
        Point2<float> size{ 0, 0 };

        _state.transform *= m_cam.getTransform();
        if (_state.texture != nullptr)
            size = _state.texture->getSize().as<float>();
        for (Vertex3D &_vertex : cache) {
            _vertex.pos = m_cam.project(_state.transform * _vertex.pos);
            if (_state.texture != nullptr)
                _vertex.txtrPos *= size; // certainly move it to Model and other IDrawable3D
        }

        switch (_type) {
            case VertexArray::Type::Point:
                for (size_t it = 0; it < _size; it++)
                    setPixel(cache[it].pos.as2<uint32_t>(), cache[it].clr, cache[it].pos.z);
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
                // caluclate minimal range of the drawing on y axes
                for (size_t it = 0; it + 3 <= _size; it += delta) {
                    int32_t ystart = static_cast<int32_t>(std::max(std::min({ cache[0].pos.y, cache[1].pos.y, cache[2].pos.y }), 0.f));
                    int32_t yend = static_cast<int32_t>(std::min(std::max({ cache[0].pos.y, cache[1].pos.y, cache[2].pos.y }), static_cast<float>(getSize().y)));

                    for (; ystart < yend; ystart++)
                        drawTriangle(cache.data() + it, ystart, triRange(cache.data() + it, ystart), _state.texture);
                }
                break;
        }
    }

    void RenderTarget3D::drawLine(const Vertex3D &_start, const Vertex3D &_end)
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
                setPixel(pos, _start.clr, 0);
            }
        } else {
            int32_t delta = 2 * derivate_abs.x - derivate_abs.y;
            for (Point2<uint32_t> pos = in_start.as<uint32_t>(); pos.y != in_end.y; pos.y += sy) {
                if (delta > 0) {
                    pos.x += sx;
                    delta -= 2 * derivate_abs.y;
                }
                delta += 2 * derivate_abs.x;
                setPixel(pos, _start.clr, 0);
            }
        }
    }

    void RenderTarget3D::drawTriangle(const Vertex3D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture *_txtr)
    {
        using ColorProcess = Color (*)(const Vertex3D *, float, float, float, const Texture *);

        Point2<float> vertex1 = _vtx[0].pos.as2();
        Point2<float> vertex2 = _vtx[1].pos.as2();
        Point2<float> vertex3 = _vtx[2].pos.as2();

        float total_area = area(vertex1, vertex2, vertex3);

        // caluclate minimal range of the drawing on x axes
        float xstart = static_cast<float>(std::max(_range.x, 0U));
        float xend = static_cast<float>(std::min(_range.y, getSize().x));
        uint32_t depth_pos = _line * getSize().x + static_cast<uint32_t>(xstart);

        float ratio1 = 0.f;
        float ratio2 = 0.f;
        float ratio3 = 0.f;
        float depth = 0.f;
        Point2<float> rpos = { 0.f, 0.f };
        ColorProcess getColor;

        if (_txtr == nullptr) {
            getColor = [] (const Vertex3D *_vtx, float _ratio1, float _ratio2, float _ratio3, const Texture * _txtr) {
                std::ignore = _txtr;

                return Color{ static_cast<uint8_t>(_vtx[1].clr.R * _ratio1 + _vtx[2].clr.R * _ratio2 + _vtx[0].clr.R * _ratio3),
                    static_cast<uint8_t>(_vtx[1].clr.G * _ratio1 + _vtx[2].clr.G * _ratio2 + _vtx[0].clr.G * _ratio3),
                    static_cast<uint8_t>(_vtx[1].clr.B * _ratio1 + _vtx[2].clr.B * _ratio2 + _vtx[0].clr.B * _ratio3),
                    static_cast<uint8_t>(_vtx[1].clr.A * _ratio1 + _vtx[2].clr.A * _ratio2 + _vtx[0].clr.A * _ratio3) };
            };
        } else {
            getColor = [](const Vertex3D *_vtx, float _ratio1, float _ratio2, float _ratio3, const Texture* _txtr) {
                Point2<float> pos = _vtx[1].txtrPos * _ratio1 + _vtx[2].txtrPos * _ratio2 + _vtx[0].txtrPos * _ratio3;
                return _txtr->getPixel(pos.as<uint32_t>());
            };
        }

        for (Point2<float> pos = { xstart, static_cast<float>(_line) }; pos.x <= xend; pos.x++, depth_pos++) {
            // calculating mapping of the depth
            ratio1 = area(vertex3, vertex1, pos) / total_area;
            ratio2 = area(vertex1, vertex2, pos) / total_area;
            ratio3 = 1 - ratio1 - ratio2;
            depth = _vtx[1].pos.z * ratio1 + _vtx[2].pos.z * ratio2 + _vtx[0].pos.z * ratio3;
            if (depth > m_depth[depth_pos])
                setPixel(pos.as<uint32_t>(), getColor(_vtx, ratio1, ratio2, ratio3, _txtr), depth);
        }
    }

    void RenderTarget3D::setPixel(const Point2<uint32_t> &_pos, Color _clr, float _depth)
    {
        size_t pos = _pos.y * getSize().x + _pos.x;
        uint32_t clr = CLR(_clr);

        if (0 <= pos && pos < m_depth.size()) {
            m_depth[pos] = _depth;
            std::memcpy(m_data + (_pos.y * getSize().x + _pos.x) * static_cast<uint32_t>(m_bpp / 8), &clr, sizeof(uint32_t));
        }
    }
}