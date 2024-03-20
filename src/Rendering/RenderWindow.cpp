#include "M3L/Maths/Maths.hpp"
#include "M3L/Rendering/RenderWindow.hpp"
#include "M3L/Rendering/Sprite.hpp"

namespace m3l
{
    RenderWindow::RenderWindow(ThreadPool &_tp, uint32_t _x, uint32_t _y, const std::string &_title)
        : EPWindow(_tp), Window(_x, _y, _title)
    {
        Point2<uint32_t> size = getSize();

        create(m_size.y, m_size.x);
        getCamera().setFov(110.f).setRange(0.1f, 100.f).setSize(static_cast<float>(size.x), static_cast<float>(size.y)).move({ 0, 0, -10 });
    }

    const Point2<uint32_t> &RenderWindow::getSize() const
    {
        return m_size;
    }

    bool RenderWindow::pollEvent(Event &_event)
    {
        disptachEvent();
        if (!m_event.empty())
            _event = m_event.pop_front();
        return !m_event.empty();
    }

    void RenderWindow::display()
    {
        InvalidateRect(getWindow(), NULL, FALSE);
    }

    void RenderWindow::clear(const Color &_clr)
    {
        RenderTarget2D::clear(_clr);
        RenderTarget3D::clear(_clr);
    }

    void RenderWindow::create(uint32_t _x, uint32_t _y, const Camera &_cam, uint8_t _bpp)
    {
        m_size = { _x, _y };
        RenderTarget2D::create(m_size.y, m_size.x, _bpp);
        RenderTarget3D::create(m_size.y, m_size.x, _cam, _bpp);
    }

    void RenderWindow::render(HDC _draw) const
    {
        Point2<uint32_t> size = getSize();
        BITMAPINFO bmi;
        // bpp handling
        std::vector<uint32_t> data(size.x * size.y);
        const uint32_t *data2d = reinterpret_cast<const uint32_t *>(RenderTarget2D::getData());
        const uint32_t *data3d = reinterpret_cast<const uint32_t *>(RenderTarget3D::getData());

        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = size.x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(size.y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = RenderTarget2D::getBpp();
        bmi.bmiHeader.biCompression = BI_RGB;
        for (size_t it = 0; it < size.x * size.y; it++) {
            // bpp handling
            if (CLR_GET_ALPHA(data2d[it]) == 0 || CLR_GET_RGB(data2d[it]) == 0)
                data[it] = data3d[it];
            else
                data[it] = data2d[it];
        }
        SetDIBitsToDevice(_draw, 0, 0, size.x, size.y, 0, 0, 0, size.y, data.data(), &bmi, DIB_RGB_COLORS);
    }

    void RenderWindow::onResize(Event _event)
    {
        Event::Resize resize = std::get<Event::Resize>( _event.event);
        m_size = { resize.width, resize.height };
        RenderTarget2D::create(resize.width, resize.height);
        RenderTarget3D::create(resize.width, resize.height);
        getCamera().setSize(static_cast<float>(resize.width), static_cast<float>(resize.height));
        raise<Event::Resize>(resize);
        m_event.push(_event);
    }

    void RenderWindow::onMouseButtonEvent(Event _event)
    {
        raise<Event::MouseButton>(std::get<Event::MouseButton>(_event.event));
        m_event.push(_event);
    }

    void RenderWindow::onMouseMove(Event _event)
    {
        raise<Event::MouseMove>(std::get<Event::MouseMove>(_event.event));
        m_event.push(_event);
    }

    void RenderWindow::onKeyboardEvent(Event _event)
    {
        raise<Event::Keyboard>(std::get<Event::Keyboard>(_event.event));
        m_event.push(_event);
    }

    void RenderWindow::onFocus(Event _event)
    {
        raise<Event::Focus>(std::get<Event::Focus>(_event.event));
        m_event.push(_event);
    }
}