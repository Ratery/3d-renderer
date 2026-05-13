#pragma once

#include <vector>

#include "rendering/lighting/AmbientLight.h"
#include "rendering/lighting/DirectionalLight.h"
#include "scene/Camera.h"
#include "scene/Object.h"

namespace renderer {

class Scene {
   public:
    explicit Scene(Camera&& camera);

    void add_object(const Object& obj);
    void add_object(Object&& obj);

    const std::vector<Object>& get_objects() const;

    Camera& camera();
    const Camera& get_camera() const;

    const AmbientLight& get_ambient_light() const;
    const std::vector<DirectionalLight>& get_directional_lights() const;
    void set_ambient_light(const AmbientLight& light);
    void add_directional_light(const DirectionalLight& light);

   private:
    Camera camera_;
    std::vector<Object> objects_;
    AmbientLight ambient_light_;
    std::vector<DirectionalLight> directional_lights_;
};

}  // namespace renderer
