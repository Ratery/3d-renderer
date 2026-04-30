#pragma once

#include "../core/Linalg.h"

namespace renderer {

class Camera {
public:
    explicit Camera(float near, float far, float fov, float aspect_ratio);

    Matrix4 get_view_matrix() const;
    Matrix4 get_projection_matrix() const;

private:
    float near_;
    float far_;
    float fov_;
    float aspect_ratio_;
    Matrix4 view_matrix_;
};

}  // namespace renderer
