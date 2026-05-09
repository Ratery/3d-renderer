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
    static constexpr float camera_move_speed = 0.2f;
    static constexpr float camera_rotate_speed = 0.05f;

    static Scene make_scene();

    void handle_keyboard_input();
};

}  // namespace renderer
