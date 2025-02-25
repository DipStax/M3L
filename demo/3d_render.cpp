#include "M3L/Rendering/Target/RenderWindow.hpp"
#include "M3L/Rendering/Model.hpp"

int main()
{
    m3l::ThreadPool tp;
    m3l::RenderWindow window(tp, 300, 300, "title");
    m3l::Event event;
    m3l::Texture texture;
    m3l::Object3D obj;
    m3l::Model model;
    m3l::Color white{ 255, 255, 255, 255 };

    obj.load("ressources/Cube.obj");
    texture.load("ressources/texture.bmp");

    window.getCamera().setPosition({ 5.f, 0.f, 5.f });
    model.setTexture(texture);
    model.setObject(obj);
    // model.displayEdge(true, true);
    while (window.isOpen()) {
        while (window.pollEvent(event)) {}
        window.clear(white);
        window.draw(model);
        window.display();
    }
    return 0;
}