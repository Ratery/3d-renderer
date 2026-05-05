#include "Application.h"

#include <utility>

namespace renderer {

namespace {

Color from_sf_color(const sf::Color& sf_color) {
    return {sf_color.r / 255.0f, sf_color.g / 255.0f, sf_color.b / 255.0f, sf_color.a / 255.0f};
}

Frame create_frame_for_window(const sf::RenderWindow& window) {
    auto [width, height] = window.getSize();
    return {Width{width}, Height{height}};
}

}  // namespace

Application::Application(Width width, Height height, const std::string& title)
    : scene_(make_scene()), view_(width, height, title) {}

void Application::run() {
    auto& window = view_.window();
    auto frame = create_frame_for_window(window);

    frame = renderer_.make_frame(scene_, std::move(frame));
    view_.show(frame);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
    }
}

Scene Application::make_scene() {
    Camera camera(0.1f, 1000.0f, M_PI / 2.0f);
    Scene scene(std::move(camera));

    // Object 1
    Eigen::Affine3f transform_1 = Eigen::Affine3f::Identity();
    transform_1.translate(Eigen::Vector3f(0.0f, 0.0f, 2.0f));
    transform_1.rotate(Eigen::AngleAxisf(M_PI / 2.5f, Eigen::Vector3f::UnitX()));
    Eigen::Matrix4f M_1 = transform_1.matrix();

    Object obj1({}, M_1);
    obj1.add_triangle(Triangle(Vector4(-1.0f, 0, 0.0f, 1), Vector4(1.0f, 0, 0.0f, 1),
                               Vector4(0.0f, 8.0f, 0.0f, 1), Vector4::Zero(), Vector4::Zero(),
                               Vector4::Zero(), from_sf_color(sf::Color::Red),
                               from_sf_color(sf::Color::Yellow), from_sf_color(sf::Color::White)));
    scene.add_object(obj1);

    // Object 2
    Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
    transform_2.translate(Eigen::Vector3f(0.0f, 0.2f, 4.0f));
    transform_2.rotate(Eigen::AngleAxisf(M_PI / 4.0f, -Eigen::Vector3f::UnitZ()));
    Eigen::Matrix4f M_2 = transform_2.matrix();

    Object obj2({}, M_2);
    obj2.add_triangle(Triangle(Vector4(-1.0f, 0, 0.0f, 1), Vector4(1.0f, 0, 0.0f, 1),
                               Vector4(0.0f, 1.0f, 0.0f, 1), Vector4::Zero(), Vector4::Zero(),
                               Vector4::Zero(), from_sf_color(sf::Color::Green),
                               from_sf_color(sf::Color::Green), from_sf_color(sf::Color::Blue)));
    scene.add_object(obj2);
    return scene;
}

}  // namespace renderer
