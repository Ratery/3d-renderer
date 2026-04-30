#include "Camera.h"

#include <cmath>

namespace renderer {

Camera::Camera(float near, float far, float fov, float aspect_ratio)
    : near_(near),
      far_(far),
      fov_(fov),
      aspect_ratio_(aspect_ratio),
      view_matrix_(Matrix4::Identity()) {}

Matrix4 Camera::get_view_matrix() const {
    return view_matrix_;
}

Matrix4 Camera::get_projection_matrix() const {
    float right = near_ * std::tan(fov_ / 2.0f);
    float top = right * aspect_ratio_;
    return Matrix4{
        {near_ / right, 0.0f, 0.0f, 0.0f},
        {0.0f, near_ / top, 0.0f, 0.0f},
        {0.0f, 0.0f, (far_ + near_) / (far_ - near_), -2.0f * near_ * far_ / (far_ - near_)},
        {0.0f, 0.0f, 1.0f, 0.0f}};
}

}  // namespace renderer
