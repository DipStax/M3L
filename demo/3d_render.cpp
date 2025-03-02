#include "M3L/Rendering/Target/RenderWindow.hpp"
#include "M3L/Rendering/Model.hpp"
#include <thread>
#include <chrono>

int main()
{
    m3l::ThreadPool tp;
    m3l::RenderWindow window(tp, 300, 300, "title");
    m3l::Event event;
    m3l::Texture texture;
    m3l::Object3D obj;
    m3l::Model model;
    m3l::Color white{ 255, 255, 255, 255 };
    m3l::Color blue{ 0, 0, 255, 255 };

    obj.load("ressources/Cube.obj");
    texture.load("ressources/texture.bmp");

    m3l::Camera& cam = window.getCamera();
    cam.setPosition({ 0.f, 0.f, 10.f });
    model.setTexture(texture);
    model.setObject(obj);
    model.displayEdge(true, false);
    while (window.isOpen()) {
        while (window.pollEvent(event)) {}
        cam.rotate({ 1, 0, 0 });
        window.clear(blue);
        window.draw(model);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}