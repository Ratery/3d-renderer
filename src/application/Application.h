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

    static Scene make_scene();
};

}  // namespace renderer
