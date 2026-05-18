#pragma once

#include "core/Linalg.h"

namespace renderer {

class Camera {
   public:
    explicit Camera(float near, float far, float fov);

    const Matrix4& get_view_matrix() const;
    Matrix4 make_projection_matrix(float aspect_ratio) const;

    void move_forward(float distance);
    void move_backward(float distance);
    void move_right(float distance);
    void move_left(float distance);
    void move_up(float distance);
    void move_down(float distance);
    void rotate_horizontal(float angle);
    void rotate_vertical(float angle);

   private:
    float near_;
    float far_;
    float fov_;
    Matrix4 view_matrix_;

    Vector3 get_world_up_vector() const;
};

}  // namespace renderer
