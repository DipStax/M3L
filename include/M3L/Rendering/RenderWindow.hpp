#pragma once

#include "M3L/Event/Event.hpp"
#include "M3L/Event/EventPool.hpp"
#include "M3L/Rendering/RenderTarget2D.hpp"
#include "M3L/Rendering/RenderTarget3D.hpp"
#include "M3L/System/Window.hpp"

namespace m3l
{
    using EPWindow = EventPool<Event::Focus, Event::MouseButton, Event::MouseMove, Event::Keyboard, Event::Resize>;

    class M3L_API RenderWindow : public EPWindow, public Window, public RenderTarget2D, public RenderTarget3D
    {
        public:
            RenderWindow(ThreadPool &_tp, uint32_t _x, uint32_t _y, const std::string &_title);
            ~RenderWindow() = default;

            [[nodiscard]] const Point2<uint32_t> &getSize() const;

            bool pollEvent(Event &_event);

            void display();

            void clear(const Color &_clr = { 0, 0, 0, 255 });

        protected:
            void create(uint32_t _x, uint32_t _y, const Camera &_cam = Camera(), uint8_t _bpp = 32);

            void render(HDC _draw) const;

            void onResize(Event _event) override;
            void onMouseButtonEvent(Event _event) override;
            void onMouseMove(Event _event) override;
            void onKeyboardEvent(Event _event) override;
            void onFocus(Event _event) override;

        private:
            Point2<uint32_t> m_size;

            ts::Queue<Event> m_event;
    };
}