#include "M3L/Maths/Maths.hpp"
#include "M3L/Rendering/RenderWindow.hpp"
#include "M3L/Rendering/Sprite.hpp"

#include <iostream>

namespace m3l
{
    RenderWindow::RenderWindow(ThreadPool &_tp, uint32_t _x, uint32_t _y, const std::string &_title)
        : EPWindow(_tp), Window(_x, _y, _title)
    {
        Point2<uint32_t> size = getSize();

        getCamera().setFov(110.f).setRange(0.1f, 100.f).setSize(static_cast<float>(size.x), static_cast<float>(size.y)).move({ 0, 0, -10 });
        m_size = { _x, _y };
        create(m_size.y, m_size.x);
    }

    Point2<uint32_t> RenderWindow::getSize() const
    {
        return m_size;
    }

    void RenderWindow::setCamera(const Camera &_cam)
    {
        m_cam = _cam;
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

    void RenderWindow::onResize(Event _event)
    {
        Event::Resize resize = std::get<Event::Resize>( _event.event);
        m_size = { resize.width, resize.height };
        create(resize.width, resize.height);
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

    void RenderWindow::render(HDC _draw) const
    {
        Point2<uint32_t> size = getSize();
        BITMAPINFO bmi;

        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = size.x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(size.y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = getBpp();
        bmi.bmiHeader.biCompression = BI_RGB;
        SetDIBitsToDevice(_draw, 0, 0, size.x, size.y, 0, 0, 0, size.y, getData(), &bmi, DIB_RGB_COLORS);
    }
}