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

}  // namespace renderer
