#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>

#include "scene/Object.h"
#include "render/Renderer.h"
#include "render/Frame.h"
#include "scene/Camera.h"
#include "scene/Scene.h"

using namespace renderer;  // FIXME: for test only

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;

    Frame frame(WIDTH, HEIGHT);
    float aspect = static_cast<float>(HEIGHT) / WIDTH;
    Camera camera(0.1f, 1000.0f, M_PI / 2.0f, aspect);
    Scene scene(camera);
    Renderer renderer(scene);

    // Object 1
    Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    transform.translate(Eigen::Vector3f(0.0f, 0.0f, 2.0f));
    //transform.rotate(Eigen::AngleAxisf(M_PI / 4.0f, -Eigen::Vector3f::UnitZ()));
    transform.rotate(Eigen::AngleAxisf(M_PI / 2.5f, Eigen::Vector3f::UnitX()));
    Eigen::Matrix4f M = transform.matrix();

    Object obj1({}, M);
    Vertex v1(Vector4(-1.0f, 0, 0.0f, 1), Vector4::Zero(),
        Color::from_SFML(sf::Color::Red));
    Vertex v2(Vector4(1.0f, 0, 0.0f, 1), Vector4::Zero(),
        Color::from_SFML(sf::Color::Yellow));
    Vertex v3(Vector4(0.0f, 8.0f, 0.0f, 1), Vector4::Zero(),
        Color::from_SFML(sf::Color::White));
    obj1.add_triangle(Triangle(v1, v2, v3));
    scene.add_object(obj1);

    // Object 2
    Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
    transform_2.translate(Eigen::Vector3f(0.0f, 0.2f, 4.0f));
    transform_2.rotate(Eigen::AngleAxisf(M_PI / 4.0f, -Eigen::Vector3f::UnitZ()));
    //transform_2.rotate(Eigen::AngleAxisf(-M_PI / 2.5f, Eigen::Vector3f::UnitX()));
    Eigen::Matrix4f M_2 = transform_2.matrix();

    Object obj2({}, M_2);
    Vertex v1_2(Vector4(-1.0f, 0, 0.0f, 1), Vector4::Zero(),
        Color::from_SFML(sf::Color::Green));
    Vertex v2_2(Vector4(1.0f, 0, 0.0f, 1), Vector4::Zero(),
        Color::from_SFML(sf::Color::Green));
    Vertex v3_2(Vector4(0.0f, 1.0f, 0.0f, 1), Vector4::Zero(),
        Color::from_SFML(sf::Color::Blue));
    obj2.add_triangle(Triangle(v1_2, v2_2, v3_2));
    scene.add_object(obj2);



    frame = renderer.make_frame(std::move(frame));

    // Drawing
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WIDTH, HEIGHT)), "3D Renderer");
    sf::Texture texture(sf::Vector2u(WIDTH, HEIGHT));
    texture.update(frame.get_pixels().data());
    sf::Sprite sprite(texture);

    window.clear();
    window.draw(sprite);
    window.display();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
    }

    return 0;
}
