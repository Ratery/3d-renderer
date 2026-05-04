#pragma once

#include <vector>

#include "Camera.h"
#include "Object.h"

namespace renderer {

class Scene {
   public:
    explicit Scene(Camera&& camera);

    void add_object(const Object& obj);
    void add_object(Object&& obj);

    const std::vector<Object>& get_objects() const;

    Camera& camera();
    const Camera& get_camera() const;

   private:
    Camera camera_;
    std::vector<Object> objects_;
};

}  // namespace renderer
