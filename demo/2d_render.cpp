#include "M3L/Graphics/Target/RenderWindow.hpp"
#include "M3L/Graphics/Sprite.hpp"
#include "M3L/Graphics/2D/Rectangle.hpp"

int main()
{
    m3l::ThreadPool tp;
    m3l::RenderWindow window(tp, 500, 500, "title");
    m3l::Event event;

    m3l::Texture texture;
    m3l::Sprite sprite;

    texture.load("ressources/texture.bmp");
    sprite.setTexture(texture);
    sprite.setPosition(20.f, 50.f);
    //sprite.rotate(30);

    m3l::Color red = { 255, 0, 0, 255 };
    m3l::Color green = { 0, 255, 0, 255 };
    m3l::Color blue = { 0, 0, 255, 255 };
    m3l::VertexArray vertex(m3l::VertexArray::Type::Triangle);

    vertex.append({ { 200, 200 }, { 0, 0 }, red });
    vertex.append({ { 200, 250 }, { 0, 0 }, green });
    vertex.append({ { 250, 200 }, { 0, 0 }, blue });

    m3l::VertexArray vertex2(m3l::VertexArray::Type::LineStrip);

    vertex2.append({ { 350, 200 }, { 0, 0 }, red });
    vertex2.append({ { 300, 200 }, { 0, 0 }, blue });
    vertex2.append({ { 350, 250 }, { 0, 0 }, green });
    vertex2.append({ { 350, 225 }, { 0, 0 }, red });
    vertex2.append({ { 375, 200 }, { 0, 0 }, blue });

    m3l::Rectangle2D rect{ 50, 50 };

    rect.setPosition(200, 50);
    rect.rotate(135);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {}
        window.clear(blue);
        window.draw(sprite);
        window.draw(vertex);
        window.draw(vertex2);
        window.draw(rect);
        window.display();
    }
    return 0;
}