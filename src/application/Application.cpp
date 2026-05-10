#include "Application.h"

#include <utility>

#include "lighting/DirectionalLight.h"
#include "loader/ObjLoader.h"

namespace renderer {

namespace {

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

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        handle_keyboard_input();
        handle_mouse_input();
        frame = renderer_.make_frame(scene_, std::move(frame));
        view_.show(frame);
    }
}

Scene Application::make_scene() {
    Camera camera(0.01f, 1000.0f, M_PI / 2.0f);
    Scene scene(std::move(camera));

    auto obj = ObjLoader::load_from_file("model_1.obj");
    Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    transform.translate(Eigen::Vector3f(-0.2f, -0.35f, 0.9f));
    transform.rotate(Eigen::AngleAxisf(M_PI / 7.0f, -Eigen::Vector3f::UnitX()));
    transform.rotate(Eigen::AngleAxisf(M_PI / 2.0f, -Eigen::Vector3f::UnitZ()));
    obj.set_transform_matrix(transform.matrix());
    scene.add_object(obj);

    const DirectionalLight sun{Color(1.0f, 1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.6f)};
    scene.add_directional_light(sun);

    return scene;
}

void Application::handle_keyboard_input() {
    using sf::Keyboard::isKeyPressed;
    using sf::Keyboard::Scancode;

    auto& camera = scene_.camera();

    if (isKeyPressed(Scancode::W)) {
        camera.move_forward(camera_move_speed);
    }
    if (isKeyPressed(Scancode::S)) {
        camera.move_backward(camera_move_speed);
    }
    if (isKeyPressed(Scancode::A)) {
        camera.move_left(camera_move_speed);
    }
    if (isKeyPressed(Scancode::D)) {
        camera.move_right(camera_move_speed);
    }
    if (isKeyPressed(Scancode::Q)) {
        camera.move_up(camera_move_speed);
    }
    if (isKeyPressed(Scancode::E)) {
        camera.move_down(camera_move_speed);
    }
}

void Application::handle_mouse_input() {
    sf::Vector2i current_pos = sf::Mouse::getPosition(view_.window());
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i delta = current_pos - mouse_pos_;
        auto& camera = scene_.camera();
        if (delta.x) {
            camera.rotate_horizontal(-calc_camera_rotation_angle(delta.x));
        }
        if (delta.y) {
            camera.rotate_vertical(-calc_camera_rotation_angle(delta.y));
        }
    }
    mouse_pos_ = current_pos;
}

float Application::calc_camera_rotation_angle(int mouse_offset) const {
    return static_cast<float>(mouse_offset) * mouse_sensitivity_;
}

}  // namespace renderer
