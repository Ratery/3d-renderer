#pragma once

#include "View.h"
#include "render/Frame.h"
#include "render/Renderer.h"
#include "scene/Scene.h"

namespace renderer {

class Application {
   public:
    Application(Width width, Height height, const std::string& title);
    void run();

   private:
    Renderer renderer_;
    Scene scene_;
    View view_;
    sf::Vector2i mouse_pos_;
    static constexpr float camera_move_speed = 0.2f;
    static constexpr float mouse_sensitivity_ = 0.002f;

    static Scene make_scene();

    void handle_keyboard_input();
    void handle_mouse_input();

    float calc_camera_rotation_angle(int mouse_offset) const;
};

}  // namespace renderer
