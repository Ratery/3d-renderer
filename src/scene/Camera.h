#pragma once

#include "core/Linalg.h"

namespace renderer {

class Camera {
   public:
    explicit Camera(float near, float far, float fov);

    Matrix4 make_view_matrix() const;
    Matrix4 make_projection_matrix(float aspect_ratio) const;

   private:
    float near_;
    float far_;
    float fov_;
    Matrix4 view_matrix_;
};

}  // namespace renderer
